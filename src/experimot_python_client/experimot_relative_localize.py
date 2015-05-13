__author__      = 'Praveenkumar VASUDEVAN'
__copyright__   = "Copyright 2015, GVLab"
__credits__     = ["Praveenkumar VASUDEVAN"]
__license__     = "MIT"
__version__     = "0.0.1"
__email__       = "praveenv4k@gmail.com"
__status__      = "Development"

# Standard libraries
import socket
import json
import sys
import thread
import threading
import time
import math
import os
import argparse


from os.path import dirname
from os.path import abspath


# Additional dependencis
# ZeroMQ Python bindings - http://zeromq.org/bindings:python
import zmq

# matplot library - http://matplotlib.org/
import matplotlib.pyplot as plt
import matplotlib.transforms as tfm
import matplotlib.patches as patches
import matplotlib.animation as animation

# transformations.py - http://www.lfd.uci.edu/~gohlke/code/transformations.py.html
import transformations


dev = os.environ["DEV_SDK_ROOT"]
dir1 = os.path.join(dev,"experimot","scripts","msgs")
dir2 = os.path.join(dev,"experimot","scripts","experimot_robot_interface")

sys.path.append(dir1)
sys.path.append(dir2)


# Protobuf Messages
import human_pb2


# some global variables for positions and orientations
pos = [0.0,0.0,0.0]
orient = [1.0,0.0,0.0,0.0]

pose = [0.0,0.0,0.0,0.0,0.0,0.0]

global_humans = human_pb2.Humans()
#############################################################################################################
# Localization server - A sample server for testing purpose
def localization_server(ip,port):
    context = zmq.Context()
    socket = context.socket(zmq.REP)
    socket.bind(("tcp://*:%d" % port))

    #dummy = { 'pos' : {'x':'1000','y':'1000','z':'1000'}, 'orient': {'w':'1','x':'0','y':'0','z':'0'}};
    dummy = { 'pose' : {'x':'1','y':'1','alpha':'0'}};
    while True:
        #  Wait for next request from client
        message = socket.recv()
        #print("Received request: %s" % message)

        #  Do some 'work'
        time.sleep(0.050)

        #  Send reply back to client
        socket.send(json.dumps(dummy))
    print "quitting ... "

#############################################################################################################
# Localization client  
def localization_client(lock,ip,port):
    context = zmq.Context()
    #  Socket to talk to server
    print "Connecting to localization server ... "
    socket = context.socket(zmq.REQ)
    socket.connect(("tcp://localhost:%d" % port))

    #  Do 10 requests, waiting each time for a response
    while True:
        # print("Sending request %s ... " % request)
        socket.send(b"pose")

        #  Get the reply.
        str = socket.recv(1024)
        #print str
        result = json.loads(str)

        # printing the result
        # print(result)
        
        # In order to access position : (result["pos"]["x"],result["pos"]["y"],result["pos"]["z"])
        # In order to access orientation : (result["orient"]["w"],result["orient"]["x"],result["orient"]["y"],result["orient"]["z"])

        lock.acquire()
        #global pos, orient
        #pos = [float(result["pos"]["x"]),float(result["pos"]["y"]),float(result["pos"]["z"])]
        #orient = [float(result["orient"]["w"]),float(result["orient"]["x"]),float(result["orient"]["y"]),float(result["orient"]["z"])]
        global pose
        #pose = [float(result["pose"]["x"]),float(result["pose"]["y"]),float(result["pose"]["alpha"])]
        pose = [float(result["pos"]["x"]),float(result["pos"]["y"]),float(result["orient"]["z"]),float(result["euler"]["Rx"]),float(result["euler"]["Ry"]),float(result["euler"]["Rz"])]
        lock.release()

        #print "Position    : " , pos
        #print "Orientation : " , orient

        # wait for a while
        time.sleep(0.050)

