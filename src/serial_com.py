import serial
import time

port = serial.Serial('COM9', 9600, timeout=0.5)
port.write('0'.encode('utf_8'))
time.sleep(0.1)

try:
    while(1):
        val = input("[0] Disarm cabin\n[1] Arm Cabin\r\n")
        port.write(val.encode('utf_8'))
        time.sleep(0.1)

except KeyboardInterrupt as e:
    print("Ending program\n")
    port.write('0'.encode('utf_8'))
    time.sleep(0.1)
    port.close()