import RPi.GPIO as io
import time
from valuesnpins import *
from motion import *
def main():
		motor()
		print "going forward:"
		forward()
		time.sleep(3)

if __name__ == "__main__":
		main()
