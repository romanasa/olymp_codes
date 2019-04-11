from PIL import Image
im = Image.open("m.png")


h, w = im.size

matr = [[0] * w for i in range(h)]

for i in range(h):
	for j in range(w):
		matr[i][j] = im.getpixel((i, j)))
		
for i in range(0, h, 100):
	for j in range(0, w, 100):
