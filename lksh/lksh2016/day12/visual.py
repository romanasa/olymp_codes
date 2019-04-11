from tkinter import *
import sys

root = Tk()
R = 10

fin = open('input.txt')

p = [list(map(lambda x : int(x) * 50 + 50, line.split())) for line in fin.readlines()]
history = []

def f_redraw():
	w.delete(ALL)
	for i in range(len(p)):
		j = (i + 1) % len(p)
		w.create_line(p[i][0], p[i][1], p[j][0], p[j][1], fill="red")
	# enumerate([x, y, z]) = [(0, x), (1, y), (2, z)]
	for i, (x, y) in enumerate(p):
		w.create_oval(x - R, y - R, x + R, y + R, 
			fill="green", outline="#00aa00")
		w.create_text(x, y, fill="white", 
			text=str(i+1), justify=CENTER, font="Courier 10 bold")
	                          
w = Canvas(root, width=400, height=400)

f_redraw()

w.pack()

root.mainloop()