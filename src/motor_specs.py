# motor specs as a dict

MOTORS = {
    "actuonix_PQ12R_door": {
        "position": "door",
        "frequency": 300, # hz
        "dc_low": 60,     # 30-60%
        "dc_high": 30,
        "driver_pins": [], # pwm1, pwm2
        "stroke": 0,   # mm
    },
    "servo_door": {
        "position": "door",
        "frequency": 300,   # hz
        "dc_low": 28,     # 28-64%
        "dc_high": 64,
    },
    "actuonix_PQ12R_rails": {
        "position": "seat",
        "frequency": 300, # hz
        "dc_low": 60,     # 30-60%
        "dc_high": 30,
        "driver_pins": [], # pwm1, pwm2
        "stroke": 0,   # mm
    }
}