def read_sensor(i):
	index = 0
	for j in range(8):
		if i == 2:
			index = 7 - j
		else:
			index = j
		values[i][index] = mcp[i].read_adc(index)