#############################################################################################################
# Human Pose  
def human_client(lock,ip,port,topic):
    context = zmq.Context()
    #  Socket to talk to server
    print "Connecting to human pose server ... "
    sock = context.socket(zmq.SUB)
    sock.connect(("tcp://localhost:%d" % port))
    #socket.subscribe(topic)
    sock.setsockopt(zmq.SUBSCRIBE, topic)
    while True:
        # print("Sending request %s ... " % request)
        #  Get the reply.
        header = sock.recv_string()
        body = sock.recv()
        #print str
        humans = human_pb2.Humans()
        humans.ParseFromString(body)
        #print humans

        lock.acquire()
        #global pos, orient
        #pos = [float(result["pos"]["x"]),float(result["pos"]["y"]),float(result["pos"]["z"])]
        #orient = [float(result["orient"]["w"]),float(result["orient"]["x"]),float(result["orient"]["y"]),float(result["orient"]["z"])]
        global global_humans
        global_humans = humans
        lock.release()

        #print "Position    : " , pos
        #print "Orientation : " , orient

        # wait for a while
        time.sleep(0.050)

#############################################################################################################
# Plotting function
def plot_robot_pose(interval, lock, lock2):
    # Creating a figure
    F = plt.figure(1,(10,10))
    # Get an instance to axis
    ax = plt.gca()
    # clear things for fresh plot
    ax.cla() 
    # change default range - approximate localization range
    ax.set_xlim((-0.5,5.5))
    ax.set_ylim((-3,3))
    # set the titles
    ax.set_title('Localization on XZ Plane')
    ax.set_xlabel('Z Axis (m)')
    ax.set_ylabel('X Axis (m)')
    # get a handle to the figure
    fig = plt.gcf()

    angle = 0
    wedge1= patches.Wedge((3,0),0.5,angle-15,angle+15)

    human_wedge1= patches.Wedge((3,0),0.5,angle-15,angle+15)
    human_wedge2= patches.Wedge((3,0),0.5,angle-15,angle+15)
    human_wedge3= patches.Wedge((3,0),0.5,angle-15,angle+15)
    human_wedge4= patches.Wedge((3,0),0.5,angle-15,angle+15)
    human_wedge5= patches.Wedge((3,0),0.5,angle-15,angle+15)
    human_wedge6= patches.Wedge((3,0),0.5,angle-15,angle+15)

    # Kinect Camera
    points = [[0, 0.3], [0, -0.3], [-0.3, 0]]
    polygon = plt.Polygon(points)
    fig.gca().add_artist(polygon)
    # Camera origin
    camera_origin=plt.Circle((0,0),0.05,color='r')
    fig.gca().add_artist(camera_origin)
    # Camera Text annotation
    ax.text(-0.4, -0.5, 'KINECT', fontsize=18)

    # Draw stuff
    plt.draw()
    # enable grid
    plt.grid()

    def init():
        wedge1.center = (3, 0)
        human_wedge1.center = (3.1,0)
        human_wedge1.set_color('r')

        human_wedge2.center = (3.2,0)
        human_wedge2.set_color('orange')

        human_wedge3.center = (3.3,0)
        human_wedge3.set_color('g')

        human_wedge4.center = (3.4,0)
        human_wedge4.set_color('b')

        human_wedge5.center = (3.5,0)
        human_wedge5.set_color('indigo')

        human_wedge6.center = (3.6,0)
        human_wedge6.set_color('violet')

        #new Pen(Brushes.Red, 6),
        #        new Pen(Brushes.Orange, 6),
        #        new Pen(Brushes.Green, 6),
        #        new Pen(Brushes.Blue, 6),
        #        new Pen(Brushes.Indigo, 6),
        #        new Pen(Brushes.Violet, 6)

        ax.add_patch(wedge1)
        ax.add_patch(human_wedge1)
        ax.add_patch(human_wedge2)
        ax.add_patch(human_wedge3)
        ax.add_patch(human_wedge4)
        ax.add_patch(human_wedge5)
        ax.add_patch(human_wedge6)
        return [wedge1,human_wedge1,human_wedge2,human_wedge3,human_wedge4,human_wedge5,human_wedge6],

    def animate(i):
        lock.acquire()
        local_pos = pose[0:2];
        local_orient = pose[2]
        local_rpy = [pose[3],pose[4],pose[5]]
        lock.release()

        lock2.acquire()
        global global_humans
        local_humans = global_humans
        lock2.release()

        human_wedge1.set_visible(False)
        human_wedge2.set_visible(False)
        human_wedge3.set_visible(False)
        human_wedge4.set_visible(False)
        human_wedge5.set_visible(False)
        human_wedge6.set_visible(False)
        for human in local_humans.human:
            id = human.id
            tracked = human.tracked
            if tracked == True:
                temp_wedge = None
                if(id == 1):
                    temp_wedge = human_wedge1
                elif(id == 2):
                    temp_wedge = human_wedge2
                elif(id == 3):
                    temp_wedge = human_wedge3
                elif(id == 4):
                    temp_wedge = human_wedge4
                elif(id == 5):
                    temp_wedge = human_wedge5
                elif(id == 6):
                    temp_wedge = human_wedge6

            if temp_wedge != None:
                temp_wedge.set_visible(True)
                human_torso = human.torso_position
                #print human_torso
                w = human.orientation.w
                x = human.orientation.x
                y = human.orientation.y
                z = human.orientation.z
                human_orient = [human.orientation.w,human.orientation.x,human.orientation.y,human.orientation.z]
                #print human_orient
                temp_wedge.set_center((human_torso.z,human_torso.x))
                
                human_euler = transformations.euler_from_quaternion(human_orient,axes='szyx')

                if(not(math.isnan(w)) and not(math.isnan(x)) and not(math.isnan(y)) and not(math.isnan(z))):
                    roll  = math.degrees(math.atan2(2*y*w - 2*x*z, 1 - 2*y*y - 2*z*z));
                    pitch = math.degrees(math.atan2(2*x*w - 2*y*z, 1 - 2*x*x - 2*z*z));
                    yaw   = math.degrees(math.asin(2*x*y + 2*z*w));
                    human_euler = [math.degrees(x) for x in human_euler]
                    human_deg = 180-roll
                    temp_wedge.set_theta1(human_deg - 15)
                    temp_wedge.set_theta2(human_deg + 15)

                    print "Human : " , human.id, " , " , [human_torso.z,human_torso.x], " , " , [roll,pitch,yaw] 
        #local_pos = [x/1000 for x in local_pos]
        
        #euler = transformations.euler_from_quaternion(local_orient,axes='syxz')
        #euler = [math.degrees(x) for x in euler]
        #deg = euler[1]
        deg = math.degrees(local_orient)
        if(deg > 0):
            deg = deg-90
        else:
            deg = deg+90
        #x,y   = wedge1.center
        x = local_pos[0]
        y = local_pos[1]

        wedge1.set_center((x,y))
        wedge1.set_theta1(deg - 15)
        wedge1.set_theta2(deg + 15)
        #print "Hello : (%d,%d);(%d,%d)" % (x,y,theta1,theta2)
        
        local_rpy = [math.degrees(x) for x in local_rpy]
        print local_pos,deg,local_rpy
        #print "Position    : " , local_pos
        #print "Orientation : " , local_orient
        #print "Euler       : " , deg

        return [wedge1,human_wedge1,human_wedge2,human_wedge3,human_wedge4,human_wedge5,human_wedge6],

    an1 = animation.FuncAnimation(fig,animate,init_func=init,interval=interval)
    plt.show()


#############################################################################################################
# Main function
if __name__ == "__main__":

    # port
    port = 5700
    # ip address
    ip = "localhost"

    # Human pose port
    port2 = 5571
    # Human Pose Topic
    topic = "HPP"

    try:
        # create a lock object for synchronization
        lock = thread.allocate_lock()
        lock2 = thread.allocate_lock()

        # Starting the plotting thread
        interval = 200;
        thread.start_new_thread(plot_robot_pose,(interval,lock,lock2));

        # Responder (server) - uncomment to check with the local server
        #thread.start_new_thread(localization_server,(ip,port));

        # Requester (client)
        thread.start_new_thread(localization_client,(lock,ip,port));
        thread.start_new_thread(human_client,(lock2,ip,port2,topic));

    except:
        # printing on exception
        print "Exception occured : ", sys.exc_info()

    # do nothing in the main thread
    while 1:
        pass