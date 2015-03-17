import csv
import socket
import SimpleClient

CRLF = "\r\n"

def csv_reader(file_obj):
    reader = csv.reader(file_obj)
    i=0;
    for row in reader:
        #print(" ".join(row))
        if i>0:  
            send_joint_values(row)
        i=i+1

def send_joint_values(row):
    joint_values = row[3:28]
    print(joint_values)

if __name__ == "__main__":
    csv_path = "datalog.csv"
    client = SimpleClient.SimpleClient("localhost",4765)
    #client.writeline("env_getrobots")
    client.writeline("robot_getdofvalues 1")
    while 1:
        line = client.readline()
        if not line:
            break
        else:
            print line
            break
    
    #s = socket.socket(
    #socket.AF_INET, socket.SOCK_STREAM)
    
    #s.connect(("localhost", 4765))
    #s.sendall('env_getbodies' + CRLF )
    #data = s.recv(1024)
    #s.close()
    #print data

    #with open(csv_path, "rb") as f_obj:
    #    csv_reader(f_obj)