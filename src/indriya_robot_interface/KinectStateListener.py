__author__ = 'Praveenkumar'

import os
import zmq
import sys
import time
import argparse
import thread
import json
from naoqi import ALProxy

from os.path import dirname
from os.path import abspath

dev = os.environ["INDRIYA_ROOT"]
dir1 = os.path.join(dev,"scripts","msgs")

sys.path.append(dir1)

import kinect_body_pb2

useSensors = False

if __name__ == "__main__":
    # Real Robot

    SUB_IP = "tcp://localhost"
    SUB_PORT = "5570"
    SUB_TOPIC = "KSP"
    try:
        if (len(sys.argv) >= 3):
              print sys.argv
              parser = argparse.ArgumentParser(description='Kinect state listener')
              parser.add_argument('-p','--param', help='Parameter server address', required=True)
              parser.add_argument('-n','--name', help='Name of the node', required=True)
              args = vars(parser.parse_args())
              name = args["name"]
              paramServer = args["param"]

              # Utils
              import parameter_utils
              node = parameter_utils.getNodeParameters(name,paramServer,1000)

              if node != None:
                  print node
                  sub = parameter_utils.getSubscriberInfo(node,"KinectBodies")
                  if sub != None:
                    SUB_IP = sub.host.encode('utf-8')
                    SUB_PORT = sub.port
                    SUB_TOPIC = sub.topic.encode('utf-8')
                    print "Subscriber info retrieved"
        else:
              print "Start locally"

        context = zmq.Context()
        sock = context.socket(zmq.SUB)
        sock.connect("%s:%s" % (SUB_IP,SUB_PORT))
        sock.setsockopt(zmq.SUBSCRIBE, SUB_TOPIC)

        while True:
            topic = sock.recv()
            message = sock.recv()
            bodies = kinect_body_pb2.KinectBodies()
            #print message
            bodies.ParseFromString(message)

            print bodies
    except:
      print "Exception occured : ", sys.exc_info()

    raw_input("Press enter to continue ... ")