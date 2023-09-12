import serial
from datetime import datetime
import os

usb_port = "/dev/ttyUSB0"
baud = 115200

log_path = os.path.dirname(os.path.realpath(__file__)) + "/logs/"
os.makedirs(log_path, exist_ok=True)
ser = serial.Serial(usb_port, baud)
now = datetime.now().isoformat().replace(':', '-').replace('T', '_')[:19]
log_file = log_path + "log_" + now + ".txt"
with open(log_file, "wb") as f:
    while True:
        f.write(ser.readline())
