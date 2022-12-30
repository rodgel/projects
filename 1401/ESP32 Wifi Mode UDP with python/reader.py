# a python program to send an initial packet, then listen for packets from the ESP32
# the laptop/rasp pi that this code runs on can still be connected to the internet, but should also "share" its connection by creating its own mobile hotspot
# this version of the code allows your laptop to remain connected to the internet (which is a postive)
# but requires configuring your laptop to share its internet connection (which can be a negative because it is tricky to set up depending on your OS)
# for version that does not require sharing an internet connection, see https://gist.github.com/santolucito/70ecb94ce297eb1b8b8034f78683447b 

import socket
UDP_IP = "172.20.10.2" # The IP that is printed in the serial monitor from the ESP32
SHARED_UDP_PORT = 4210
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Internet  # UDP
sock.connect((UDP_IP, SHARED_UDP_PORT))
def loop():
    while True:
        data = sock.recv(2048)
        print(data)
if __name__ == "__main__":
    sock.send('Hello ESP32'.encode())
    loop()