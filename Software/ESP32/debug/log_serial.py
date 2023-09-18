import serial
from datetime import datetime
import os
from time import time

usb_port = "/dev/ttyUSB0"
baud = 115200
timeout = 10 * 60  # 10 mins

log_path = os.path.dirname(os.path.realpath(__file__)) + "/logs/"
os.makedirs(log_path, exist_ok=True)
ser = serial.Serial(usb_port, baud)
now = datetime.now().isoformat().replace(':', '-').replace('T', '_')[:19]
log_file = log_path + "log_" + now + ".txt"
with open(log_file, "wb") as f:
    end_t = time.time() + timeout
    while time.time() < end_t:
        try:
            f.write(ser.readline())
        except serial.SerialException as ex:
            f.write("Serial exception: " + ex)
