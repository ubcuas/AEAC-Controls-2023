import serial
import time
import logging

logging.basicConfig(level=logging.DEBUG)
uaslog = logging.getLogger("UASlogger")

class CabinControl:
    def __init__(self, UNO_COM, RFD_COM): # TODO: add Uno and RFD COM port args
        uaslog.info("Starting Cabin Controls System Init...")
        
        #####################
        # INIT SERIAL PORTS #
        #####################
        uaslog.debug("Setting up Arduino Uno Serial Port...")
        self.uno_port = serial.Serial(UNO_COM, 9600, timeout=0.5)

        uaslog.debug("Setting up RFD900x Serial Port...")
        self.rfd_port = serial.Serial(RFD_COM, 115200, timeout=0.5)

        ####################
        # INIT CABIN STATE #
        ####################
        self.cabin_state = 0
        self.change_state = 0

        # arduino firmware handling value sent, mirrored onto RFD
        self.uno_port.write(self.cabin_state) # init cabin state disarmed
        time.sleep(0.1)

        #################
        # CONFIG RFD TX #
        #################
        self.rfd_port.write('ATPP'.encode('utf_8')) # check status
        time.sleep(0.1)
        self.rfd_port.write('ATPI=2'.encode('utf_8')) # set pin 2 as input
        time.sleep(0.1)
        self.rfd_port.write('ATPM=2'.encode('utf_8')) # set pin 2 mirroring
        time.sleep(0.1)

    def controlLoop(self):
        try:
            while True:
                if self.change_state:
                    uaslog.info("Changing Cabin State to {}\r\n".format(self.cabin_state))
                    self.uno_port.write(self.cabin_state.encode('utf_8'))
                    time.sleep(0.1)
                    self.change_state = 0

        except KeyboardInterrupt as e:
            # TODO: not terminating when parent thread ended
            self.cleanup()
            sys.exit(0)

    def setCabinState(self, state):
        uaslog.debug("Setting Cabin State to {}\r\n".format(self.cabin_state))
        self.cabin_state = state
        self.change_state = 1

    def cleanup(self):
        uaslog.info("Cleaning up and closing Serial ports.\r\n")
        self.uno_port.write('0'.encode('utf_8'))
        time.sleep(0.1)
        self.uno_port.close()