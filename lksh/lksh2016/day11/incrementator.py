import sys
sys.setrecursionlimit(100500)

fin = open('incrementator.in')
fout = open('incrementator.out', 'w')

M = {}

for line in fin.readlines():
	a, b = line.split()        
	M[a] = M.get(a, 0) + int(b)
	print(M[a], file = fout)