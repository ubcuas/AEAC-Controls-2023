# motor specs as a dict
from constants import *

MOTORS = {
    "actuonix_PQ12R_door": {
        "position": "door",
        "frequency": 300, # hz
        "dc_in": 63,     # 30-60%
        "dc_out": 30,
        "channel": CHANNEL4,
        "stroke": 0,   # mm
    },
    "servo_door": {
        "position": "door",
        "frequency": 50,   # hz
        "dc_in": 1,     # 
        "dc_out": 12,
        "channel": CHANNEL0,
    },
    "actuonix_PQ12R_rail": {
        "position": "seat",
        "frequency": 300, # hz
        "dc_in": 63,     # 30-60%
        "dc_out": 30,
        "channel": CHANNEL5,
        "stroke": 0,   # mm
    }
}