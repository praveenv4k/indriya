__author__ = 'GVlab'

import joint_value_map_pb2
import zmq
import csv
import time

jMap = {0:1,1:0,2:9,3:8,4:7,5:10,6:2,7:3,8:11,
        9:12,10:5,11:4,12:13,13:6,14:20,15:19,
        16:21,17:14,18:15,19:22,20:23,21:17,22:16,23:24,24:18}

#print(jMap)
#print jMap[20]

port = "5563"
context = zmq.Context()
sock = context.socket(zmq.PUB)
sock.bind("tcp://*:%s" % port)
head = "RSP"

def csv_reader(file_obj,repeat):
    reader = csv.reader(file_obj)
    for k in range(0,repeat):
        i=0
        for row in reader:
            #print(" ".join(row))
            #if i>2:
            #    break
            if i>0:
                send_joint_values(row)
                #print row[4:29]
            i=i+1
            time.sleep(0.1)

def send_joint_values(row):
    joint_values = row[4:29]
    rave_joint = reorder_joint_values(joint_values)

    msg = joint_value_map_pb2.JointValueVector()

    for i in range(0,25):
        #elem = msg.map_field.add()
        #elem.key = i
        #elem.value = float(rave_joint[i])
        elem = msg.JointValues.add()
        elem.id = i
        elem.value = float(rave_joint[i])

    str = msg.SerializeToString()
    sock.send_string(head,zmq.SNDMORE)
    sock.send_string(str)
    #print(joint_values)
    #print(rave_joint)

def reorder_joint_values(row):
    data = []
    for i in range(0,25):
        data.append(row[jMap[i]])
    #print data
    return data

if __name__ == "__main__":
    csv_path = "datalog.csv"
    repeat = 1
    with open(csv_path, "rb") as f_obj:
        csv_reader(f_obj,repeat)

