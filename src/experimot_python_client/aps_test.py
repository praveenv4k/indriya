from pytz import utc
import os
import sys
import time
import argparse
import thread
import json

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
        check_gesture_trigger(result)
        
        # wait for a while
        time.sleep(0.200)

def check_gesture_trigger(humans):
    num = len(humans)
    for human in humans:
        #print human
        for gesture in human["Gestures"]:
            active = bool(gesture["Active"])
            if active == True:
                confidence = int(gesture["Confidence"])
                if confidence > 95:
                    print "Gesture %s is detected" % gesture["Name"]

def execute_behavior_blocking(behavior_name):
    print behavior_name

# main function
if __name__ == "__main__":
    context_server = "tcp://localhost"
    context_port = "5800"

    try:
        if (len(sys.argv) >= 3):
            print sys.argv
            parser = argparse.ArgumentParser(description='Nao Robot Behavior')
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
        #scheduler = BackgroundScheduler(jobstores=jobstores, executors=executors, job_defaults=job_defaults, timezone=utc)
        scheduler = BackgroundScheduler(executors=executors, job_defaults=job_defaults, timezone=utc)
        #job = scheduler.add_job(myfunc, 'interval', minutes=1)

        scheduler.start()

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