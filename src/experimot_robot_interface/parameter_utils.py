import socket
import zmq
import node_pb2
import robot_behavior_pb2
import sys

def getNodeParameters(name,parameterServerAddress,timeout):
    try:
        # using with keyword save the life! If not used, the unmanaged resources are getting cleaned up
        # and this caused problems with interacting with Naoqi proxy
        with zmq.Context.instance() as ctx: 
            with ctx.socket(zmq.REQ) as sock:
                #socket = context.socket(zmq.REQ)
                sock.connect(parameterServerAddress)
                print "Sending parameter retrieval request"
                sock.send(name)
                print "waiting parameter response"
                str = sock.recv()
                node = node_pb2.Node()
                print "parsing parameter response"
                node.ParseFromString(str)
                sock.close()
                print node
                return node
    except:
        print "getNodeParameters : ", sys.exc_info()


def getParam(node,key,defaultValue):
    ret = defaultValue
    if node != None:
        for p in node.param:
            if p.key == key:
                ret = p.value.encode('utf-8') # needed to encode in utf-8 because naoqi doesn't accept unicode
    return ret

def register_motions(node,parameterServerAddress,motions):
    print "Creating behavior module message"
    behaviorModule = robot_behavior_pb2.RobotBehaviorModule()
    behaviorModule.name = node.name


    port = int(parameter_utils.getParam(node,"RequestServerPort", "5590"))
    ip = parameter_utils.getParam(node,"RequestClientIP", "*")
    behaviorModule.responder = robot_behavior_pb2.RobotBehaviorResponder()

    behaviorModule.responder.Host = ip
    behaviorModule.responder.Port = port

    for motion in motions:
        print "Creating behavior description message", motion
        desc = behaviorModule.behaviors.add()
        desc.name = motion
        desc.type = robot_behavior_pb2.BehaviorDescription.Blocking
        desc.state = robot_behavior_pb2.BehaviorDescription.Idle

    print behaviorModule

    try:
        with zmq.Context.instance() as ctx: 
            with ctx.socket(zmq.REQ) as sock:
                parts = []
                str = behaviorModule.SerializeToString();
                sock.connect(parameterServerAddress)
                parts.append("register_behaviors")
                parts.append(node.name.encode('utf-8'))
                parts.append(str)                
                print "Sending register_motions message", parts
                sock.send_multipart(parts)
                response = sock.recv()
                sock.close()
                print response
    except:
        print "register_motions : ", sys.exc_info()
