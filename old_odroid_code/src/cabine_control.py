import time
import sys
import math
import logging
import odroid_wiringpi as wpi
# sys.path.append('./aeac_controls_2022/')
from pwm import PWM
from constants import *
from motor_specs import MOTORS

logging.getLogger("Adafruit_I2C.Device.Bus.{0}.Address.{1:#0X}".format(0, 0X40)).setLevel(logging.WARNING)
logging.basicConfig(level=logging.DEBUG)
uaslog = logging.getLogger("UASlogger")


class CabineControl:
    def __init(self):
        uaslog.info("Starting Motor Drive System init...")

        ############################
        # INIT MOTOR TARGET VALUES #
        ############################
        self.target_servo = [0, 0]
        self.target_actuator = [0, 0]

        self.door_closed = False
        self.belt_secured = False

        ##################
        # INIT GPIO PINS #
        ##################
        self.init_gpio()

        ############
        # INIT PWM #
        ############
        uaslog.debug("Init PWM...")
        self.pwm = PWM(address=I2C_CHIP, busnum=I2C_BUS, debug=False)
        self.pwm.setPWMFreq(FREQUENCY)

        ###############
        # INIT MOTORS #
        ###############
        uaslog.debug("Init Motors...")

        # ACTUATORS
        # door lock
        self.actuonix_1 = PCA9685(channel=CHANNEL8, freq=300)
        self.actuonix_1.reset(self.pwm)
        self.actuonix_1.setPWM(self.pwm, dutycycle=30)

        # seat belt
        self.actuonix_2 = PCA9685(channel=CHANNEL9, freq=300)
        self.actuonix_2.reset(self.pwm)
        self.actuonix_2.setPWM(self.pwm, dutycycle=30)


        uaslog.info("Motor System init complete! Starting main routine...")
        
        # self.controlLoop()
