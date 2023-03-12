import sys
import logging
import threading
import serial
sys.path.append('./AEAC-Controls-2023/src/')

logging.basicConfig(level=logging.DEBUG)
uaslog = logging.getLogger("UASlogger")

def main():
    uaslog.debug("Setting up RFD900x Serial Port...")
    rfd_port = serial.Serial('COM8', 115200, timeout=0.5)

    # rfd_port.write('ATPP'.encode('utf_8')) # check status
    # time.sleep(0.1)
    # rfd_port.write('ATPI=2'.encode('utf_8')) # set pin 2 as input
    # time.sleep(0.1)
    # rfd_port.write('ATPM=2'.encode('utf_8')) # set pin 2 mirroring
    # time.sleep(0.1)

    try:
        while True:
            cmd = input("Enter cmd to send to RFD900x\r\n")
            rfd_port.write(cmd.encode('utf-8'))
            # rfd_port.write('ATPP'.encode('utf-8')) # check status

            while rfd_port.in_waiting:
                # display each character to the LCD
                res = rfd_port.read()
                print(res.decode("utf-8"))

    except KeyboardInterrupt as e:
        uaslog.info("Terminating RFD900x Config Test.\r\n")
        sys.exit(0)


if __name__ == "__main__":
    main()