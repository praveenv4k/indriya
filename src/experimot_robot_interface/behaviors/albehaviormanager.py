# -*- encoding: UTF-8 -*- 

import sys
import time

from naoqi import ALProxy

def main(robotIP, port, behaviorName):
  # Create proxy to ALBehaviorManager
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

  ROBOTIP = "127.0.0.1"
  PORT = 52686

  #main(sys.argv[1], sys.argv[2])
  main(ROBOTIP, PORT, "stand")