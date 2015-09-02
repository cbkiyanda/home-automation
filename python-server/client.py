import socket
import sys
import struct

packet_format = '!ifff'
test_data = [[1441138382,1.0,2.0,3.0],[1441138383,1.1,2.1,3.1],[1441138384,1.2,2.2,3.2],[1441138385,1.3,2.3,3.3]]
# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
server_address = ('localhost', 10000)
print >>sys.stderr, 'connecting to %s port %s' % server_address
sock.connect(server_address)

try:
    # Send data
    for data in test_data:
      print >>sys.stderr, 'sending {0}'.format(data)
      message = struct.pack(packet_format, *data)
      print >>sys.stderr, struct.unpack(packet_format, message)
      sock.sendall(message)
finally:
    print >>sys.stderr, 'closing socket'
    sock.close()
