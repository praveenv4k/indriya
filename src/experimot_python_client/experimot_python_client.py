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
            while 1:
                print "Handling request"
                data = json.loads(self.request.recv(1024).strip())
                # process the data, i.e. print it:
                print data
                # send some 'ok' back
                self.request.sendall(json.dumps({'return':'ok'}))
        except Exception, e:
            print "Exception wile receiving message: ", e

def localization_server(ip,port):
    server = LocalizationServer((ip,port), LocalizationServerHandler)
    server.serve_forever()
    print "quitting ... "

def localization_client(ip,port):
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((ip,port))
        data = {'req':'localization'}

        while(1):
            print "requesting ... "
            s.send(json.dumps(data))
            result = json.loads(s.recv(1024));
            print(result)
            time.sleep(1)

        s.close()
    except:
        print "Exception. Check if the server is running", sys.exc_info()

if __name__ == "__main__":
    port = 5560
    ip = "localhost"

    try:
        thread.start_new_thread(localization_server,(ip,port));
        thread.start_new_thread(localization_client,(ip,port));
    except:
        print "Exception occured : ", sys.exc_info()

    while 1:
        pass