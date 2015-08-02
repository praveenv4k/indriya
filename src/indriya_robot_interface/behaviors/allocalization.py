from naoqi import ALProxy

robotIP = '192.168.11.3'
PORT = 9559

motionProxy  = ALProxy("ALMotion", robotIP, PORT)
localizationProxy = ALProxy("ALLocalization", robotIP, PORT)

# Learning home.
ret = localizationProxy.learnHome()
# Check that no problem occurred.
if ret == 0:
  print "Learning OK"
else:
  print "Error during learning " + str(ret)

# Make some moves.
motionProxy.moveTo(0.5, 0.0, 0.2)

# Go back home.
ret = localizationProxy.goToHome()
# Check that no problem occurred.
if ret == 0:
  print "go to home OK"
else:
  print "error during go to home " + str(ret)

# Save the data for later use.
ret = localizationProxy.save("example")
# Check that no problem occurred.
if ret == 0:
  print "saving OK"
else:
  print "error during saving" + str(ret)