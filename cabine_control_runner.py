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
            # get updated values (done from software side when importing cabine control as submodule)
            cabinectrl.arm = int(input("[0] to un-secure cabin\n [1] to secure cabin\n"))
            
    except Exception as e:
        print(f"{e}\nExiting Cabine Control Runner.")
        cabinectrl.cleanup()
        sys.exit(0)


if __name__ == "__main__":
    main()
