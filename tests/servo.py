import time
import sys
import math
import logging
import odroid_wiringpi as wpi
sys.path.append('../src/')
from pwm import PWM
from constants import *
from PCA9685 import PCA9685
# from motor_specs import MOTORS

logging.getLogger("Adafruit_I2C.Device.Bus.{0}.Address.{1:#0X}".format(0, 0X40)).setLevel(logging.WARNING)
logging.basicConfig(level=logging.DEBUG)
uaslog = logging.getLogger("UASlogger")

class Servo:
    def __init__(self):
        ##################
        # INIT GPIO PINS #
        ##################
        self.init_gpio()

        ############
        # INIT PWM #
        ############
        uaslog.debug("Init PWM...")
        self.pwm = PWM(address=I2C_CHIP, busnum=I2C_BUS, debug=False)
        self.pwm.setPWMFreq(FREQUENCY)  # 50 Hz for analog servo

        ###############
        # INIT MOTORS #
        ###############
        uaslog.debug("Init Motors...")
        # HEXTRONIK
        self.hexatronik = PCA9685(channel=CHANNEL0, freq=50)
        self.hexatronik.reset(self.pwm)
        # self.hexatronik.setPWM(self.pwm, dutycycle=30)

        uaslog.info("Motor Drive System init complete! Starting main routine...")

    def controlLoop(self):
        try:
            uaslog.info("Starting Servo Test...")
            uaslog.info("Plug a Hexatronik Servo at Channel 0 of PCA9685 and enter DC values.")

            while True:
                # freq and dc motor testing
                dc = int(input("Enter Duty Cycle [0,95]: "))
                uaslog.info("Servo Position at DC {}".format(dc))

                self.hexatronik.setPWM(self.pwm, dutycycle=dc)
                
        except KeyboardInterrupt as e:
            uaslog.warning(f"{e}\nServo Test Complete.")
            self.cleanup()
            sys.exit(0)

    def init_gpio(self):
            uaslog.info("Init GPIO...")
            # unexport pins
            for pin in range(0, 256):
                file = open("/sys/class/gpio/unexport","w")
                file.write(str(pin))

            # setup wpi
            wpi.wiringPiSetup()
            
            # set pin mode
            for pin in GPIO_IN:
                wpi.pinMode(pin, wpi.INPUT)
                wpi.pullUpDnControl(pin, wpi.GPIO.PUD_UP)

            for pin in GPIO_OUT:
                wpi.pinMode(pin, wpi.OUTPUT)
                # init out pins low
                wpi.digitalWrite(pin, 0)
            uaslog.info("Init GPIO complete!")

    def cleanup(self):
        uaslog.info("Cleaning up driver system...")

        # reset motors
        self.hexatronik.reset(self.pwm)

        # unexport pins
        for pin in range(0, 256):
            file = open("/sys/class/gpio/unexport","w")
            file.write(str(pin))
        
        uaslog.info("Driver system cleanup complete!")

def main():
    test = Servo()
    test.controlLoop()

if __name__ == "__main__":
    main()