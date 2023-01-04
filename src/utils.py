import sys
# sys.path.append('./aeac_controls_2022/')
from constants import COUNT_SIZE

# calculate OFF count from duty cycle and delay %
def getCounterValues(delay, dc):
    on_count = round(delay*COUNT_SIZE/100)
    off_count = on_count + round(dc*COUNT_SIZE/100)

    return on_count, off_count

def pwmToDc(range):
    return (100*(range + 1)/256)