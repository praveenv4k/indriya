import socket
import json
import sys


def localization_client(ip,port):
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect(ip,port)

        while(1):
            result = json.loads(s.recv(1024));
            print(result)

        s.close()
    except:
        print "Exception. Check if the server is running", sys.exc_info()


if __name__ == "__main__":
    localization_client("localhost",5700)