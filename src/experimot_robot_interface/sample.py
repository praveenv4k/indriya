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

# Additional dependencis
# ZeroMQ Python bindings - http://zeromq.org/bindings:python
import zmq

# matplot library - http://matplotlib.org/
import matplotlib.pyplot as plt
import matplotlib.transforms as tfm
import matplotlib.patches as patches
import matplotlib.animation as animation

# transformations.py - http://www.lfd.uci.edu/~gohlke/code/transformations.py.html
#import transformations

# some global variables for positions and orientations
pos = [0.0,0.0,0.0]
orient = [1.0,0.0,0.0,0.0]

#############################################################################################################
# Localization server - A sample server for testing purpose
def localization_server(ip,port):
    context = zmq.Context()
    socket = context.socket(zmq.REP)
    socket.bind(("tcp://*:%d" % port))

    dummy = { 'pos' : {'x':'100','y':'100','z':'100'}, 'orient': {'w':'1','x':'0','y':'0','z':'0'}};
    while True:
        #  Wait for next request from client
        message = socket.recv()
        print("Received request: %s" % message)

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
        result = json.loads(socket.recv(1024));

        # printing the result
        # print(result)
        
        # In order to access position : (result["pos"]["x"],result["pos"]["y"],result["pos"]["z"])
        # In order to access orientation : (result["orient"]["w"],result["orient"]["x"],result["orient"]["y"],result["orient"]["z"])

        lock.acquire()
        global pos, orient
        pos = [float(result["pos"]["x"]),float(result["pos"]["y"]),float(result["pos"]["z"])]
        orient = [float(result["orient"]["w"]),float(result["orient"]["x"]),float(result["orient"]["y"]),float(result["orient"]["z"])]
        lock.release()

        #print "Position    : " , pos
        #print "Orientation : " , orient

        # wait for a while
        time.sleep(0.050)

#############################################################################################################
# Plotting function
def plot_robot_pose(interval, lock):
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
        ax.add_patch(wedge1)
        return wedge1,

    def animate(i):
        lock.acquire()
        local_pos = pos;
        local_orient = orient
        lock.release()
        x,y   = wedge1.center
        theta1 = wedge1.theta1
        theta2 = wedge1.theta2
        wedge1.set_center((x,y))
        wedge1.set_theta1(i - 15)
        wedge1.set_theta2(i + 15)
        #print "Hello : (%d,%d);(%d,%d)" % (x,y,theta1,theta2)
        
        print "Position    : " , local_pos
        print "Orientation : " , local_orient

        return wedge1,

    an1 = animation.FuncAnimation(fig,animate,init_func=init,interval=interval)
    plt.show()


#############################################################################################################
# Main function
if __name__ == "__main__":
    # port
    port = 5700
    # ip address
    ip = "localhost"

    try:
        # create a lock object for synchronization
        lock = thread.allocate_lock()

        # Starting the plotting thread
        interval = 500;
        thread.start_new_thread(plot_robot_pose,(interval,lock));

        # Responder (server) - uncomment to check with the local server
        thread.start_new_thread(localization_server,(ip,port));

        # Requester (client)
        thread.start_new_thread(localization_client,(lock,ip,port));

    except:
        # printing on exception
        print "Exception occured : ", sys.exc_info()

    # do nothing in the main thread
    while 1:
        pass