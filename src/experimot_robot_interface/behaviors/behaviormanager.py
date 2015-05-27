# -*- encoding: UTF-8 -*- 
import os
import sys
import time
import argparse
import thread
import NaoBehaviorModule
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
# JSON
import json

def parse_and_execute(behaviorModule,recv_str):
    ret = True
    try:
      if behaviorModule is not None:
          out = json.loads(recv_str)
          print "Name" , out["BehaviorName"]
          print "Function Name" , out["FunctionName"]
          # Compose Parameter Dictionary
          paramDict = dict({})
          params = out['Parameters']
          for param in params:
              print param, params[param], params[param]['value']
              type = params[param]['type']
              key = str(param.encode('utf-8'))
              value = str(params[param]['value'].encode('utf-8'))
              #value = params[param]['value']
              if(type == 'float'):
                  paramDict[key] = float(value)
              else:
                  paramDict[key] = value
          behaviorModule.executeAction(out["FunctionName"],paramDict)
    except:
        ret = False
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
        behavior = socket.recv()
        print("Received request: %s" % behavior)

        try:
            response = "Execution successful"
            if parse_and_execute(behaviorModule,behavior) is not True:
                response = "Execution Failed"
            socket.send(response)
        except:
            print "Exception occured while execution ", sys.exc_info()
            socket.send("Execution Failed")

        #  Do some 'work'
        time.sleep(0.5)

    print "quitting ... "

if __name__ == "__main__":
  try:

      from langdetect import detect
      print detect(u"Cosa vuoi mangiare?")
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
              module = NaoBehaviorModule.NaoBehaviorModule(ROBOTIP,PORT)
              behaviors = module.getCapabilities()
              #parameter_utils.register_behaviors(node,paramServer,["crouch","stand","hand_wave","greet","wish","introduction"])
              parameter_utils.register_behaviors(node,paramServer,behaviors)
              thread.start_new_thread(behavior_server,(module,BEHAVIOR_IP,BEHAVIOR_PORT))
      else:
          print "Start locally"

      time.sleep(1)

      # do nothing 
      while 1:
        pass
  except:
      print "Exception occured : ", sys.exc_info()
    
  raw_input("Press enter to continue ... ")