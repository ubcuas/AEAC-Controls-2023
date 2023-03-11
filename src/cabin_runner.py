import sys
import logging
import threading
sys.path.append('./AEAC-Controls-2023/src/')
from cabin_control import CabinControl

logging.basicConfig(level=logging.DEBUG)
uaslog = logging.getLogger("UASlogger")

def main():
    cabinctrl = CabinControl('COM9', 'COM8')

    cabin_thread = threading.Thread(target=cabinctrl.controlLoop, daemon=True)
    cabin_thread.start()

    # serial_com.setCabinState()

    try:
        while True:
            val = input("[0] Disarm cabin\n[1] Arm Cabin\r\n")
            cabinctrl.setCabinState(val)

    except KeyboardInterrupt as e:
        cabinctrl.cleanup()   # TODO: use in child thread
        uaslog.info("Terminating Cabin Runner.\r\n")
        sys.exit(0)


if __name__ == "__main__":
    main()