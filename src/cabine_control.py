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
        
