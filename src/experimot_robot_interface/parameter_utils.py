import socket
import zmq
import node_pb2
import sys


def getNodeParameters(name,parameterServerAddress,timeout):
    try:
        context = zmq.Context()
        socket = context.socket(zmq.REQ)
        socket.connect(parameterServerAddress)
        socket.send(name)
        str = socket.recv()
        #str = socket.recv_string(encoding='latin1')
        #print str
        node = node_pb2.Node()
        node.ParseFromString(str)
        socket.close()
        print node
        return node
    except:
        print "getNodeParameters : ", sys.exc_info()

def getParam(node,key,defaultValue):
    ret = defaultValue
    if node != None:
        for p in node.param:
            if p.key == key:
                ret = p.value
    return ret