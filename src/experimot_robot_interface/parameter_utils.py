import socket
import zmq
import node_pb2


def getNodeParameters(name,parameterServerAddress,timeout):
    try:
        context = zmq.Context()
        socket = context.socket(zmq.REQ)
        socket.connect(parameterServerAddress)
        socket.send(name)
        
    except:
        print "getNodeParameters : ", sys.exc_info()