import sys
sys.stdout = open("easy.out", 'w')
with open('easy.in', 'r') as file_in:
    a,b,c = map(int,file_in.readline().split())
l=-1
r=max(b,c)*a
a-=1
while r-l>1:
    m=(l+r)//2
    if m//b+m//c>=a:
        r=m
    else:
        l=m
print(r+min(b,c))
sys.stdout.close()