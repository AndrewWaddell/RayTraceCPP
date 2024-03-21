# -*- coding: utf-8 -*-
"""
Created on Tue Mar 19 18:06:37 2024

@author: ihipt
"""

import tkinter as tk
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg,
                                               NavigationToolbar2Tk)

class GUI():
    def __init__(self,masterClass=False):
        self.masterClass = masterClass
        self.windowType()
        self.initialiseData()
        self.setTitle()
        self.frames()
        self.buttons()
        self.labels()
        self.entries()
        self.optionMenus()
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
    def initialiseData(self):
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
    def optionMenus(self):
        pass
    def entryVals(self):
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
        self.sourceButton = tk.Button(master=self.window,
                                      text="Create Source",
                                      command=self.createSource)
        self.plotButton = tk.Button(master=self.window,
                                    text="Plot",
                                    command=self.plot)
    def initialiseData(self):
        self.sources = []
    def plot(self):
        print(self.sources)
        y = [i**2 for i in range(int("15"))]
        self.plot1.plot(y)
        self.plotCanvas.draw()
    def initialisePlot(self):
        self.fig = Figure(figsize=(5,5),dpi=100)
        self.plot1 = self.fig.add_subplot(111)
        self.plotCanvas = FigureCanvasTkAgg(self.fig,
                                            master=self.window)
        self.plot()
    def pack(self):
        self.sourceButton.pack()
        self.plotButton.pack()
        self.plotCanvas.get_tk_widget().pack()
        toolbar = NavigationToolbar2Tk(self.plotCanvas,self.window)
        toolbar.update()
        self.plotCanvas.get_tk_widget().pack()
    def createSource(self):
        self.sourceWindow = sourceGUI(self)
            

