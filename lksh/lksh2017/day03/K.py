n = int(input())


location = "none"
speedlimit = float("inf")
overtake = "allowed"

for i in range(n):
	s = input().split()
	
	if (s[0] == "Info"):
		print("current location:", location) 
		print("current speed limit: ", end = '')
		if (location == "none"):
			print(min(speedlimit, 90))
		else:
			print(min(speedlimit, 60))
		print("overtake is", overtake)
		print()

	if (s[0] == "Begin"):
		location = s[2]
	if (s[0] == "End"):
		location = "none"
	if (s[0] == "Speed"):
		speedlimit = int(s[2])
	if (s[0] == "No" and s[1] == "speed"):
		speedlimit = float("inf")
	if (s[0] == "No" and s[1] == "overtaking"):
		overtake = "not allowed"
	if (s[0] == "Overtaking"):
		overtake = "allowed"
	if (s[0] == "No" and s[1] == "restriction"):
		speedlimit = float("inf")
		overtake = "allowed"