__author__ = 'Praveenkumar VASUDEVAN'

import socket
import json
import sys
import SocketServer
import thread
import time

class LocalizationServer(SocketServer.ThreadingTCPServer):
    allow_reuse_address = True

class LocalizationServerHandler(SocketServer.BaseRequestHandler):
    def handle(self):
        try:
            # per client handler forever
            while 1:
                # retrieve the request
                data = json.loads(self.request.recv(1024).strip())
                # process the data, i.e. print it:
                print data
                # send back dummy position/orientation data
                # pos: cartesian 3d position ; orient: quaternion
                # pos: (x,y,z) ; orient: (w,x,y,z)
                self.request.sendall(json.dumps({ 'pos' : {'x':'100','y':'100','z':'100'}, 'orient': {'w':'1','x':'0','y':'0','z':'0'}}))
        except Exception, e:
            print "Exception while receiving message: ", e

# server
def localization_server(ip,port):
    server = LocalizationServer((ip,port), LocalizationServerHandler)
    server.serve_forever()
    print "quitting ... "

# client 
def localization_client(ip,port,retryCount,retryInterval):
    try:
        # Open socket
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        connected = 0
        # Connect to the localization server
        for t in range(1,retryCount):
            print "Trying to connect ...."
            try:
                s.connect((ip,port))
                connected = 1
                print "Connected ...."
                break
            except:
                print "Exception while connecting to server: ", sys.exc_info()
            time.sleep(retryInterval)

        time.sleep(5);

        if (connected == 1):
            # Localization data request format
            data = {'req':'localization'}
            # Loop forever to retrieve the localization data
            while(1):
                try:
                    print "Requesting data ..."
                    # send the request as Json object
                    s.send(json.dumps(data))
                    
                    # Receive the response and parse into a json object
                    #result = json.loads(s.recv(1024));
                    result = s.recv(1024);
                    
                    # Print the result (optional). Comment if not needed
                    print(result)
                except:
                    print "Exception in received value: ", sys.exc_info()
                # 200 ms sleep
                time.sleep(0.2)
        
            # close the socket
            s.close()
    except:
        # printing the exception message
        print "Exception in localization client: ", sys.exc_info()

# main function
if __name__ == "__main__":
    # port
    port = 5700
    # ip address
    ip = "localhost"

    try:
        # client listener
        thread.start_new_thread(localization_client,(ip,port,10,1));
        
        # emulate delay in starting of the server
        # time.sleep(5)

        # starting a test server to test the communication. need to be commented when working with real server
        # thread.start_new_thread(localization_server,(ip,port));

    except:
        # printing on exception
        print "Exception occured : ", sys.exc_info()

    # do nothing 
    while 1:
        pass