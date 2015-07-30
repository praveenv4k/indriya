#!/usr/bin/env python
# -*- coding: utf-8 -*-
__author__ = 'Praveenkumar VASUDEVAN'

from naoqi import ALProxy
import time
import inspect
import detectlanguage
import pycountry
import os
import sys
import PeopleTracker

class NaoBehaviorModule:
    def __init__(self, robot_ip, robot_port):
        self.data = []
        self.ROBOT_IP = robot_ip
        self.ROBOT_PORT = robot_port
        #self.language = None
        self.language = 'English'
        self.volume_set = False

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

    def getMemoryProxy(self):
        return  ALProxy("ALMemory", self.ROBOT_IP, self.ROBOT_PORT)

    def getAudioDeviceProxy(self):
        return  ALProxy("ALAudioDevice", self.ROBOT_IP, self.ROBOT_PORT)

    def getLandmarkDetectionProxy(self):
        return  ALProxy("ALLandMarkDetection", self.ROBOT_IP, self.ROBOT_PORT)

    def getInstalledBehaviors(self):
      ''' Know which behaviors are installed on the robot '''
      managerProxy = self.getBehaviorProxy()
      return self.getBehaviors(managerProxy)

    def getBehaviors(self,managerProxy):
      ''' Know which behaviors are installed on the robot '''

      installed = managerProxy.getInstalledBehaviors()
      #print "Behaviors on the robot:"
      #print installed

      #names = managerProxy.getRunningBehaviors()
      #print "Running behaviors:"
      #print names

      return installed

    def launchAndStopBehavior(self,managerProxy, behaviorName):
      ''' Launch and stop a behavior, if possible. '''

      # Check that the behavior exists.
      if (managerProxy.isBehaviorInstalled(behaviorName)):

        # Check that it is not already running.
        if (not managerProxy.isBehaviorRunning(behaviorName)):
          # Launch behavior. This is a blocking call, use post if you do not
          # want to wait for the behavior to finish.
          return managerProxy.post.runBehavior(behaviorName)
          time.sleep(1)
        else:
          print "Behavior is already running."

      else:
        print "Behavior not found."
      
      return -1

      #names = managerProxy.getRunningBehaviors()
      #print "Running behaviors:"
      #print names

      # Stop the behavior.
      #while (managerProxy.isBehaviorRunning(behaviorName)):
      #  time.sleep(1.0)

      #if (managerProxy.isBehaviorRunning(behaviorName)):
      #  managerProxy.stopBehavior(behaviorName)
      #  time.sleep(1.0)
      #else:
      #  print "Behavior is already stopped."

      #names = managerProxy.getRunningBehaviors()
      #print "Running behaviors:"
      #print names

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

    def set_jointAngles(self,jointNames,jointValues):
        proxy = self.getMotionProxy()
        if proxy is not None:
            proxy.setStiffnesses("Body", 1.0)
            fractionMaxSpeed  = 0.2
            proxy.setAngles(jointNames, jointValues, fractionMaxSpeed)

    def set_language(self, language):
        proxy = self.getTextToSpeechProxy()
        lang = proxy.getAvailableLanguages()
        if language in lang:
            proxy.setLanguage(language)

    def action_setLanguage(self, params):
        language = params.get('lang','')
        proxy = self.getTextToSpeechProxy()
        languages = proxy.getAvailableLanguages()
        print languages
        if language in languages:
            self.language = language
            id = proxy.post.setLanguage(language)
            return [id,proxy]
        return []

    def action_executeBehavior(self,params):
        name = params.get('name','')
        if name is not '':
            managerProxy = self.getBehaviorProxy()
            #self.getBehaviors(managerProxy)
            id = self.launchAndStopBehavior(managerProxy, name)
            return [id,managerProxy]
            #self.defaultBehaviors(managerProxy, name)
        return []
     
    def action_sayExpressively(self,params):
        language = params.get('lang','')
        msg = params.get('msg','')

        if self.volume_set==False:
            self.setSpeakerVolume(75)
            self.volume_set = True

        #if language is '' and msg is not '':
        #    # Try to detect language
        #    apiKey = os.environ['LANGUAGE_DETECT_APIKEY']
        #    if apiKey is not '':
        #        try:
        #            langCode = detectlanguage.simple_detect(msg)
        #            langDetails = pycountry.languages.get(langCode)
        #            language = str(langDetails.name)
        #            print 'Identified Language is ', language
        #        except:
        #            print "Exception occured while execution ", sys.exc_info()

        if (language is '') and (self.language is None):
            # Try to detect language
            language = 'English'
        else:
            if self.language is not None:
                language = self.language

        if language is not '' and msg is not '':
            proxy = self.getAnimatedSayProxy()
            if proxy is not None:
                self.set_language(language)
                # set the local configuration
                configuration = {"bodyLanguageMode":"contextual"}
                id= proxy.post.say(msg,configuration)
                return [id,proxy]
        return []

    def setSpeakerVolume(self,volume):
        try:
            proxy = self.getAudioDeviceProxy()
            if proxy is not None:
                id = proxy.setOutputVolume(volume)
        except:
            print "Set speaker volume occured : ", sys.exc_info()

    def action_setSpeakerVolume(self,params):
        volume = params.get('volume',50)
        proxy = self.getAudioDeviceProxy()
        if proxy is not None:
            id = proxy.post.setOutputVolume(volume)
            return [id,proxy]
        return []

    def action_goToPosture(self,params):
        posture = params.get('posture','')
        if posture is not '':
            proxy = self.getPostureProxy()
            if proxy is not None:
                id = proxy.post.goToPosture(posture, 1.0)
                return [id,proxy]
        return []

    def moveInit(self):
        # Send NAO to Pose Init
        postureProxy = self.getPostureProxy()

        postureProxy.goToPosture("Stand", 0.5)
        # Initialize move process.
        motionProxy = self.getMotionProxy()
        motionProxy.moveInit()

    def action_trackPeople(self,params):
        x = params.get('x',0.0)
        y = params.get('y',0.0)
        theta = params.get('theta',0.0)
        self.moveInit()
        #proxy = self.getMotionProxy()
        memory = self.getMemoryProxy()
        tracker = self.getTrackerProxy()
        if memory is not None and tracker is not None:
            people = PeopleTracker.PeopleTracker(tracker,memory,x,y,theta)
            people.start()
            
            # 1 minute timeout
            timeout = time.time() + 60*1;

            while True:
                time.sleep(1)
                if people.getTargetReached() or people.getTargetLost():
                    break;
                if time.time() > timeout:
                    # Timeout reached
                    print "Tracker Time out reached"
                    break;

            people.stop()

    def action_moveTo(self,params):
        #x = float(params.get('x','0.0').encode('utf-8'))
        #y = float(params.get('y','0.0').encode('utf-8'))
        #theta = float(params.get('theta','0.0').encode('utf-8'))
        x = params.get('x',0.0)
        y = params.get('y',0.0)
        theta = params.get('theta',0.0)
        self.moveInit()
        proxy = self.getMotionProxy()
        if proxy is not None:
            id = proxy.post.moveTo(x,y,theta)
            return [id,proxy]
        return []

    def action_rest(self,params):
        proxy = self.getMotionProxy()
        if proxy is not None:
            id = proxy.post.rest()
            return [id,proxy]
        return []

    def action_wakeUp(self,params):
        proxy = self.getMotionProxy()
        if proxy is not None:
            id = proxy.post.wakeUp()
            return [id,proxy]
        return []

    def action_moveToward(self,params):
        #x = float(params.get('x','0.0').encode('utf-8'))
        #y = float(params.get('y','0.0').encode('utf-8'))
        #theta = float(params.get('theta','0.0').encode('utf-8'))
        x = params.get('x',0.0)
        y = params.get('y',0.0)
        theta = params.get('theta',0.0)
        self.moveInit()
        proxy = self.getMotionProxy()
        if proxy is not None:
            id = proxy.post.moveToward(x,y,theta)
            return [id,proxy]
        return []

    def action_lookAt(self,params):
        x = params.get('x',0.0)
        y = params.get('y',0.0)
        z = params.get('z',0.0)
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
            id = proxy.post.lookAt([x, y, z], frame, maxSpeed, useWholeBody)
            return [id,proxy]
        return []

    def executeAction(self,name,params):
        method = getattr(self,name)
        if method is not None:
            arg_spec = inspect.getargspec(method)
            #print arg_spec.args
            print 'Method', name, "Params", params
            return method(params)
        else:
            print 'Method', name, "not found!"
        return []

    def createArg(self, value, placeHolder=False, type='string'):
        arg = dict({})
        arg['value'] = value
        arg['place_holder'] = placeHolder
        arg['type'] = type
        return arg

    def getCapabilities(self):
        # action -> function mapping
        installedBehaviors = self.getInstalledBehaviors()
        cap_dict = dict({})
        for insBehavior in installedBehaviors:
            behaviorStr = insBehavior.replace('.lastUploadedChoregrapheBehavior/','',1)
            cap_dict[behaviorStr] = {'function':'action_executeBehavior','args':{'name':self.createArg(behaviorStr)}}

        cap_dict['Look At'] = {'function':'action_lookAt',
                                       'args':{'x':self.createArg(0.0,True,'float'),
                                               'y':self.createArg(0.0,True,'float'),
                                               'z':self.createArg(0.0,True,'float'),
                                               'frame':self.createArg('torso',True)}}

        cap_dict['Move To'] = {'function':'action_moveTo',
                                       'args':{'x':self.createArg(0.0,True,'float'),
                                               'y':self.createArg(0.0,True,'float'),
                                               'theta':self.createArg(0.0,True,'float')}}

        cap_dict['Track People'] = {'function':'action_trackPeople',
                                       'args':{'x':self.createArg(0.0,True,'float'),
                                               'y':self.createArg(0.0,True,'float'),
                                               'theta':self.createArg(0.0,True,'float')}}

        cap_dict['Move Toward'] = {'function':'action_moveToward',
                                       'args':{'x':self.createArg(0.0,True,'float'),
                                               'y':self.createArg(0.0,True,'float'),
                                               'z':self.createArg(0.0,True,'float')}}

        cap_dict['Take Rest'] = {'function':'action_rest',
                                       'args':{'val':self.createArg(0.0,False,'float')}}

        cap_dict['Wake up'] = {'function':'action_wakeUp',
                                       'args':{'val':self.createArg(0.0,False,'float')}}

        cap_dict['Set Language'] = {'function':'action_setLanguage',
                                       'args':{'lang':self.createArg(0.0,True,'string')}}

        cap_dict['Say Expressively'] = {'function':'action_sayExpressively',
                              'args':{'lang':self.createArg('',True),
                                      'msg':self.createArg('Hello!',True)}}

        standardPostures = ['Sit Relax','LyingBelly','LyingBack','Stand','Crouch','Sit']
        for standardPosture in standardPostures:
            cap_dict[standardPosture]= {'function':'action_goToPosture','args':{'posture':self.createArg(standardPosture)}}

        return cap_dict

