import time
import sys
import math
import logging
import odroid_wiringpi as wpi
from pwm import PWM
from constants import *
from PCA9685 import PCA9685
from motor_specs import MOTORS

logging.getLogger("Adafruit_I2C.Device.Bus.{0}.Address.{1:#0X}".format(0, 0X40)).setLevel(logging.WARNING)
logging.basicConfig(level=logging.DEBUG)
uaslog = logging.getLogger("UASlogger")

class CabineControl:
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

        self.pwm.setPWMFreq(MOTORS["servo_door"]["frequency"])  # 50 Hz for analog servo
        
        # HEXTRONIK DOOR
        self.hexatronik = PCA9685(channel=MOTORS["servo_door"]["channel"], freq=MOTORS["servo_door"]["frequency"])
        self.hexatronik.reset(self.pwm)
        self.hexatronik.setPWM(self.pwm, dutycycle=MOTORS["servo_door"]["dc_in"])
        
        time.sleep(0.5)     # wait for servo to stop moving before turning off
        self.hexatronik.off(self.pwm)   # turn off to avoid burning servo with high frequency
        self.pwm.setPWMFreq(MOTORS["actuonix_PQ12R_door"]["frequency"]) # set frequency to digital actuators

        # ACTUONIX DOOR
        self.actuonix_door = PCA9685(channel=MOTORS["actuonix_PQ12R_door"]["channel"], freq=MOTORS["actuonix_PQ12R_door"]["frequency"])
        self.actuonix_door.reset(self.pwm)
        self.actuonix_door.setPWM(self.pwm, dutycycle=MOTORS["actuonix_PQ12R_door"]["dc_in"])

        time.sleep(0.5)
        self.actuonix_door.off(self.pwm)

        # ACTUONIX RAIL
        self.actuonix_rail = PCA9685(channel=MOTORS["actuonix_PQ12R_rail"]["channel"], freq=MOTORS["actuonix_PQ12R_rail"]["frequency"])
        self.actuonix_rail.reset(self.pwm)
        self.actuonix_rail.setPWM(self.pwm, dutycycle=MOTORS["actuonix_PQ12R_rail"]["dc_in"])
        
        time.sleep(0.5) # let actuator move before switching freq
        self.actuonix_rail.off(self.pwm)

        uaslog.info("Motor System init complete! Starting main routine...")
    
    def controlLoop(self):
        try:
            uaslog.info("Starting Cabine Control Routine...")

            while True:
                self.pwm.setPWMFreq(MOTORS["servo_door"]["frequency"])

                dc = int(input("Enter Duty Cycle for Servo 1 [1,12]: "))
                uaslog.info("Motor Position at DC {}".format(dc))
                self.hexatronik.setPWM(self.pwm, dutycycle=dc)

                time.sleep(0.5)     # wait for servo to stop moving before turning off
                self.hexatronik.off(self.pwm)   # turn off to avoid burning servo with high frequency
                self.pwm.setPWMFreq(MOTORS["actuonix_PQ12R_door"]["frequency"])

                dc = int(input("Enter Duty Cycle for Actuonix 1 [30,63]: "))
                uaslog.info("Motor Position at DC {}".format(dc))
                self.actuonix_door.setPWM(self.pwm, dutycycle=dc)

                time.sleep(0.5)
                self.actuonix_door.off(self.pwm)

                dc = int(input("Enter Duty Cycle for Actuonix 2 [30,63]: "))
                uaslog.info("Motor Position at DC {}".format(dc))
                self.actuonix_rail.setPWM(self.pwm, dutycycle=dc)

                time.sleep(0.5) # let actuator move before switching freq
                self.actuonix_rail.off(self.pwm)
                
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
        self.actuonix_door.reset(self.pwm)
        self.actuonix_rail.reset(self.pwm)

        # unexport pins
        for pin in range(0, 256):
            file = open("/sys/class/gpio/unexport","w")
            file.write(str(pin))
        
        uaslog.info("Driver system cleanup complete!")

def main():
    control = CabineControl()
    control.controlLoop()

if __name__ == "__main__":
    main()