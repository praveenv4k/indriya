#!/usr/bin/env python
# -*- coding: utf-8 -*-
__author__ = 'Praveenkumar VASUDEVAN'
 
import os
import sys
import time
import argparse
import thread
import PepperBehaviorModule
from os.path import dirname
from os.path import abspath

dev = os.environ["INDRIYA_ROOT"]
dir1 = os.path.join(dev,"scripts","msgs")
dir2 = os.path.join(dev,"scripts","indriya_robot_interface")

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
# JSON
import json

state = 0
cmd_arrived = False
stop_arrived = False
reset_arrived = False
cmd_args = None

CMD_START_REQ = "START_REQ"
CMD_RUN_REQ   = "RUN_REQ"
CMD_STS_REQ   = "STS_REQ"
CMD_STOP_REQ  = "STOP_REQ"
CMD_RESET_REQ = "RESET_REQ"

STS_RUN       = "RUN" 
STS_RUN_READY = "RUN_READY" 
STS_WAIT_ARG  = "WAIT_ARG"
STS_IDLE      = "IDLE"
STS_ERR       = "ERR"
STS_STOP      = "STOP"
STS_UNKNOWN   = "UNKNOWN"

STATE_IDLE      = 0
STATE_WAIT_ARG  = 1
STATE_RUN       = 2
STATE_RUN_READY = 3
STATE_ERR       = 4
STATE_STOP      = 5

def sts_from_state(state):
    if state == STATE_IDLE:
        return STS_IDLE
    if state == STATE_WAIT_ARG:
        return STS_WAIT_ARG
    if state == STATE_RUN:
        return STS_RUN
    if state == STATE_RUN_READY:
        return STS_RUN_READY
    if state == STATE_ERR:
        return STS_ERR
    if state == STATE_STOP:
        return STS_STOP
    return STS_UNKNOWN

def parse_and_execute(behaviorModule,recv_str):
    ret = []
    try:
      if behaviorModule is not None:
          out = json.loads(recv_str)
          ret = parse_and_execute_json(behaviorModule,out)
    except:
      ret = []
      print "Exception occured while execution ", sys.exc_info()
    return ret

def parse_and_execute_json(behaviorModule,json_obj):
    ret = []
    try:
      if behaviorModule is not None:
          out = json_obj
          print "Name" , out["BehaviorName"]
          print "Function Name" , out["FunctionName"]
          # Compose Parameter Dictionary
          paramDict = dict({})
          params = out['Parameters']
          for param in params:
              print param, params[param], params[param]['value']
              type = str(params[param]['type'].encode('utf-8'))
              key = str(param.encode('utf-8'))
              #value = params[param]['value']
              if(type == 'float'):
                  valueStr = params[param]['value']
                  value = 0.0
                  if isinstance(valueStr,basestring):
                    value = float(valueStr.encode('utf-8'))
                  else:
                    value = float(params[param]['value'])
                  paramDict[key] = value
              else:
                  value = str(params[param]['value'].encode('utf-8'))
                  paramDict[key] = value
          ret = behaviorModule.executeAction(out["FunctionName"],paramDict)
    except:
        ret = []
        print "Exception occured while execution ", sys.exc_info()
    return ret

#############################################################################################################
# Behavior server - A Behavior request/response server
def behavior_server(behaviorModule,ip,port):
    context = zmq.Context()
    socket = context.socket(zmq.REP)
    socket.bind(("%s:%d" % (ip,port)))
    print "Server bound: %s,%d" % (ip,port)
    while True:
        #  Wait for next request from client
        try:
            behavior = socket.recv(zmq.NOBLOCK)
            print("Received request: %s" % behavior)

            try:
                response = "Execution successful"
                ret = parse_and_execute(behaviorModule,behavior)
                if len(ret) == 0:
                    response = "Execution Failed"
                else:
                    print ret
                socket.send(response)
            except:
                print "Exception occured while execution ", sys.exc_info()
                socket.send("Execution Failed")

        except zmq.ZMQError as e:
            if e.errno == zmq.EAGAIN:
                #print "Message not ready", e.errno
                pass
        #  Do some 'work'
        time.sleep(0.5)

    print "quitting ... "

