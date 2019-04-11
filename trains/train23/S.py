import sys
sys.stdin = open('subtract.in')
sys.stdout = open('subtract.out', 'w')

a, b = [int(i) for i in input().split()]
print(a - b)
