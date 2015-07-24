__author__ = 'Praveenkumar'

import os
import zmq
import sys
import time
import argparse
import thread
import json
from naoqi import ALProxy

from os.path import dirname
from os.path import abspath

dev = os.environ["INDRIYA_ROOT"]
dir1 = os.path.join(dev,"scripts","msgs")

sys.path.append(dir1)

import joint_value_map_pb2

useSensors = False

#ROBOT_IP = "nao.local"
#ROBOT_IP = "127.0.0.1"

# SENSOR_TO_LOG_LIST = ['DCM/Time',
#                                'DCM/CycleTime',
#                                'Device/SubDeviceList/Head/Touch/Middle/Sensor/Value',
#                                "Device/SubDeviceList/HeadPitch/Position/Sensor/Value",
#                                "Device/SubDeviceList/HeadYaw/Position/Sensor/Value",
#                                "Device/SubDeviceList/LAnklePitch/Position/Sensor/Value",
#                                "Device/SubDeviceList/LAnkleRoll/Position/Sensor/Value",
#                                "Device/SubDeviceList/LElbowRoll/Position/Sensor/Value",
#                                "Device/SubDeviceList/LElbowYaw/Position/Sensor/Value",
#                                "Device/SubDeviceList/LHand/Position/Sensor/Value",
#                                "Device/SubDeviceList/LHipPitch/Position/Sensor/Value",
#                                "Device/SubDeviceList/LHipRoll/Position/Sensor/Value",
#                                "Device/SubDeviceList/LHipYawPitch/Position/Sensor/Value",
#                                "Device/SubDeviceList/LKneePitch/Position/Sensor/Value",
#                                "Device/SubDeviceList/LShoulderPitch/Position/Sensor/Value",
#                                "Device/SubDeviceList/LShoulderRoll/Position/Sensor/Value",
#                                "Device/SubDeviceList/LWristYaw/Position/Sensor/Value",
#                                "Device/SubDeviceList/RAnklePitch/Position/Sensor/Value",
#                                "Device/SubDeviceList/RAnkleRoll/Position/Sensor/Value",
#                                "Device/SubDeviceList/RElbowRoll/Position/Sensor/Value",
#                                "Device/SubDeviceList/RElbowYaw/Position/Sensor/Value",
#                                "Device/SubDeviceList/RHand/Position/Sensor/Value",
#                                "Device/SubDeviceList/RHipPitch/Position/Sensor/Value",
#                                "Device/SubDeviceList/RHipRoll/Position/Sensor/Value",
#                                "Device/SubDeviceList/RKneePitch/Position/Sensor/Value",
#                                "Device/SubDeviceList/RShoulderPitch/Position/Sensor/Value",
#                                "Device/SubDeviceList/RShoulderRoll/Position/Sensor/Value",
#                                "Device/SubDeviceList/RWristYaw/Position/Sensor/Value",
#                                "Device/SubDeviceList/InertialSensor/AccelerometerX/Sensor/Value",
#                                "Device/SubDeviceList/InertialSensor/AccelerometerY/Sensor/Value",
#                                "Device/SubDeviceList/InertialSensor/AccelerometerZ/Sensor/Value",
#                                "Device/SubDeviceList/InertialSensor/GyroscopeX/Sensor/Value",
#                                "Device/SubDeviceList/InertialSensor/GyroscopeY/Sensor/Value",
#                                "Device/SubDeviceList/InertialSensor/AngleX/Sensor/Value",
#                                "Device/SubDeviceList/InertialSensor/AngleY/Sensor/Value",
#                                "Device/SubDeviceList/LFoot/FSR/FrontLeft/Sensor/Value",
#                                "Device/SubDeviceList/LFoot/FSR/FrontRight/Sensor/Value",
#                                "Device/SubDeviceList/LFoot/FSR/RearLeft/Sensor/Value",
#                                "Device/SubDeviceList/LFoot/FSR/RearRight/Sensor/Value",
#                                "Device/SubDeviceList/RFoot/FSR/FrontLeft/Sensor/Value",
#                                "Device/SubDeviceList/RFoot/FSR/FrontRight/Sensor/Value",
#                                "Device/SubDeviceList/RFoot/FSR/RearLeft/Sensor/Value",
#                                "Device/SubDeviceList/RFoot/FSR/RearRight/Sensor/Value"]

jMap = {0:1,1:0,2:9,3:8,4:7,5:10,6:2,7:3,8:11,
        9:12,10:5,11:4,12:13,13:6,14:20,15:19,
        16:21,17:14,18:15,19:22,20:23,21:17,22:16,23:24,24:18}

SENSOR_TO_LOG_LIST = ["Device/SubDeviceList/HeadPitch/Position/Sensor/Value",
                        "Device/SubDeviceList/HeadYaw/Position/Sensor/Value",
                        "Device/SubDeviceList/LAnklePitch/Position/Sensor/Value",
                        "Device/SubDeviceList/LAnkleRoll/Position/Sensor/Value",
                        "Device/SubDeviceList/LElbowRoll/Position/Sensor/Value",
                        "Device/SubDeviceList/LElbowYaw/Position/Sensor/Value",
                        "Device/SubDeviceList/LHand/Position/Sensor/Value",
                        "Device/SubDeviceList/LHipPitch/Position/Sensor/Value",
                        "Device/SubDeviceList/LHipRoll/Position/Sensor/Value",
                        "Device/SubDeviceList/LHipYawPitch/Position/Sensor/Value",
                        "Device/SubDeviceList/LKneePitch/Position/Sensor/Value",
                        "Device/SubDeviceList/LShoulderPitch/Position/Sensor/Value",
                        "Device/SubDeviceList/LShoulderRoll/Position/Sensor/Value",
                        "Device/SubDeviceList/LWristYaw/Position/Sensor/Value",
                        "Device/SubDeviceList/RAnklePitch/Position/Sensor/Value",
                        "Device/SubDeviceList/RAnkleRoll/Position/Sensor/Value",
                        "Device/SubDeviceList/RElbowRoll/Position/Sensor/Value",
                        "Device/SubDeviceList/RElbowYaw/Position/Sensor/Value",
                        "Device/SubDeviceList/RHand/Position/Sensor/Value",
                        "Device/SubDeviceList/RHipPitch/Position/Sensor/Value",
                        "Device/SubDeviceList/RHipRoll/Position/Sensor/Value",
                        "Device/SubDeviceList/RKneePitch/Position/Sensor/Value",
                        "Device/SubDeviceList/RShoulderPitch/Position/Sensor/Value",
                        "Device/SubDeviceList/RShoulderRoll/Position/Sensor/Value",
                        "Device/SubDeviceList/RWristYaw/Position/Sensor/Value"]

