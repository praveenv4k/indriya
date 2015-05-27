#!/usr/bin/env python
# -*- coding: utf-8 -*-
__author__ = 'Praveenkumar VASUDEVAN'

from naoqi import ALProxy
import time
import inspect

class NaoBehaviorModule:
    def __init__(self, robot_ip, robot_port):
        self.data = []
        self.ROBOT_IP = robot_ip
        self.ROBOT_PORT = robot_port

    def getPostureProxy(self):
        return ALProxy("ALRobotPosture", self.ROBOT_IP, self.ROBOT_PORT)

    def getTextToSpeechProxy(self):
        return ALProxy("ALTextToSpeech", self.ROBOT_IP, self.ROBOT_PORT)

    def getAnimatedSayProxy(self):
        return ALProxy("ALAnimatedSpeech", self.ROBOT_IP, self.ROBOT_PORT)

    def getMotionProxy(self):
        return ALProxy("ALMotion", self.ROBOT_IP, self.ROBOT_PORT)

    def getBehaviorProxy(self):
        return  ALProxy("ALBehaviorManager", self.ROBOT_IP, self.ROBOT_PORT)

    def getTrackerProxy(self):
        return  ALProxy("ALTracker", self.ROBOT_IP, self.ROBOT_PORT)

    def getLandmarkDetectionProxy(self):
        return  ALProxy("ALLandMarkDetection", self.ROBOT_IP, self.ROBOT_PORT)

    def getInstalledBehaviors(self):
      ''' Know which behaviors are installed on the robot '''
      managerProxy = self.getBehaviorProxy()
      return self.getBehaviors(managerProxy)

    def getBehaviors(self,managerProxy):
      ''' Know which behaviors are installed on the robot '''

      installed = managerProxy.getInstalledBehaviors()
      print "Behaviors on the robot:"
      print installed

      names = managerProxy.getRunningBehaviors()
      print "Running behaviors:"
      print names

      return installed

    def launchAndStopBehavior(self,managerProxy, behaviorName):
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

    def defaultBehaviors(self,managerProxy, behaviorName):
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

    def set_language(self, language):
        proxy = self.getTextToSpeechProxy()
        lang = proxy.getAvailableLanguages()
        if language in lang:
            proxy.setLanguage(language)

    def action_executeBehavior(self,params):
        name = params.get('behaviorName','')
        if name is not '':
            managerProxy = self.getBehaviorProxy()
            self.getBehaviors(managerProxy)
            self.launchAndStopBehavior(managerProxy, name)
            self.defaultBehaviors(managerProxy, name)

    def action_sayExpressively(self,params):
        language = params.get('lang','')
        msg = params.get('msg','')
        if language is not '' and msg is not '':
            proxy = self.getAnimatedSayProxy()
            if proxy is not None:
                self.set_language(language)
                # set the local configuration
                configuration = {"bodyLanguageMode":"contextual"}
                proxy.say(msg,configuration)

    def action_goToPosture(self,params):
        posture = params.get('posture','')
        if posture is not '':
            proxy = self.getPostureProxy()
            if proxy is not None:
                proxy.goToPosture(posture, 1.0)

    def action_lookAt(self,params):
        x = float(params.get('x',0))
        y = float(params.get('y',0))
        z = float(params.get('z',0))
        frameStr = params.get('frame',0)
        frame = 0
        if frameStr == "Torso":
            frame = 0
        elif frameStr == "World":
            frame = 1
        elif frameStr == "Robot":
            frame = 2

        maxSpeed = 0.5
        useWholeBody = False

        proxy = self.getTrackerProxy()
        if proxy is not None:
            proxy.lookAt([x, y, z], frame, maxSpeed, useWholeBody)

    def executeAction(self,name,params):
        method = getattr(self,name)
        if method is not None:
            arg_spec = inspect.getargspec(method)
            #print arg_spec.args
            method(params)

    def getCapabilities(self):
        # action -> function mapping
        installedBehaviors = self.getInstalledBehaviors()
        cap_dict = dict({})
        for insBehavior in installedBehaviors:
            behaviorStr = insBehavior.replace('.lastUploadedChoregrapheBehavior/','',1);
            cap_dict[behaviorStr] = {'function':'action_executeBehavior','args':{'name':'Name of the installed behavior'}}
        cap_dict['Say Expressively']= {'function':'action_sayExpressively','args':{'x':'X coordinate in m','y':'Y coordinate in m','z':'Z coordinate in m','frame':'Frame (World, Torso, Robot)'}}
        cap_dict['Look At']= {'function':'action_sayExpressively','args':{'lang':'Language','msg':'Text'}}
        cap_dict['Sit Relax']= {'function':'action_goToPosture','args':{'posture':'Desired Posture'}}
        cap_dict['LyingBelly']= {'function':'action_goToPosture','args':{'posture':'Desired Posture'}}
        cap_dict['LyingBack']= {'function':'action_goToPosture','args':{'posture':'Desired Posture'}}
        cap_dict['Stand']= {'function':'action_goToPosture','args':{'posture':'Desired Posture'}}
        cap_dict['Crouch']= {'function':'action_goToPosture','args':{'posture':'Desired Posture'}}
        cap_dict['Sit']= {'function':'action_goToPosture','args':{'posture':'Desired Posture'}}
        return cap_dict

# if __name__ == "__main__":
#     a = NaoBehaviorModule('127.0.0.1',57105)
#     msg = 'ありがとうございました。'
#     say_param = {'lang':'Japanese','msg':msg}
#
#     cap = a.getCapabilities()
#     for i in cap:
#         print(i)
#     #msg_encoded = msg.encode('utf-8')
#     a.executeAction('action_goToPosture',{'posture':'Stand'})
#     a.executeAction('action_sayExpressively',say_param)
#     a.executeAction('action_goToPosture',{'posture':'Crouch'})
#     a.executeAction('action_lookAt',{'x':'0','y':'0.5','z':'0.5','frame':'torso'})
#     a.executeAction('action_lookAt',{'x':'0','y':'0.0','z':'0.2','frame':'torso'})