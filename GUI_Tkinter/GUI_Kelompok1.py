from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
from tkinter import *
import tkinter as tk
import numpy as np
import serial as sr
import time
from PIL import Image,ImageTk
from matplotlib import style
from time import strftime

data1 = np.array([])
data2 = np.array([])
data3 = np.array([])
data4 = np.array([])
cond = False
dataPID = False

fc1="#171F24"
bg1="#03DAC5"
bg2="#CF6679"
fg1="#FFFFFF"
fg2="#000000"
text1="#FFFFFF"
fill2="#171F24"

FontGede=("Gama-Sans", 18)
FontCilik=("Gama-Serif", 12)
FontCilikBgt=("Gama-Serif",11)

# --- Start Serial ---
s = sr.Serial('COM5',9600, timeout=1)
# time.sleep(2)
s.reset_input_buffer()

# -- Plot Data --
def plot_data():
    global cond,data1,data2,data3,data4, stat, dataPID

    if(dataPID == True):
        a = s.readline()
        string = a.decode()
        p = string.split(",")
        kp = float(p[5])
        ki = float(p[6])
        kd = float(p[7])

        canvas.create_text(100, 183, anchor=W, font=(FontCilik),text = kp, fill = text1)
        canvas.create_text(100, 220, anchor=W, font=(FontCilik),text = ki, fill = text1)
        canvas.create_text(100, 260, anchor=W, font=(FontCilik),text = kd, fill = text1)

    if (cond==True and stat == 1):
        a = s.readline()
        string = a.decode()
        p = string.split(",")
        sp = float(p[0])
        pot = float(p[1])
        error = float(p[2])

        if(len(data1) < 100):
            data1 = np.append(data1,sp)
        else:
            data1[0:99] = data1[1:100]
            data1[99] = sp
        
        if(len(data2) < 100):
            data2 = np.append(data2,pot)
        else:
            data2[0:99] = data2[1:100]
            data2[99] = pot
        
        if(len(data3) < 100):
            data3 = np.append(data3,error)
        else:
            data3[0:99] = data3[1:100]
            data3[99] = error

        lines1p.set_xdata(np.arange(0,len(data1)))
        lines1p.set_ydata(data1)
        lines2.set_xdata(np.arange(0,len(data2)))
        lines2.set_ydata(data2)
        lines3.set_xdata(np.arange(0,len(data3)))
        lines3.set_ydata(data3)

        canvas1.draw()
        canvas3.draw()
    
    if(cond == True and stat == 2):
        a = s.readline()
        string = a.decode()
        p = string.split(",")
        sp_b = float(p[3])
        error = float(p[2])
        tacho = float(p[4])
        if(len(data1) < 100):
            data1 = np.append(data1,sp_b)
        else:
            data1[0:99] = data1[1:100]
            data1[99] = sp_b
        
        if(len(data4) < 100):
            data4 = np.append(data4,tacho)
        else:
            data4[0:99] = data4[1:100]
            data4[99] = tacho
        
        if(len(data3) < 100):
            data3 = np.append(data3,error)
        else:
            data3[0:99] = data3[1:100]
            data3[99] = error

        lines1s.set_xdata(np.arange(0,len(data1)))
        lines1s.set_ydata(data1)
        lines4.set_xdata(np.arange(0,len(data4)))
        lines4.set_ydata(data4)
        lines3.set_xdata(np.arange(0,len(data3)))
        lines3.set_ydata(data3)

        canvas2.draw()
        canvas3.draw()
    root.after(1,plot_data)

def plot_start1():
    global cond, stat
    cond = True
    stat = 1
    s.reset_input_buffer()

def plot_start2():
    global cond, stat
    cond = True
    stat = 2
    s.reset_input_buffer()

def plot_stop1():
    global cond, stat
    cond = False
    stat = 1

def plot_stop2():
    global cond, stat
    cond = False
    stat = 2

def updatePID():
    global dataPID
    dataPID = True

