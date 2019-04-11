a, b = [int(i) for i in input().split()]
a *= 10 ** 19
print('0', (a // 10) // b + ((a // b) % 10 >= 5), sep = '.')