# if __name__ == "__main__":
#     a = NaoBehaviorModule('127.0.0.1',57105)
#     msg = 'ありがとうございました。'
#     say_param = {'lang':'Japanese','msg':msg}
#
#     behaviors = a.getCapabilities()
#     # for i in cap:
#     #     print i, str(cap[i])
#
#     import robot_behavior_pb2
#     behaviorModule = robot_behavior_pb2.RobotBehaviorModule()
#     behaviorModule.name = "dummy"
#
#     behaviorModule.responder.Host = "ip"
#     behaviorModule.responder.Port = 1000
#
#     for behavior in behaviors:
#         print "Creating behavior description message", behavior
#         desc = behaviorModule.behaviors.add()
#         desc.name = behavior
#         desc.function_name = behaviors[behavior]['function']
#         args = behaviors[behavior]['args']
#         for arg in args:
#             desc_arg = desc.arg.add()
#             desc_arg.name = arg
#             desc_arg.place_holder = args[arg]['place_holder']
#             desc_arg.value = str(args[arg]['value'])
#             desc_arg.type = args[arg]['type']
#         desc.type = robot_behavior_pb2.BehaviorDescription.Blocking
#         desc.state = robot_behavior_pb2.BehaviorDescription.Idle
#
#     print behaviorModule
    # a.executeAction('action_goToPosture',{'posture':'Stand'})
    # a.executeAction('action_sayExpressively',say_param)
    # a.executeAction('action_goToPosture',{'posture':'Crouch'})
    # a.executeAction('action_lookAt',{'x':'0','y':'0.5','z':'0.5','frame':'torso'})
    # a.executeAction('action_lookAt',{'x':'0','y':'0.0','z':'0.2','frame':'torso'})