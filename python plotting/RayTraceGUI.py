# -*- coding: utf-8 -*-
"""
Created on Tue Mar 19 18:06:37 2024

@author: ihipt
"""

import tkinter as tk
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg,NavigationToolbar2Tk)

class GUI():
    def __init__(self):
        self.windowType()
        self.setTitle()
        self.frames()
        self.buttons()
        self.labels()
        self.entries()
        self.lamps()
        self.defaults()
        self.initialisePlot()
        self.pack()
        self.mainloop()
    def windowType(self):
        self.window = tk.Tk()
    def setTitle(self):
        self.window.title("New Window")
    def mainloop(self):
        pass
    def frames(self):
        pass
    def buttons(self):
        pass
    def plot(self):
        pass
    def labels(self):
        pass
    def entries(self):
        pass
    def entryVals(self):
        pass
    def lamps(self):
        pass
    def defaults(self):
        pass
    def initialisePlot(self):
        pass
    def pack(self):
        pass
        
        
        

class mainGUI(GUI):
    def mainloop(self):
        self.window.mainloop()
    def setTitle(self):
        self.window.title("Ray Trace")
    def buttons(self):
        self.sourceButton = tk.Button(master=self.window,text="Create Source",command=self.createSource)
        self.plotButton = tk.Button(master=self.window,text="Plot",command=self.plot)
    def plot(self):
        y = [i**2 for i in range(int("15"))]
        self.plot1.plot(y)
        self.plotCanvas.draw()
    def initialisePlot(self):
        self.fig = Figure(figsize=(5,5),dpi=100)
        self.plot1 = self.fig.add_subplot(111)
        self.plotCanvas = FigureCanvasTkAgg(self.fig,master=self.window)
        self.plot()
    def pack(self):
        self.sourceButton.pack()
        self.plotButton.pack()
        self.plotCanvas.get_tk_widget().pack()
        toolbar = NavigationToolbar2Tk(self.plotCanvas,self.window)
        toolbar.update()
        self.plotCanvas.get_tk_widget().pack()
    def createSource(self):
        self.sourceWindow = sourceGUI()
        

class sourceGUI(GUI):
    def windowType(self):
        self.window = tk.Toplevel()
    def setTitle(self):
        self.window.title("Create Source")
    def buttons(self):
        self.circleButton = tk.Button(master=self.window,text="Circle",command=self.makeCircle)
        self.rectangleButton = tk.Button(master=self.window,text="Rectangle",command=self.makeRectangle)
        self.pointButton = tk.Button(master=self.window,text="Point",command=self.makePoint)
        self.beamButton = tk.Button(master=self.window,text="Beam",command=self.makeBeam)
    def makeCircle(self):
        self.circleCanvas.itemconfig(self.circleLamp,state=tk.NORMAL)
        self.rectangleCanvas.itemconfig(self.rectangleLamp,state=tk.HIDDEN)
    def makeRectangle(self):
        self.circleCanvas.itemconfig(self.circleLamp,state=tk.HIDDEN)
        self.rectangleCanvas.itemconfig(self.rectangleLamp,state=tk.NORMAL)
    def makePoint(self):
        self.pointCanvas.itemconfig(self.pointLamp,state=tk.NORMAL)
        self.beamCanvas.itemconfig(self.beamLamp,state=tk.HIDDEN)
    def makeBeam(self):
        self.pointCanvas.itemconfig(self.pointLamp,state=tk.HIDDEN)
        self.beamCanvas.itemconfig(self.beamLamp,state=tk.NORMAL)
    def labels(self):
        self.densityLabel = tk.Label(master=self.window,text="Density")
        self.xLabel = tk.Label(master=self.window,text="X (diameter)")
        self.yLabel = tk.Label(master=self.window,text="Y")
        self.divergenceLabel = tk.Label(master=self.window,text="Divergence(deg)")
    def entries(self):
        self.entryVals()
        self.densityEntry = tk.Entry(master=self.window,width=5)
        self.xEntry = tk.Entry(master=self.window,textvariable=self.xVal,width=15)
        self.yEntry = tk.Entry(master=self.window,width=15)
        self.divergenceEntry = tk.Entry(master=self.window,width=15)
    def entryVals(self):
        self.densityVal = tk.StringVar()
        self.xVal = tk.StringVar()
        self.yVal = tk.StringVar()
        self.divergenceVal = tk.StringVar()
    def lamps(self):
        '''Circle lamp'''
        self.circleCanvas = tk.Canvas(self.window, width=10, height=10)
        self.circleLamp = self.circleCanvas.create_oval(2,2,10,10)
        self.circleCanvas.itemconfig(self.circleLamp,fill="red",outline="black",state=tk.NORMAL)
        '''Rectangle lamp'''
        self.rectangleCanvas = tk.Canvas(self.window, width=10, height=10)
        self.rectangleLamp = self.rectangleCanvas.create_rectangle(2,2,10,10)
        self.rectangleCanvas.itemconfig(self.rectangleLamp,fill="red",outline="black",state=tk.HIDDEN)
        '''Point lamp'''
        self.pointCanvas = tk.Canvas(self.window, width=10, height=10)
        self.pointLamp = self.pointCanvas.create_oval(2,2,10,10)
        self.pointCanvas.itemconfig(self.pointLamp,fill="red",outline="black",state=tk.NORMAL)
        '''Beam lamp'''
        self.beamCanvas = tk.Canvas(self.window, width=10, height=10)
        self.beamLamp = self.beamCanvas.create_oval(2,2,10,10)
        self.beamCanvas.itemconfig(self.beamLamp,fill="red",outline="black",state=tk.HIDDEN)
    def defaults(self):
        self.densityEntry.insert(0,"5")
        self.xEntry.insert(0,"15")
        self.yEntry.insert(0,"10")
        self.divergenceEntry.insert(0,"0")
    def pack(self):
        self.densityLabel.grid(row=1,column=0)
        self.densityEntry.grid(row=1,column=1)
        self.circleButton.grid(row=2,column=0)
        self.circleCanvas.grid(row=2,column=1)
        self.rectangleButton.grid(row=3,column=0)
        self.rectangleCanvas.grid(row=3,column=1)
        self.xLabel.grid(row=4,column=0)
        self.xEntry.grid(row=4,column=1)
        self.yLabel.grid(row=5,column=0)
        self.yEntry.grid(row=5,column=1)
        self.pointButton.grid(row=6,column=0)
        self.pointCanvas.grid(row=6,column=1)
        self.beamButton.grid(row=7,column=0)
        self.beamCanvas.grid(row=7,column=1)
        self.divergenceLabel.grid(row=8,column=0)
        self.divergenceEntry.grid(row=8,column=1)
        
        
app = mainGUI()