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


POS_TO_LOG_LIST = ["Motion/Walk/AbsDistanceX",
                   "Motion/Walk/AbsDistanceY",
                   "Motion/Walk/AbsDistanceTheta"]

stop = False
gPose = None
gPoseFiltered = None

dataNamesList = ["DCM/Time",
                "Device/SubDeviceList/InertialSensor/AngleX/Sensor/Value",
                "Device/SubDeviceList/InertialSensor/AngleY/Sensor/Value",
                "Device/SubDeviceList/InertialSensor/AngleZ/Sensor/Value",
                "Device/SubDeviceList/InertialSensor/GyroscopeX/Sensor/Value", 
                "Device/SubDeviceList/InertialSensor/GyroscopeY/Sensor/Value",
                "Device/SubDeviceList/InertialSensor/GyroscopeZ/Sensor/Value",
                "Device/SubDeviceList/InertialSensor/AccelerometerX/Sensor/Value", 
                "Device/SubDeviceList/InertialSensor/AccelerometerY/Sensor/Value",
                "Device/SubDeviceList/InertialSensor/AccelerometerZ/Sensor/Value"]

def getHeading(q):
    yaw = math.atan2(2.0 * (q[2] * q[0] - q[1] * q[3]),1 - 2 * q[2] * q[2] - 2 * q[3] * q[3])
    return yaw

def localize_client(stop2,lock):
    try:
        # using with keyword save the life! If not used, the unmanaged resources are getting cleaned up
        # and this caused problems with interacting with Naoqi proxy
        with zmq.Context.instance() as ctx: 
            with ctx.socket(zmq.SUB) as sock:
                #socket = context.socket(zmq.REQ)
                sock.connect("tcp://localhost:5566")
                sock.setsockopt(zmq.SUBSCRIBE, "TPP")
                
                #global stop
                global gPose
                global gPoseFiltered
                while stop is not True:
                    msgs = sock.recv_multipart()
                    #print msgs
                    poses = pose_v_pb2.Pose_V()
                    poses.ParseFromString(msgs[1])

                    for pose in poses.pose:
                        #print pose
                        if pose.name == "torso_frame_world":
                            lock.acquire()
                            rot = [pose.orientation.w,pose.orientation.x,pose.orientation.y,pose.orientation.z]
                            gPose = [pose.position.x,pose.position.y,pose.position.z,pose.orientation.w,pose.orientation.x,pose.orientation.y,pose.orientation.z, getHeading(rot)]
                            #print "L:", gPose[0]/1000,gPose[1]/1000,gPose[2]/1000, gPose[3],gPose[4],gPose[5],gPose[6], gPose[7]
                            lock.release()
                        elif pose.name == "torso_frame_world_filtered":
                            lock.acquire()
                            rot = [pose.orientation.w,pose.orientation.x,pose.orientation.y,pose.orientation.z]
                            gPoseFiltered = [pose.position.x,pose.position.y,pose.position.z,pose.orientation.w,pose.orientation.x,pose.orientation.y,pose.orientation.z, getHeading(rot)]
                            #print "L:", gPose[0]/1000,gPose[1]/1000,gPose[2]/1000, gPose[3],gPose[4],gPose[5],gPose[6], gPose[7]
                            lock.release()
                            #print gPose
                sock.close()
    except:
        print "localize_client : ", sys.exc_info()

def send_position_values(vals):
    print vals

def recordData(memory):
    """ Record the data from ALMemory.
    Returns a matrix of values
    """
    pos = memory.getListData(POS_TO_LOG_LIST)
    return pos

def recordPositionValues(memory,lock):
    while stop is not True:
        lock.acquire()
        pos = recordData(memory)
        send_position_values(pos)
        lock.release()
        time.sleep(0.100)

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

def action_moveTo(motion,posture,x,y,theta):
        #moveInit(motion,posture)
        if motion is not None:
            id = motion.post.moveTo(x,y,theta)
            return [id,motion]
        return []


