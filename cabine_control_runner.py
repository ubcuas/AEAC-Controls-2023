# A temporary cabine control runner for testing purposes without needing software signals
import sys
import threading
import odroid_wiringpi as wpi
sys.path.append('./src/')
from cabine_control import CabineControl
from pwm import PWM
from constants import *
from motor_specs import MOTORS
from TB9051FTG import TB9051FTG
from PCA9685 import PCA9685
from utils import *

def main():
    cabinectrl = CabineControl()

    control_thread = threading.Thread(target=cabinectrl.controlLoop, daemon=True)
    control_thread.start()

    try:
        while True:
            # get updated values (done from software side importing cabine control submodule)
            buttonA = wpi.digitalRead(PIN_A)   # A
            buttonB = wpi.digitalRead(PIN_B)   # B
            buttonX = wpi.digitalRead(PIN_X)   # X
            buttonY = wpi.digitalRead(PIN_Y)  # Y

            # set values
            cabinectrl.setRemoteValues(buttonA, buttonB, buttonX, buttonY, ljs_x, ljs_y, 1, 0.0, 0.0, 1)
    
    except Exception as e:
        print(f"{e}\nExiting Cabine Control Runner.")
        cabinectrl.cleanup()
        sys.exit(0)


if __name__ == "__main__":
    main()
