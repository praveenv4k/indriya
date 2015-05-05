from pytz import utc
import os
import sys
import time
import argparse
import thread

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

# main function
if __name__ == "__main__":
    # port
    port = 5700
    # ip address
    ip = "localhost"

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
                ROBOTIP = parameter_utils.getParam(node,"ROBOTIP", "127.0.0.1")
                PORT =  int(parameter_utils.getParam(node,"PORT", "9559"))
                BEHAVIOR_PORT = int(parameter_utils.getParam(node,"RequestServerPort", "5590"))
                BEHAVIOR_IP = parameter_utils.getParam(node,"RequestServerIP", "*")
                parameter_utils.register_motions(node,paramServer,["crouch","stand","wave","greet"])
                thread.start_new_thread(behavior_server,(BEHAVIOR_IP,BEHAVIOR_PORT,ROBOTIP,PORT));
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

        # client listener
        thread.start_new_thread(localization_client,(ip,port,10,1));
        
        # starting a test server to test the communication. need to be commented when working with real server
        # thread.start_new_thread(localization_server,(ip,port));

    except:
        # printing on exception
        print "Exception occured : ", sys.exc_info()

    # do nothing 
    while 1:
        pass