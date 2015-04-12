__author__ = 'Praveenkumar VASUDEVAN'

import socket
import json
import sys
import SocketServer
import thread
import time
import zmq

# server
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
        time.sleep(1)

        #  Send reply back to client
        socket.send(json.dumps(dummy))
    print "quitting ... "

# client 
def localization_client(ip,port):
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
        print "Position    : " , (float(result["pos"]["x"]),float(result["pos"]["y"]),float(result["pos"]["z"]))
        print "Orientation : " , (float(result["orient"]["w"]),float(result["orient"]["x"]),float(result["orient"]["y"]),float(result["orient"]["z"]))

        # wait for a while
        time.sleep(0.1)

# main function
if __name__ == "__main__":
    # port
    port = 5700
    # ip address
    ip = "localhost"

    try:
        # Responder (server) - uncomment to check with the local server
        # thread.start_new_thread(localization_server,(ip,port));

        # Requester (client)
        thread.start_new_thread(localization_client,(ip,port));

    except:
        # printing on exception
        print "Exception occured : ", sys.exc_info()

    # do nothing 
    while 1:
        pass

    time.sleep(10)