import socket, select, sys

# COPY SYNC SERVER
class CS_server:
    # Get the basic of the server set up
    def __init__(self, port=8088, buf_size=1024, **kwargs):
        # List for socket descriptors
        self.CONNECTION_LIST = []
        self.buf_size = buf_size
        # Port number we are going to use
        self.port = port
        self.server_socket = self.server_setup()
        print ("server started at port " + str(self.port))
        self.run()
    
    # This function do the socket, bind and listen operation and set up server
    def server_setup(self):
        try:
            server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            server_socket.bind(("localhost", self.port))
            server_socket.listen(10)
            self.CONNECTION_LIST.append(server_socket)
        except:
            print ("Failed to initialize server!")
            sys.exit(1)
        return server_socket

    def run(self):
        while 1:
            # Get the list socket that are ready for select
            read_socket, write_socket, error_socket = select.select(self.CONNECTION_LIST, [], [])
            for sock in read_socket:
                # New connection
                if sock == self.server_socket:
                    # append the new socket new connection to our list
                    sockfd, addr = self.server_socket.accept()
                    self.CONNECTION_LIST.append(sockfd)
                    print ("SOMEONE FROM (%s, %s) CONNECTED" % addr)
                else:
                    # Data receive from client side, need to process
                    try:
                        data=sock.recv(self.buf_size)
                        # TODO do something with the data
                        print(data.decode())
                    except:
                        print ("CLIENT FROM (%s, %s) HAS DISCONNECTED" % addr)
                        sock.close()
                        self.CONNECTION_LIST.remove(sock)
                        continue
        self.server_socket.close()

if __name__ == "__main__":
    my_server = CS_server()
