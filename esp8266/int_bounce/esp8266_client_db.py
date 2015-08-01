

import bson
from collections import namedtuple
import hashlib
#hashlib.sha224("Nobody inspects the spammish repetition").hexdigest()
import struct

import pymongo
from pymongo import MongoClient

#variable = sys.argv[1]
#variable = 'FEDO' # start with this

def ip2int(addr):                                                               
    return struct.unpack("!I", socket.inet_aton(addr))[0]                       

def int2ip(addr):                                                               
    val = socket.inet_ntoa(struct.pack("!I", addr))
    return '.'.join(val.split('.')[::-1])

#client = MongoClient()

#db1 = client['ESP8266']
#collection1 = db1['Touch']

DataIn = namedtuple('DataIn', ['millis', 'adc', 'ip'], verbose=True)
Data = namedtuple('Data', ['millis', 'adc', 'ip' 'sha'], verbose=True)




    
import socket 
import time

host = '192.168.1.29' 
port = 80 
size = 1024 
i=0
while True:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
    s.connect((host,port))
    s.send(str(i)) 
    data, addr = s.recvfrom(size) 
    print 'Received:', data, 'from:', addr
    i = int(data.split('::')[1]) + 1
    s.close()
    time.sleep(2)

    

    

client.close()




