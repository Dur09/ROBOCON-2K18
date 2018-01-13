flag=0
cf = 25
CLK  = 18
MISO = 23
MOSI = 24
node = 0
CS =[25, 22, 27, 10]
mcp = [Adafruit_MCP3008.MCP3008(clk = CLK, cs = CS[0], miso = MISO, mosi = MOSI)] * 4

for i in range(4):
	mcp[i] = Adafruit_MCP3008.MCP3008(clk=CLK, cs=CS[i], miso=MISO, mosi=MOSI)
avg = [[0 for i in range(8)] for j in range(4)]
bi = [[0 for i in range(8)] for j in range(4)]
values = [[0 for i in range(8)] for j in range(4)]

motordir = [6,4,2,19]
motorpwm = [13,17,8,26]
motorin =[0,0,0,0]
sp =[55,50,50,60]
