import qi
from naoqi import ALProxy
import NaoBehaviorModule
import time

#session = qi.Session()

#session.connect("tcp://127.0.0.1:51557")
#tts = session.service("ALTextToSpeech")
#tts.say("In 2014, Facebook launched Messenger as a separate chat app and forced Facebook app users to download Messenger if they wanted to instant-message friends on their phones. This year, Facebook started adding third-party apps to Messenger, and the company also introduced a standalone Web version of Messenger this spring.", _async=True)

#tts.say("Hello, World1")
#tts.say("Hello, World2")
#tts.say("Hello, World3")
#tts.say("Hello, World4")
#tts.say("Hello, World5")
#tts.say("Hello, World6")
#tts.say("Hello, World7")

module = NaoBehaviorModule.NaoBehaviorModule("127.0.0.1",51557)

tts = module.getTextToSpeechProxy()

id = tts.post.say("In 2014, Facebook launched Messenger as a separate chat app and forced Facebook app users to download Messenger if they wanted to instant-message friends on their phones. This year, Facebook started adding third-party apps to Messenger, and the company also introduced a standalone Web version of Messenger this spring.")

waitTime = 0
while tts.isRunning(id):
    print "Waiting for execution completion!", waitTime
    time.sleep(0.1)
    waitTime = waitTime + 0.1
    if waitTime > 1:
        tts.stop(id)

print "Execution complete!"