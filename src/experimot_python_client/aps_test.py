from pytz import utc
import os
import sys
import time
import argparse
import thread
import json
import datetime

from apscheduler.schedulers.background import BackgroundScheduler
#from apscheduler.jobstores.sqlalchemy import SQLAlchemyJobStore
from apscheduler.executors.pool import ThreadPoolExecutor, ProcessPoolExecutor

from os.path import dirname
from os.path import abspath

dev = os.environ["DEV_SDK_ROOT"]
dir1 = os.path.join(dev,"experimot","scripts","msgs")
dir2 = os.path.join(dev,"experimot","scripts","experimot_robot_interface")

sys.path.append(dir1)
sys.path.append(dir2)

# Zero mq messaging library
import zmq
# Parameter server access Utils
# import parameter_utils

scheduler = None



def myfunc():
    print "Hello, this is my function"

#############################################################################################################
# Localization client  
def context_client(lock,ip,port):
    context = zmq.Context()
    #  Socket to talk to server
    print "Connecting to context server ... "
    socket = context.socket(zmq.REQ)
    socket.connect("%s:%s" % (ip,port))

    while True:
        socket.send(b"human")

        #  Get the reply.
        str = socket.recv(1024)
        #print str
        result = json.loads(str)

        # printing the result
        #print len(result)
        check_gesture_trigger(result,socket)
        
        # wait for a while
        time.sleep(0.200)

def check_gesture_trigger(humans, sock):
    num = len(humans)
    use_scheduler = False
    for human in humans:
        for gesture in human["Gestures"]:
            active = bool(gesture["Active"])
            if active == True:
                confidence = int(gesture["Confidence"])
                if confidence > 95:
                    print "Gesture %s is detected" % gesture["Name"]
                    if sock!= None:
                        try:
                            sock.send(b"behavior_modules")
                            #  Get the reply.
                            str = sock.recv(1024)
                            #print str
                            modules = json.loads(str)
                            for module in modules:
                                for behavior in module["behaviors"]:
                                    behavior_name = behavior["name"].encode("utf-8")
                                    if behavior_name == "greet":
                                        global scheduler
                                        id = "nao_behavior"
                                        ret = check_job_exists(id,scheduler)
                                        if ret == False:
                                            responder = module["responder"]
                                            if use_scheduler == True:
                                                #job = scheduler.add_job(execute_behavior_task,args=(behavior_name,responder),id=id)
                                                job = scheduler.add_job(myfunc,id=id,next_run_time=datetime.datetime.now() + datetime.timedelta(seconds=1))
                                                print job
                                            else:
                                                execute_behavior_task(behavior_name,responder)
                                        else:
                                            print "Job already exists"

                            #print modules
                        except:
                            print "Exception occured while retrieving modules : ", sys.exc_info()

def check_job_exists(id,scheduler):
    ret = False
    if scheduler != None:
        job = scheduler.get_job(id)
        if job != None:
            ret = True
    return ret


def execute_behavior_task(name,responder):
    print "execute behavior task"
    if responder != None:
        host = responder["Host"].encode("utf-8")
        port = responder["Port"]
        print "Will connect to %s:%d and request %s" % (host,port,name)
        try:
            # using with keyword save the life! If not used, the unmanaged resources are getting cleaned up
            # and this caused problems with interacting with Naoqi proxy
            with zmq.Context.instance() as ctx: 
                with ctx.socket(zmq.REQ) as sock:
                    #socket = context.socket(zmq.REQ)
                    sock.connect("%s:%s" % (host,port))
                    print "Sending behavior execution request"
                    sock.send(name)
                    print "Waiting behavior modules response"
                    #  Get the reply.
                    str = sock.recv(1024)
                    print "Received behavior modules response"
                    print str
                    #result = json.loads(str)
                    #return result
        except:
            print "execute_behavior_task : ", sys.exc_info()

# main function
if __name__ == "__main__":
    context_server = "tcp://localhost"
    context_port = "5800"
    
    # Advanced Python Scheduler Initialization - Background Scheduler

    #jobstores = {
    #    'default': SQLAlchemyJobStore(url='sqlite:///jobs.sqlite')
    #}
    executors = {
        'default': ThreadPoolExecutor(20),
        'processpool': ProcessPoolExecutor(5)
    }
    job_defaults = {
        'coalesce': False,
        'max_instances': 3
    }
    # global scheduler
    #scheduler = BackgroundScheduler(jobstores=jobstores, executors=executors, job_defaults=job_defaults, timezone=utc)
    scheduler = BackgroundScheduler(executors=executors, job_defaults=job_defaults, timezone=utc)
    #job = scheduler.add_job(myfunc, 'interval', minutes=1)
    scheduler.add_job(myfunc)
    scheduler.start()

    #scheduler.add_job(myfunc,id="job1",next_run_time=datetime.datetime.now() + datetime.timedelta(seconds=1))

    try:
        if (len(sys.argv) >= 3):
            print sys.argv
            parser = argparse.ArgumentParser(description='Main program')
            parser.add_argument('-p','--param', help='Parameter server address', required=True)
            parser.add_argument('-n','--name', help='Name of the node', required=True)
            args = vars(parser.parse_args())
            name = args["name"]
            paramServer = args["param"]

            # Utils
            import parameter_utils
            node = parameter_utils.getNodeParameters(name,paramServer,1000)

            if node != None:
                context_server = parameter_utils.getParam(node,"ContextClientHost","tcp://localhost")
                context_port = parameter_utils.getParam(node,"ContextServerPort","5800")
        else:
            print "Start locally"

        # create a lock object for synchronization
        lock = thread.allocate_lock()

        # client listener
        thread.start_new_thread(context_client,(lock,context_server,context_port));
        
        # starting a test server to test the communication. need to be commented when working with real server
        # thread.start_new_thread(localization_server,(ip,port));

    except:
        # printing on exception
        print "Exception occured : ", sys.exc_info()

    # do nothing 
    while 1:
        pass