style.use("dark_background")

root = tk.Tk()
root.title('GUI')
# root.geometry("1920x1080")
# width= root.winfo_screenwidth()
# height= root.winfo_screenheight()
# root.geometry("%dx%d" % (width, height))
root.attributes('-fullscreen', 1)
root.bind('<Escape>', lambda _: root.destroy())

bg = PhotoImage(file = "bg_bodhi.png")

canvas = Canvas(root, width=1920, height=1080)

canvas.pack(fill = "both", expand = True)

canvas.create_image( 0, 0, image = bg, anchor = "nw")

## -- Create Plot object on GUI --
fig1 = Figure()
fig2 = Figure()
fig3 = Figure()

## Subplot Position
ax = fig1.add_subplot(111, facecolor = fc1)
ax.set_title("Position Control Response")
ax.grid()
# ax.set_xlabel("Time")
# ax.set_ylabel("Setpoint")
ax.set_xlim(0,100)
ax.set_ylim(0,360)
lines1p = ax.plot([],[],label = "SP")[0]
lines2 = ax.plot([],[],label = "Enc_Pot")[0]
ax.legend()

# Subplot Speed
ax2 = fig2.add_subplot(111, facecolor = fc1)
ax2.set_title("Speed Control Response")
ax2.grid()
# ax2.legend()
# ax.set_xlabel("Time")
# ax.set_ylabel("Setpoint")
ax2.set_xlim(0,100)
ax2.set_ylim(0,100)
lines1s = ax2.plot([],[], label = "SP")[0]
lines4 = ax2.plot([],[], label = "Tacho")[0]
ax2.legend()

# Subplot Error
ax3 = fig3.add_subplot(111, facecolor = fc1)
ax3.set_title("Error")
ax3.grid()
# ax3.legend()
# ax2.set_xlabel("Time")
# ax2.set_ylabel("Value")
ax3.set_xlim(0,100)
ax3.set_ylim(-50,50)
lines3 = ax3.plot([],[],label= "Error")[0]
ax3.legend()

judul = "Motor Control GUI"

canvas.pack()

canvas.create_text(720, 35, anchor=W, font=(FontGede),text = judul, fill = text1)

def time():
    string = strftime('%H:%M:%S %p')
    lbl.config(text=string)
    lbl.after(1000, time)
 
def round_rectangle(x1, y1, x2, y2, radius=25, **kwargs):
    
    points = [x1+radius, y1,
              x1+radius, y1,
              x2-radius, y1,
              x2-radius, y1,
              x2, y1,
              x2, y1+radius,
              x2, y1+radius,
              x2, y2-radius,
              x2, y2-radius,
              x2, y2,
              x2-radius, y2,
              x2-radius, y2,
              x1+radius, y2,
              x1+radius, y2,
              x1, y2,
              x1, y2-radius,
              x1, y2-radius,
              x1, y1+radius,
              x1, y1+radius,
              x1, y1]
    return canvas.create_polygon(points, **kwargs, smooth=True)

#Kotak Kelompok
my_rectangle = round_rectangle(850,100,1460,250, radius=20, outline=text1,fill=fill2, stipple='gray50')
canvas.create_text(1020, 160, anchor=W, font=("Gama-sans", 16),text = "Praktikum Sistem Kontrol Lanjut", fill = text1)
canvas.create_text(930, 130, anchor=W, font=("Gama-sans", 16),text = "Teknologi Rekayasa Instrumentasi dan Kontrol 2020", fill = text1)
canvas.create_text(1075, 190, anchor=W, font=("Gama-sans", 16),text = "Fahmizal. S.T., M.Sc", fill = text1)
canvas.create_text(1030, 220, anchor=W, font=("Gama-sans", 16),text = "https://otomasi.sv.ugm.ac.id/", fill = text1)