class sourceGUI(GUI):
    def windowType(self):
        self.window = tk.Toplevel()
    def setTitle(self):
        self.window.title("Create Source")
    def buttons(self):
        self.createSourceButton = tk.Button(master=self.window,
                                            text="Create Source",
                                            command=self.createSource,
                                            width=12)
    def createSource(self):
        source = {}
        source['density'] = self.densityVal.get()
        source['x'] = self.xVal.get()
        source['y'] = self.yVal.get()
        source['divergence'] = self.divergenceVal.get()
        source['circle'] = self.circleVal.get()
        source['point'] = self.pointVal.get()
        self.masterClass.sources.append(source)
        self.window.destroy()
    def labels(self):
        self.densityLabel = tk.Label(master=self.densityFrame,
                                     text="Density")
        self.xLabel = tk.Label(master=self.xFrame,
                               text="X")
        self.yLabel = tk.Label(master=self.yFrame,
                               text="Y")
        self.divergenceLabel = tk.Label(master=self.divergenceFrame,
                                        text="Divergence")
        self.directionLabel = tk.Label(master=self.rightFrame,
                                       text="Direction")
        self.directionXLabel = tk.Label(master=self.directionXFrame,
                                        text="X")
        self.directionYLabel = tk.Label(master=self.directionYFrame,
                                        text="Y")
        self.directionZLabel = tk.Label(master=self.directionZFrame,
                                        text="Z")
    def frames(self):
        self.leftFrame = tk.Frame(master=self.window)
        self.middleFrame = tk.Frame(master=self.window)
        self.rightFrame = tk.Frame(master=self.window)
        self.densityFrame = tk.Frame(master=self.leftFrame)
        self.xFrame = tk.Frame(master=self.leftFrame)
        self.yFrame = tk.Frame(master=self.leftFrame)
        self.divergenceFrame = tk.Frame(master=self.leftFrame)
        self.directionXFrame = tk.Frame(master=self.rightFrame)
        self.directionYFrame = tk.Frame(master=self.rightFrame)
        self.directionZFrame = tk.Frame(master=self.rightFrame)
    def entries(self):
        self.entryVals()
        self.densityEntry = tk.Entry(master=self.densityFrame,
                                     textvariable=self.densityVal,
                                     width=5)
        self.xEntry = tk.Entry(master=self.xFrame,
                               textvariable=self.xVal,
                               width=5)
        self.yEntry = tk.Entry(master=self.yFrame,
                               textvariable=self.yVal,
                               width=5)
        self.divergenceEntry = tk.Entry(master=self.divergenceFrame,
                                        width=5)
        self.directionXEntry = tk.Entry(master=self.directionXFrame,
                                        width=5)
        self.directionYEntry = tk.Entry(master=self.directionYFrame,
                                        width=5)
        self.directionZEntry = tk.Entry(master=self.directionZFrame,
                                        width=5)
    def entryVals(self):
        self.densityVal = tk.StringVar()
        self.xVal = tk.StringVar()
        self.yVal = tk.StringVar()
        self.divergenceVal = tk.StringVar()
        self.directionXVal = tk.StringVar()
        self.directionYVal = tk.StringVar()
        self.directionZVal = tk.StringVar()
    def optionVals(self):
        self.circleVal = tk.StringVar()
        self.pointVal = tk.StringVar()
        self.circleOptions = ["Circle","Rectangle"]
        self.pointOptions = ["Point","Beam"]
    def optionMenus(self):
        self.optionVals()
        self.circleOptionMenu = tk.OptionMenu(self.leftFrame,
                                              self.circleVal,
                                              *self.circleOptions)
        self.pointOptionMenu = tk.OptionMenu(self.leftFrame,
                                              self.pointVal,
                                              *self.pointOptions)
    def defaults(self):
        self.densityEntry.insert(0,"5")
        self.xEntry.insert(0,"15")
        self.yEntry.insert(0,"10")
        self.divergenceEntry.insert(0,"0")
        self.directionXEntry.insert(0,"0")
        self.directionYEntry.insert(0,"0")
        self.directionZEntry.insert(0,"1")
        self.circleVal.set("Circle")
        self.pointVal.set("Point")
    def pack(self):
        self.packLeftFrame()
        self.packMiddleFrame()
        self.packRightFrame()
    def packLeftFrame(self):
        self.packDensityFrame()
        self.circleOptionMenu.pack()
        self.packXFrame()
        self.packYFrame()
        self.pointOptionMenu.pack()
        self.packDivergenceFrame()
        self.leftFrame.grid(row=0,column=0)
    def packMiddleFrame(self):
        # pack scatter plot no toolbar
        # pack divergence plot no toolbar
        self.middleFrame.grid(row=0,column=1)
    def packRightFrame(self):
        self.directionLabel.pack()
        self.packDirectionXFrame()
        self.packDirectionYFrame()
        self.packDirectionZFrame()
        # pack vector diagram no toolbar
        self.rightFrame.grid(row=0,column=2)
    def packDensityFrame(self):
        self.densityLabel.grid(row=0,column=0)
        self.densityEntry.grid(row=0,column=1)
        self.densityFrame.pack()
    def packXFrame(self):
        self.xLabel.grid(row=0,column=0)
        self.xEntry.grid(row=0,column=1)
        self.xFrame.pack()
    def packYFrame(self):
        self.yLabel.grid(row=0,column=0)
        self.yEntry.grid(row=0,column=1)
        self.yFrame.pack()
    def packDivergenceFrame(self):
        self.divergenceLabel.grid(row=0,column=0)
        self.divergenceEntry.grid(row=0,column=1)
        self.divergenceFrame.pack()
    def packDirectionXFrame(self):
        self.directionXLabel.grid(row=0,column=0)
        self.directionXEntry.grid(row=0,column=1)
        self.directionXFrame.pack()
    def packDirectionYFrame(self):
        self.directionYLabel.grid(row=0,column=0)
        self.directionYEntry.grid(row=0,column=1)
        self.directionYFrame.pack()
    def packDirectionZFrame(self):
        self.directionZLabel.grid(row=0,column=0)
        self.directionZEntry.grid(row=0,column=1)
        self.directionZFrame.pack()
        
app = mainGUI()