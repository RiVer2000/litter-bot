import tty, sys, termios, serial
from time import sleep
import imagedetect_color
from picamera2 import Picamera2

picam2 = Picamera2()
config = picam2.create_still_configuration()
picam2.configure(config)

picam2.start()
ser = serial.Serial('/dev/serial/by-id/usb-Arduino_Srl_Arduino_Uno_85439303333351612151-if00',9600,bytesize=8, parity='N', stopbits=1, timeout=None);

filedescriptors = termios.tcgetattr(sys.stdin)
tty.setcbreak(sys.stdin)
x = 0
rxmsg = ser.readline()
print(rxmsg.decode('ascii'))

while 1:
  x=sys.stdin.read(1)[0]
  ser.write(x.encode('ascii'))
  print("You pressed", x)
  if (ser.inWaiting()>0):
    rx=ser.read(ser.inWaiting())
    ser.flushInput()
    ser.flushOutput()
    #capture pic
    #camflag = object_detection.trash_detect()
    print("starting image capture")
    picam2.capture_file("trash.jpg")
    print("completed image capture")
    camflag = imagedetect_color.color_detect()
    ser.write('m'.encode('ascii')) #deploy arm
    print("sending m. deploying arm")
    sleep(5)
    ser.write('c'.encode('ascii')) #close gripper
    print("sending c. closing gripper")
    sleep(5)

    if (camflag == 1):
      ser.write('n'.encode('ascii')) #stow arm
      print("sending n. stow arm")
      sleep(2)
      ser.flushOutput()
      ser.write('o'.encode('ascii')) #open gripper
      print("sending o. open gripper")
    else:
      ser.write('b'.encode('ascii')) #stow arm right
      print("sending b. stow arm to the right")
      sleep(2)
      ser.write('o'.encode('ascii')) #open gripper
      print("sending o. open gripper")
    sleep(5)
    print("Image Processing Complete. sending z to enable driving")
    ser.flushInput()
    ser.flushOutput()
    ser.write('z'.encode('ascii'))