my_rectangle2 = round_rectangle(850,590,1460,750, radius=20, outline=text1,fill=fill2, stipple='gray50')
canvas.create_text(1100, 610, anchor=W, font=("Gama-Sans",16),text = "Kelompok 1", fill = text1)
canvas.create_text(870, 640, anchor=W, font=(FontCilikBgt),text = "Priyova Muhammad Rafief\t(20/457197/SV/17644)", fill = text1)
canvas.create_text(870, 670, anchor=W, font=(FontCilikBgt),text = "Bodhi Setiawan\t\t(20/464239/SV/18558)", fill = text1)
canvas.create_text(870, 700, anchor=W, font=(FontCilikBgt),text = "Octsana Dhiyaa Warsana\t(20/464253/SV/18572)", fill = text1)
canvas.create_text(870, 730, anchor=W, font=(FontCilikBgt),text = "Karunia Dini Fadillah\t\t(20/464248/SV/18567)", fill = text1)

img2 = Image.open("logokelompok.png")
img2 = img2.resize((100,100), Image.ANTIALIAS)
logo2= ImageTk.PhotoImage(img2)
canvas.create_image(1320,680,anchor=W,image=logo2)
lbl = Label(canvas, font=("Gama-Sans",20, "bold"), background=bg1, foreground='white')

lbl.pack(anchor=NE)
time()

#Kotak PID
my_rectangle = round_rectangle(50,100,170,300, radius=20, outline=text1, fill=fill2, stipple='gray50')
canvas.create_text(75, 130, anchor=W, font=(FontGede),text = "PID Gain", fill = text1)
canvas.create_text(60, 180, anchor=W, font=(FontCilik),text = "Kp :", fill = text1)
canvas.create_text(60, 220, anchor=W, font=(FontCilik),text = "Ki  :", fill = text1)
canvas.create_text(60, 260, anchor=W, font=(FontCilik),text = "Kd :", fill = text1)

img = Image.open("Logo3.png")
img = img.resize((200,47), Image.ANTIALIAS)
logo= ImageTk.PhotoImage(img)
canvas.create_image(50,45,anchor=W,image=logo)

canvas1 = FigureCanvasTkAgg(fig1, master=root)
canvas1.get_tk_widget().place(x=180,y=100,width=600,height=320)
canvas1.draw()

canvas2 = FigureCanvasTkAgg(fig2, master=root)
canvas2.get_tk_widget().place(x=180,y=430,width=600,height=320)
canvas2.draw()

canvas3 = FigureCanvasTkAgg(fig3, master=root)
canvas3.get_tk_widget().place(x=850,y=260,width=615,height=320)
canvas3.draw()

root.update()
start1 = tk.Button(root, text="Start", font=(FontCilik), background = bg1, activebackground=fill2, 
                foreground= fg1, activeforeground= fg2, width=10, command = lambda: plot_start1())
start1.place(x=100,y=340)

root.update()
stop1 = tk.Button(root, text="Stop", font=(FontCilik), background = bg2, activebackground=fill2, 
                foreground= fg1, activeforeground= fg2, width=10, command = lambda: plot_stop1())
stop1.place(x=100, y=start1.winfo_y()+start1.winfo_reqheight()+10)

root.update()
start2 = tk.Button(root, text="Start", font=(FontCilik), background = bg1, activebackground=fill2, 
                foreground= fg1, activeforeground= fg2, width=10, command = lambda: plot_start2())
start2.place(x=100,y=670)

root.update()
stop2 = tk.Button(root, text="Stop", font=(FontCilik), background = bg2, activebackground=fill2, 
                foreground= fg1, activeforeground= fg2,width=10, command = lambda: plot_stop2())
stop2.place(x=100, y=start2.winfo_y()+start2.winfo_reqheight()+10)

update = tk.Button(root, text="PID", font=(FontCilik), background = bg2, activebackground=fill2, 
                    foreground= fg1, activeforeground= fg2, width = 10, command = lambda: updatePID())
update.place(x=60, y=115)

root.after(1,plot_data)
root.mainloop()