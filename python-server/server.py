import socket
import sys
import struct

packet_format = '!ifff'

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the port
server_address = ('localhost', 10000)
print >>sys.stderr, 'starting up on %s port %s' % server_address
sock.bind(server_address)

# Listen for incoming connections
sock.listen(1)

while True:
    # Wait for a connection
    print >>sys.stderr, 'waiting for a connection'
    connection, client_address = sock.accept()
    try:
        print >>sys.stderr, 'connection from', client_address

        # Receive the data in small chunks and retransmit it
        while True:
            data = connection.recv(32)
            print >>sys.stderr, 'received "%s"' % data
            try:
                print >>sys.stderr, 'meaning  {0}'.format(struct.unpack(packet_format,data))
            except struct.error:
                print >>sys.stderr, 'received {0}'.format(data)
            if not data:
                print >>sys.stderr, 'no more data from', client_address
                break

    finally:
        # Clean up the connection
        connection.close()