JOINT_NAMES = ["HeadPitch",
                        "HeadYaw",
                        "LAnklePitch",
                        "LAnkleRoll",
                        "LElbowRoll",
                        "LElbowYaw",
                        "LHand",
                        "LHipPitch",
                        "LHipRoll",
                        "LHipYawPitch",
                        "LKneePitch",
                        "LShoulderPitch",
                        "LShoulderRoll",
                        "LWristYaw",
                        "RAnklePitch",
                        "RAnkleRoll",
                        "RElbowRoll",
                        "RElbowYaw",
                        "RHand",
                        "RHipPitch",
                        "RHipRoll",
                        "RKneePitch",
                        "RShoulderPitch",
                        "RShoulderRoll",
                        "RWristYaw"]

POS_TO_LOG_LIST = ["Motion/Walk/AbsDistanceX",
                        "Motion/Walk/AbsDistanceY",
                        "Motion/Walk/AbsDistanceTheta"]

# def recordData(nao_ip):
#     """ Record the data from ALMemory.
#     Returns a matrix of values
#
#     """
#     print "Recording data ..."
#     memory = ALProxy("ALMemory", nao_ip, 9559)
#     data = list()
#     for i in range (1, 100):
#         line = list()
#         for key in ALMEMORY_KEY_NAMES:
#             value = memory.getData(key)
#             line.append(value)
#         data.append(line)
#         time.sleep(0.05)
#     return data

def send_joint_values(sock,head,vals):
    rave_joint = reorder_joint_values(vals)
    #if useSensors==True:
        #rave_joint = reorder_joint_values(vals)
    #else:
        #rave_joint = vals
    msg = joint_value_map_pb2.JointValueVector()
    for i in range(0,25):
        elem = msg.JointValues.add()
        elem.id = i
        elem.value = float(rave_joint[i])
    str = msg.SerializeToString()
    sock.send_string(head,zmq.SNDMORE)
    sock.send_string(str)

def send_position_values(sock,head,vals):
    str = json.dumps(vals)
    sock.send_string(head,zmq.SNDMORE)
    sock.send_string(str)

def reorder_joint_values(row):
    data = []
    for i in range(0,25):
        data.append(row[jMap[i]])
    print data
    return data

def recordData(memory,motion):
    """ Record the data from ALMemory.
    Returns a matrix of values
    """
    names         = "JointActuators"
    if useSensors==True:
        joint = memory.getListData(SENSOR_TO_LOG_LIST)
    else:
        joint = motion.getAngles(JOINT_NAMES,useSensors)
    
    print len(joint)
    #pos = memory.getListData(POS_TO_LOG_LIST)
    pos = motion.getRobotPosition(useSensors)
    return [joint,pos]

if __name__ == "__main__":
    # Real Robot
    ROBOT_IP = "192.168.11.2"
    ROBOT_PORT = 9559

    PUB_IP = "tcp://*"
    PUB_PORT = "5563"
    PUB_TOPIC = "RSP"
    try:
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
                  ROBOT_IP = parameter_utils.getParam(node,"ROBOTIP", "127.0.0.1")
                  ROBOT_PORT =  int(parameter_utils.getParam(node,"ROBOTPORT", "9559"))
                  pub = parameter_utils.getPublisherInfo(node,"JointValueVector")
                  if pub != None:
                    PUB_IP = pub.host.encode('utf-8')
                    PUB_PORT = pub.port
                    PUB_TOPIC = pub.topic.encode('utf-8')
                  pub2 = parameter_utils.getPublisherInfo(node,"AbsolutePosition")
                  if pub2 != None:
                    PUB2_IP = pub2.host.encode('utf-8')
                    PUB2_PORT = pub2.port
                    PUB2_TOPIC = pub2.topic.encode('utf-8')
        else:
              print "Start locally"

        if ROBOT_IP == '127.0.0.1':
            useSensors = False
        else:
            useSensors = True

        context = zmq.Context()
        socket = context.socket(zmq.PUB)
        socket.bind("%s:%s" % (PUB_IP,PUB_PORT))

        socket2 = context.socket(zmq.PUB)
        socket2.bind("%s:%s" % (PUB2_IP,PUB2_PORT))

        print "Publishing data ..."
        memory = ALProxy("ALMemory", ROBOT_IP, ROBOT_PORT)
        motion = ALProxy("ALMotion", ROBOT_IP, ROBOT_PORT)
        while 1:
            value = recordData(memory,motion)
            print value
            send_joint_values(socket,PUB_TOPIC,value[0])
            send_position_values(socket2,PUB2_TOPIC,value[1])
            time.sleep(0.08)
    except:
      print "Exception occured : ", sys.exc_info()

    raw_input("Press enter to continue ... ")