def makeMotion(ip,port,lock):
    useSensors = True
    if ip == '127.0.0.1':
        useSensors = False
    motion = getMotionProxy(ip,port)
    posture = getPostureProxy(ip,port)
    memory = getMemoryProxy(ip,port)
    moveInit(motion,posture)
    ret = action_moveTo(motion,posture,0.6,0.5,math.pi/2)
    #ret = action_moveTo(motion,posture,0.75,0,0)
    #global gPose
    while ret[1].isRunning(ret[0]):
        # motion.FRAME_WORLD
        odomData = motion.getPosition("Torso",1, True)
        memData = memory.getListData(dataNamesList)
        #print odomData
        
        #positionData = motion.getAngles("Body", True)
        #print positionData

        pos = [odomData[0], odomData[1], odomData[2]]
        rot = transformations.quaternion_from_euler(odomData[3], odomData[4], odomData[5])

        rPos = motion.getRobotPosition(useSensors)
        rNextPos = motion.getNextRobotPosition()
        rVel = motion.getRobotVelocity()
        #rot2 = transformations.quaternion_from_euler(memData[1], memData[2], memData[3])

        lock.acquire()
        local = gPose
        localFiltered = gPoseFiltered
        lock.release()
        if local != None:
            print "O:", pos[0],pos[1],pos[2], rot[0],rot[1],rot[2],rot[3], getHeading(rot), 0, 0
            print "L:", local[0]/1000,local[1]/1000,local[2]/1000, local[3],local[4],local[5],local[6], local[7], 0, 0
            print "L_F:", localFiltered[0]/1000,localFiltered[1]/1000,localFiltered[2]/1000, localFiltered[3],localFiltered[4],localFiltered[5],localFiltered[6], localFiltered[7], 0, 0
            print "IMU:", memData
            print "LOC:", rPos[0],rPos[1],rPos[2],rNextPos[0],rNextPos[1],rNextPos[2],rVel[0],rVel[1],rVel[2],0
        #print gPose
        time.sleep(0.100)

    for i in range(1,10):
        odomData = motion.getPosition("Torso",1, True)
        memData = memory.getListData(dataNamesList)
        #print odomData
        
        #positionData = motion.getAngles("Body", True)
        #print positionData

        pos = [odomData[0], odomData[1], odomData[2]]
        rot = transformations.quaternion_from_euler(odomData[3], odomData[4], odomData[5])

        #rot2 = transformations.quaternion_from_euler(memData[1], memData[2], memData[3])
        rPos = motion.getRobotPosition(useSensors)
        rNextPos = motion.getNextRobotPosition()
        rVel = motion.getRobotVelocity()

        lock.acquire()
        local = gPose
        localFiltered = gPoseFiltered
        lock.release()
        if local != None:
            print "O:", pos[0],pos[1],pos[2], rot[0],rot[1],rot[2],rot[3], getHeading(rot), 0, 0
            print "L:", local[0]/1000,local[1]/1000,local[2]/1000, local[3],local[4],local[5],local[6], local[7], 0, 0
            print "L_F:", localFiltered[0]/1000,localFiltered[1]/1000,localFiltered[2]/1000, localFiltered[3],localFiltered[4],localFiltered[5],localFiltered[6], localFiltered[7], 0, 0
            print "IMU:", memData
            print "LOC:", rPos[0],rPos[1],rPos[2],rNextPos[0],rNextPos[1],rNextPos[2],rVel[0],rVel[1],rVel[2],0
        #print gPose
        time.sleep(0.100)

    time.sleep(3)
    global stop
    lock.acquire()
    stop = True
    lock.release()

#def makeMotion2(ip,port,lock):
#    motion = getMotionProxy(ip,port)
#    posture = getPostureProxy(ip,port)
#    moveInit(motion,posture)

#    ret = action_moveTo(motion,posture,0.75,0,0)

#    #global gPose
#    while ret[1].isRunning(ret[0]):
#        # motion.FRAME_WORLD
#        odomData = motion.getPosition("Torso",1, True)
#        #print odomData
        
#        #positionData = motion.getAngles("Body", True)
#        #print positionData

#        pos = [odomData[0], odomData[1], odomData[2]]
#        rot = transformations.quaternion_from_euler(odomData[3], odomData[4], odomData[5])
#        lock.acquire()
#        local = gPose
#        localFiltered = gPoseFiltered
#        lock.release()
#        if local != None:
#            print "O:", pos[0],pos[1],pos[2], rot[0],rot[1],rot[2],rot[3], getHeading(rot)
#            print "L:", local[0]/1000,local[1]/1000,local[2]/1000, local[3],local[4],local[5],local[6], local[7]
#            print "L_F:", localFiltered[0]/1000,localFiltered[1]/1000,localFiltered[2]/1000, localFiltered[3],localFiltered[4],localFiltered[5],localFiltered[6], localFiltered[7]
#        #print gPose
#        time.sleep(0.100)

#    global stop
#    lock.acquire()
#    stop = True
#    lock.release()


if __name__ == "__main__":
    # Real Robot
    ROBOT_IP = "192.168.11.41"
    ROBOT_PORT = 9559
    try:
        # create a lock object for synchronization
        lock = thread.allocate_lock()
        time.sleep(8)
        #memory = ALProxy("ALMemory", ROBOT_IP, ROBOT_PORT)
        #thread.start_new_thread(recordPositionValues,(memory,lock))
        thread.start_new_thread(localize_client,(stop,lock))
        time.sleep(2)
        #stop = True
        makeMotion(ROBOT_IP,ROBOT_PORT,lock)
    except:
      print "Exception occured : ", sys.exc_info()

    raw_input("Press enter to continue ... ")