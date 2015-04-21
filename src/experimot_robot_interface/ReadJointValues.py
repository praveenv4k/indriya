__author__ = 'Praveenkumar'

import os
import zmq
import sys
import time
from naoqi import ALProxy

from os.path import dirname
from os.path import abspath

dev = os.environ["DEV_SDK_ROOT"]
dir1 = os.path.join(dev,"experimot","scripts","msgs")

sys.path.append(dir1)

import joint_value_map_pb2

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
    msg = joint_value_map_pb2.JointValueVector()
    for i in range(0,25):
        elem = msg.JointValues.add()
        elem.id = i
        elem.value = float(rave_joint[i])
    str = msg.SerializeToString()
    sock.send_string(head,zmq.SNDMORE)
    sock.send_string(str)

def reorder_joint_values(row):
    data = []
    for i in range(0,25):
        data.append(row[jMap[i]])
    print data
    return data

def recordData(memory):
    """ Record the data from ALMemory.
    Returns a matrix of values
    """
    value = memory.getListData(SENSOR_TO_LOG_LIST)
    return value

if __name__ == "__main__":
    port = "5563"

    context = zmq.Context()
    socket = context.socket(zmq.PUB)
    socket.bind("tcp://*:%s" % port)
    header = "RSP"

    # Real Robot
    ROBOT_IP = "169.254.123.55"
    PORT = 9559

    # Simulated Robot
    #ROBOT_IP = "127.0.0.1"
    #PORT = 60170

    print "Publishing data ..."
    memory = ALProxy("ALMemory", ROBOT_IP, PORT)
    while 1:
        value = recordData(memory)
        print value
        send_joint_values(socket,header,value)
        time.sleep(0.1)