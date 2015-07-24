__author__ = 'Praveenkumar'

import os
import zmq
import sys
import time
import argparse
import thread
import json
import math
from naoqi import ALProxy
import transformations


from os.path import dirname
from os.path import abspath

dev = os.environ["INDRIYA_ROOT"]
dir1 = os.path.join(dev,"scripts","msgs")

sys.path.append(dir1)

import pose_v_pb2

def getMotionProxy(ip,port):
        return ALProxy("ALMotion", ip, port)

def getPostureProxy(ip,port):
        return ALProxy("ALRobotPosture", ip, port)

def getMemoryProxy(ip,port):
        return  ALProxy("ALMemory", ip, port)

def moveInit(motion,posture):
        posture.goToPosture("Stand", 0.5)
        # Initialize move process.
        motion.moveInit()

def action_move(motion,posture,x,y,theta):
        #moveInit(motion,posture)
        if motion is not None:
            id = motion.move(x,y,theta)
            return [id,motion]
        return []


def control_loop(ip,port):
    motion = getMotionProxy(ip,port)
    posture = getPostureProxy(ip,port)
    memory = getMemoryProxy(ip,port)
    moveInit(motion,posture)

    names         = "Body"
    useSensors    = False

    for i in range(0,5):
        angles = motion.getAngles(names,useSensors)
        print angles
        position = motion.getRobotPosition(useSensors)
        print position
    #ret = action_moveTo(motion,posture,0.6,0.5,math.pi/2)
    for i in range(0,10):
        action_move(motion,posture,0.5,0,0)
        print i
        time.sleep(0.8)
    motion.stopMove()
    posture.goToPosture("Stand", 0.5)

if __name__ == "__main__":
    # Real Robot
    ROBOT_IP = "127.0.0.1"
    ROBOT_PORT = 60017

    #alconnman = ALProxy("ALConnectionManager", ROBOT_IP, ROBOT_PORT)

    #Scanning is required to update the services list
    #alconnman.scan()
    #services = alconnman.services()

    try:
        control_loop(ROBOT_IP,ROBOT_PORT)
    except:
      print "Exception occured : ", sys.exc_info()

    raw_input("Press enter to continue ... ")