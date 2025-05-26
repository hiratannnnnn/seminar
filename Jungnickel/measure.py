import subprocess
import time
import psutil
import sys

def measure_program(cmd):
	start	= time.time()
	proc	= subprocess.Popen(cmd)
	p		= psutil.Process(proc.pid)
	peak	= 0
	while proc.poll() is None:
		try:
			mem = p.memory_info().rss
			if mem > peak:
				peak = mem
		except psutil.NoSuchProcess:
			break
		time.sleep(0.01)
	end 	= time.time()
	print(f"Running the program took: {end - start:.3f} sec")
	print(f"Maximum memory allocation: {peak // 1024} KB")

if __name__ == "__main__":
	if len(sys.argv) < 2:
		print("Usage: python measure.py <command> [args...]")
		sys.exit(1)
	measure_program(sys.argv[1:])
