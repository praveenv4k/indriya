# -*- encoding: UTF-8 -*- 
import os
import sys
import time
import argparse

from naoqi import ALProxy

from os.path import dirname
from os.path import abspath

dev = os.environ["DEV_SDK_ROOT"]
dir1 = os.path.join(dev,"experimot","scripts","msgs")
dir2 = os.path.join(dev,"experimot","scripts","experimot_robot_interface")

#currdir = dirname(__file__)
#parent = abspath(os.path.join(currdir,os.pardir))

sys.path.append(dir1)
sys.path.append(dir2)

# Message - Node parameters
#import node_pb2
# Zero mq messaging library
import zmq
# Utils
import parameter_utils

def main(robotIP, port, behaviorName):
  # Create proxy to ALBehaviorManager
  print "Creating behavior manager", robotIP, port
  managerProxy = ALProxy("ALBehaviorManager", robotIP, port)

  getBehaviors(managerProxy)
  launchAndStopBehavior(managerProxy, behaviorName)
  defaultBehaviors(managerProxy, behaviorName)

def getBehaviors(managerProxy):
  ''' Know which behaviors are on the robot '''

  names = managerProxy.getInstalledBehaviors()
  print "Behaviors on the robot:"
  print names

  names = managerProxy.getRunningBehaviors()
  print "Running behaviors:"
  print names

def launchAndStopBehavior(managerProxy, behaviorName):
  ''' Launch and stop a behavior, if possible. '''

  # Check that the behavior exists.
  if (managerProxy.isBehaviorInstalled(behaviorName)):

    # Check that it is not already running.
    if (not managerProxy.isBehaviorRunning(behaviorName)):
      # Launch behavior. This is a blocking call, use post if you do not
      # want to wait for the behavior to finish.
      managerProxy.post.runBehavior(behaviorName)
      time.sleep(1)
    else:
      print "Behavior is already running."

  else:
    print "Behavior not found."
    return

  names = managerProxy.getRunningBehaviors()
  print "Running behaviors:"
  print names

  # Stop the behavior.
  while (managerProxy.isBehaviorRunning(behaviorName)):
    time.sleep(1.0)
  
  if (managerProxy.isBehaviorRunning(behaviorName)):
    managerProxy.stopBehavior(behaviorName)
    time.sleep(1.0)
  else:
    print "Behavior is already stopped."

  names = managerProxy.getRunningBehaviors()
  print "Running behaviors:"
  print names

def defaultBehaviors(managerProxy, behaviorName):
  ''' Set a behavior as default and remove it from default behavior. '''

  # Get default behaviors.
  names = managerProxy.getDefaultBehaviors()
  print "Default behaviors:"
  print names

  # Add behavior to default.
  managerProxy.addDefaultBehavior(behaviorName)

  names = managerProxy.getDefaultBehaviors()
  print "Default behaviors:"
  print names

  # Remove behavior from default.
  managerProxy.removeDefaultBehavior(behaviorName)

  names = managerProxy.getDefaultBehaviors()
  print "Default behaviors:"
  print names


if __name__ == "__main__":

  #if (len(sys.argv) < 3):
  #  print "Usage python albehaviormanager_example.py robotIP behaviorName"
  #  sys.exit(1)
  try:
      ROBOTIP = "127.0.0.1"
      PORT = 55241
      main(ROBOTIP, PORT, "stand")
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

          ROBOTIP = parameter_utils.getParam(node,"ROBOTIP", "127.0.0.1")
          PORT =  int(parameter_utils.getParam(node,"PORT", "9559"))

          print ROBOTIP, PORT
      else:
          print "Start locally"

      #param = parameter_util.getNodeParameters(

      #main(sys.argv[1], sys.argv[2])

      main(ROBOTIP, PORT, "crouch")
  except:
      print "Exception occured : ", sys.exc_info()

  #obj = node_pb2.Node()

  raw_input("Press enter to continue ... ")