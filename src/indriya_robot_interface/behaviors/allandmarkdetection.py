# This test demonstrates how to use the ALLandMarkDetection module.
# - We first instantiate a proxy to the ALLandMarkDetection module
#     Note that this module should be loaded on the robot's NAOqi.
#     The module output its results in ALMemory in a variable
#     called "LandmarkDetected"
# - We then read this AlMemory value and check whether we get
#   interesting things.
import time
import sys
import os
from naoqi import ALProxy

# Replace this with your robot's IP address
IP = "10.0.252.91"
PORT = 9559

# Create a proxy to ALLandMarkDetection
try:
  landMarkProxy = ALProxy("ALLandMarkDetection", IP, PORT)
except Exception, e:
  print "Error when creating landmark detection proxy:"
  print str(e)
  exit(1)

# Subscribe to the ALLandMarkDetection proxy
# This means that the module will write in ALMemory with
# the given period below
period = 500
landMarkProxy.subscribe("Test_LandMark", period, 0.0 )

# ALMemory variable where the ALLandMarkdetection module
# outputs its results
memValue = "LandmarkDetected"

# Create a proxy to ALMemory
try:
  memoryProxy = ALProxy("ALMemory", IP, PORT)
except Exception, e:
  print "Error when creating memory proxy:"
  print str(e)
  exit(1)

print "Creating landmark detection proxy"

# A simple loop that reads the memValue and checks
# whether landmarks are detected.
for i in range(0, 20):
  time.sleep(0.5)
  val = memoryProxy.getData(memValue, 0)
  print ""
  print "\*****"
  print ""
# Check whether we got a valid output: a list with two fields.
if(val and isinstance(val, list) and len(val) == 2):
  # We detected naomarks !
  # For each mark, we can read its shape info and ID.
  # First Field = TimeStamp.
  timeStamp = val[0]
  # Second Field = array of Mark_Info's.
  markInfoArray = val[1]

  try:
    # Browse the markInfoArray to get info on each detected mark.
    for markInfo in markInfoArray:
      # First Field = Shape info.
      markShapeInfo = markInfo[0]
      # Second Field = Extra info (ie, mark ID).
      markExtraInfo = markInfo[1]
      # Print Mark information.
      print "mark  ID: %d" % (markExtraInfo[0])
      print "  alpha %.3f - beta %.3f" % (markShapeInfo[1], markShapeInfo[2])
      print "  width %.3f - height %.3f" % (markShapeInfo[3], markShapeInfo[4])
  except Exception, e:
      print "Naomarks detected, but it seems getData is invalid. ALValue ="
      print val
      print "Error msg %s" % (str(e))
else:
  print "Error with getData. ALValue = %s" % (str(val))

# Unsubscribe from the module.
landMarkProxy.unsubscribe("Test_LandMark")
print "Test terminated successfully."