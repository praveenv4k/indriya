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
import math

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

def human_to_nao(human_angle):
    human_min = 20
    human_max = 170
    nao_min = 3
    nao_max = 88
    human_range = human_max - human_min
    nao_range = nao_max - nao_min

    value = float(human_angle)
    if value > human_max:
        value = human_max
    elif value < human_min:
        value = human_min
    # find the scaled version
    diff = value - human_min
    #new_value = nao_min + ((diff/human_range)*nao_range)
    new_value = nao_max - ((diff/human_range)*nao_range)
    return math.radians(new_value)

#############################################################################################################
# Behavior server - A Behavior request/response server
def imitate_client(behaviorModule,ip,port):
    context = zmq.Context()
    socket = context.socket(zmq.REQ)
    socket.connect(("%s:%d" % (ip,port)))
    print "Connected to: %s,%d" % (ip,port)
    while True:
        #  Wait for next request from client
        socket.send('humans')
        humansStr = socket.recv()
        humans = json.loads(humansStr)
        if len(humans) > 0:
            human = humans[0]
            id = int(str(human['Id']).encode('utf-8'))
            socket.send('body/%d' % id)
            bodyStr = socket.recv()
            body = json.loads(bodyStr)
            joints = body['Joints']
            
            if len(joints) > 0 :
                angles = dict({})
                for joint in joints:
                    angle = float(str(joint['Angle']).encode('utf-8'))
                    type = int(str(joint['Type']).encode('utf-8'))
                    angles[type] = angle
                    # Get Elbow Right value
                    if type is 9:
                        nao_angle = human_to_nao(angle)
                        behaviorModule.set_jointAngles(["RElbowRoll"],[nao_angle])
                        print 'Angle: ', nao_angle
                #print angles
                #print '**************************************************'
        # try:
        #     response = "Execution successful"
        #     if parse_and_execute(behaviorModule,behavior) is not True:
        #         response = "Execution Failed"
        #     socket.send(response)
        # except:
        #     print "Exception occured while execution ", sys.exc_info()
        #     socket.send("Execution Failed")

        #  Do some 'work'
        time.sleep(0.5)

    print "quitting ... "

#############################################################################################################
# Behavior server - A Behavior request/response server
import param_pb2

def imitate_subscriber(behaviorModule,ip,port,topic):
    context = zmq.Context()
    socket = context.socket(zmq.SUB)
    socket.connect(("%s:%d" % (ip,port)))
    socket.setsockopt(zmq.SUBSCRIBE, topic)
    print "Connected to: %s,%d" % (ip,port)
    while True:
        #  Wait for next request from client
        topic2 = socket.recv()
        msg = socket.recv()
        print topic2, msg
        paramList = param_pb2.ParamList()
        paramList.ParseFromString(msg)
        names = []
        values = []
        for param in paramList.param:
            names.append(str(param.key))
            values.append(float(param.value))
        if len(names)>0:
            behaviorModule.set_jointAngles(names,values)
        #print paramList
        time.sleep(0.2)

    print "quitting ... "


if __name__ == "__main__":
  try:
      #msg = "おはようございます！"
      #print msg

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
              CTX_IP = parameter_utils.getParam(node,"ContextClientHost", "tcp://localhost")
              CTX_PORT = int(parameter_utils.getParam(node,"ContextServerPort", "5800"))
              module = NaoBehaviorModule.NaoBehaviorModule(ROBOTIP,PORT)
              behaviors = module.getCapabilities()
              #parameter_utils.register_behaviors(node,paramServer,["crouch","stand","hand_wave","greet","wish","introduction"])
              parameter_utils.register_behaviors(node,paramServer,behaviors)
              #thread.start_new_thread(imitate_client,(module,CTX_IP,CTX_PORT))
              subscriber = parameter_utils.getSubscriberInfo(node,'ParamList')
              thread.start_new_thread(imitate_subscriber,(module,str(subscriber.host),int(subscriber.port),str(subscriber.topic)))
      else:
          print "Start locally"

      time.sleep(1)

      # do nothing 
      while 1:
        pass
  except:
      print "Exception occurred : ", sys.exc_info()
    
  raw_input("Press enter to continue ... ")