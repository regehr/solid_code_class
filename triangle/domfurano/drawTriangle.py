from Tkinter import * 

root = Tk()

canvas = Canvas(width=600, height=200, bg='white')

points = [150, 100, 200, 120, 240, 180, 210, 
    200, 150, 150, 100, 200]

canvas.create_polygon(points, outline='red', fill='green', width=2)
canvas.pack(expand=YES, fill=BOTH)

root.mainloop()