#############################################################################################################
# Behavior server - A Behavior request/response server
def behavior_server2(behaviorModule,ip,port):
    state = STATE_IDLE
    param = None
    current = []
    prev_req = None
    context = zmq.Context()
    socket = context.socket(zmq.REP)
    socket.bind(("%s:%d" % (ip,port)))
    print "Server bound: %s,%d" % (ip,port)
    while True:
        #  Wait for next request from client
        try:
            req = socket.recv(zmq.NOBLOCK)
            #print("Received request: %s" % req)

            if(prev_req != req):
                print("Received request: %s" % req)
                prev_req = req

            resp = None
            msg = None

            # TODO: Handle stop here itself
            if (req == CMD_STOP_REQ):
                id = -1
                proxy = None
                if len(current) == 2:
                    id = current[0]
                    proxy = current[1]
                else:
                    state = STATE_ERR
                    msg = "No active action running in the robot"

                if proxy is not None and id is not -1:
                    if proxy.isRunning(id):
                        # if the proxy is a ALBehaviorProxy we just invoke stopAllBehaviors
                        methods =  proxy.getMethodList()
                        if "stopAllBehaviors" in methods:
                            stopAllBehaviors = getattr(proxy,"stopAllBehaviors")
                            stopAllBehaviors()
                        elif "stopMove" in methods:
                            stopMove = getattr(proxy,"stopMove")
                            stopMove()
                        #stopAllBehaviors = getattr(proxy,"stopAllBehaviors")
                        #if stopAllBehaviors is not None:
                        #    print stopAllBehaviors
                        #    stopAllBehaviors()
                            
                        proxy.stop(id)
                        waitTime = 0
                        while proxy.isRunning(id):
                            print "Waiting for execution completion!", waitTime
                            time.sleep(0.1)
                            waitTime = waitTime + 0.1
                            if waitTime > 1:
                                print "Timeout"
                        state = STATE_IDLE
                        msg = "Idle"
                    else:
                        state = STATE_IDLE
                        msg = "Idle"


            if(state == STATE_IDLE):
                if param is not None:
                    param = None
                if(req == CMD_START_REQ):
                    state = STATE_WAIT_ARG
                    msg = "Waiting for arguments"

            elif(state== STATE_WAIT_ARG):
                try:
                    param = json.loads(req)
                    state = STATE_RUN_READY
                    msg = "Ready to run"
                except:
                    print "Unexpected request", req
                    state = STS_ERR
                    msg = "Unexpected request. Expecting arguments"

            elif(state== STATE_RUN_READY):
                if(req == CMD_RUN_REQ):
                    if param is not None:
                        current = parse_and_execute_json(behaviorModule,param)
                        if len(current) == 0:
                            state = STATE_ERR
                            msg = "Run init failed"
                        else:
                            state = STATE_RUN
                            msg = "Running"
                    else:
                        state = STATE_ERR
                        msg = "Invalid arguments"

            elif(state== STATE_RUN):
                id = -1
                proxy = None
                if len(current) == 2:
                    id = current[0]
                    proxy = current[1]
                else:
                    state = STATE_ERR
                    msg = "No active action running in the robot"

                if proxy is not None and id is not -1:
                    if proxy.isRunning(id):
                        if(req == CMD_STOP_REQ):
                            proxy.stop(id)
                            state = STATE_IDLE
                            msg = "Idle"
                    else:
                        state = STATE_IDLE
                        msg = "Idle"

            elif(state==STS_ERR):
                if(req == CMD_RESET_REQ):
                    state = STATE_IDLE
                    msg = "Idle"

            resp = sts_from_state(state)
            data = {}
            data['resp'] = resp
            data['msg'] = msg
            json_data = json.dumps(data)
            socket.send(json_data)

        except zmq.ZMQError as e:
            if e.errno == zmq.EAGAIN:
                #print "Message not ready", e.errno
                pass
        #  Do some 'work'
        time.sleep(0.1)

    print "quitting ... "

if __name__ == "__main__":
  try:
      # from langdetect import detect
      # print detect(u"Cosa vuoi mangiare?")
      ROBOTIP = "127.0.0.1"
      PORT = 55241
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
              PORT =  int(parameter_utils.getParam(node,"ROBOTPORT", "9559"))
              BEHAVIOR_PORT = int(parameter_utils.getParam(node,"RequestServerPort", "5590"))
              BEHAVIOR_IP = parameter_utils.getParam(node,"RequestServerIP", "*")
              ROBOTNAME = parameter_utils.getParam(node,"ROBOTNAME", "ROBOTX")
              module = NaoBehaviorModule.NaoBehaviorModule(ROBOTIP,PORT)
              behaviors = module.getCapabilities()
              #parameter_utils.register_behaviors(node,paramServer,["crouch","stand","hand_wave","greet","wish","introduction"])
              parameter_utils.register_behaviors(node,ROBOTNAME,paramServer,behaviors)
              thread.start_new_thread(behavior_server2,(module,BEHAVIOR_IP,BEHAVIOR_PORT))
      else:
          print "Start locally"

      time.sleep(1)

      # do nothing 
      while 1:
        pass
  except:
      print "Exception occured : ", sys.exc_info()
    
  raw_input("Press enter to continue ... ")