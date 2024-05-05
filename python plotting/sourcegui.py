# -*- coding: utf-8 -*-
"""
Created on Fri Apr 26 14:02:21 2024

@author: ihipt
"""

import tkinter as tk
from gui import GUI
import numpy as np
from numpy import linalg as nl
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg)

class sourceGUI(GUI):
    def windowType(self):
        self.window = tk.Toplevel()
    def setTitle(self):
        self.window.title("Create Source")
    def buttons(self):
        self.createSourceButton = tk.Button(master=self.middleFrame,
                                            text="Create Source",
                                            command=self.createSource,
                                            width=12)
    def createSource(self):
        source = {}
        source['name'] = self.nameVal
        source['numrays'] = self.numrays
        self.createSource2d()
        self.collectVector()
        self.generateBeam()
        source['location'] = self.Pnew
        source['unit'] = self.V
        self.masterClass.sources.append(source)
        self.masterClass.plotSources()
        self.window.destroy()
    def generateBeam(self):
        self.v /= nl.norm(self.v)
        costheta = np.dot([0,0,1],self.v)
        theta = np.arccos(costheta)
        u = np.cross([0,0,1],self.v)
        Su = [[0,-u[2],u[1]],
              [u[2],0,-u[0]],
              [-u[1],u[0],0]]
        k = (1-costheta)/theta**2
        Su2 = np.multiply(Su,Su)
        R = np.eye(3) + Su + k*Su2
        self.Pnew = np.multiply(R,self.P)
        # self.Pnew = np.einsum('ijk,ji->ki',rotationMatrix,self.P)
        self.V = np.repeat(self.v[:,np.newaxis],self.numrays,1)
    def labels(self):
        self.densityLabel = tk.Label(master=self.densityFrame,
                                     text="Density",
                                     width=10)
        self.xLabel = tk.Label(master=self.xFrame,
                               text="X",
                               width=10)
        self.yLabel = tk.Label(master=self.yFrame,
                               text="Y",
                               width=10)
        self.divergenceLabel = tk.Label(master=self.divergenceFrame,
                                        text="Divergence",
                                        width=10)
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
                                     width=3)
        self.xEntry = tk.Entry(master=self.xFrame,
                               textvariable=self.xVal,
                               width=3)
        self.yEntry = tk.Entry(master=self.yFrame,
                               textvariable=self.yVal,
                               width=3)
        self.divergenceEntry = tk.Entry(master=self.divergenceFrame,
                                        textvariable=self.divergenceVal,
                                        width=3)
        self.directionXEntry = tk.Entry(master=self.directionXFrame,
                                        textvariable=self.directionXVal,
                                        width=5)
        self.directionYEntry = tk.Entry(master=self.directionYFrame,
                                        textvariable=self.directionYVal,
                                        width=5)
        self.directionZEntry = tk.Entry(master=self.directionZFrame,
                                        textvariable=self.directionZVal,
                                        width=5)
        self.nameEntry = tk.Entry(master=self.leftFrame,
                                        textvariable=self.nameVal,
                                        width=15)
    def entryVals(self):
        self.densityVal = tk.StringVar()
        self.xVal = tk.StringVar()
        self.yVal = tk.StringVar()
        self.divergenceVal = tk.StringVar()
        self.directionXVal = tk.StringVar()
        self.directionYVal = tk.StringVar()
        self.directionZVal = tk.StringVar()
        self.nameVal = tk.StringVar()
    def optionVals(self):
        self.circleVal = tk.StringVar()
        self.pointVal = tk.StringVar()
        self.circleOptions = ["Circle","Rectangle"]
        self.pointOptions = ["Point","Beam"]
    def optionMenus(self):
        self.optionVals()
        self.circleOptionMenu = tk.OptionMenu(self.leftFrame,
                                              self.circleVal,
                                              *self.circleOptions,
                                              command=self.fixY)
        self.pointOptionMenu = tk.OptionMenu(self.leftFrame,
                                              self.pointVal,
                                              *self.pointOptions)
    def callbacks(self):
        self.densityVal.trace("w",self.plotScatter)
        self.xVal.trace("w", self.plotScatter)
        self.yVal.trace("w", self.plotScatter)
        self.divergenceVal.trace("w", self.plotDivergence)
        self.directionXVal.trace("w",self.plotVector)
        self.directionYVal.trace("w",self.plotVector)
        self.directionZVal.trace("w",self.plotVector)
    def fixY(self,chosenOption):
        if chosenOption=="Circle":
            self.yEntry.config(state="disabled")
        else:
            self.yEntry.config(state="normal")
    def defaults(self):
        self.densityEntry.insert(0,"1")
        self.xEntry.insert(0,"10")
        self.yEntry.insert(0,"5") # default state is circle
        self.divergenceEntry.insert(0,"20")
        self.directionXEntry.insert(0,"0")
        self.directionYEntry.insert(0,"0")
        self.directionZEntry.insert(0,"1")
        self.circleVal.set("Rectangle")
        self.pointVal.set("Point")
        self.nameVal.set("Source1")
    def createSource2d(self):
        if not self.collectwhd():
            return False
        raysPerX = int(np.sqrt(self.density)*self.width)
        raysPerY = int(np.sqrt(self.density)*self.height)
        x = np.linspace(-self.width/2,self.width/2,raysPerX)
        y = np.linspace(-self.height/2,self.height/2,raysPerY)
        self.numrays = raysPerX*raysPerY
        self.X = np.repeat(x,raysPerY)
        self.Y = np.tile(y,raysPerX)
        self.Z = np.zeros((1,self.numrays))
        self.P = np.vstack((self.X,self.Y,self.Z))
        return True
    def collectwhd(self):
        try:
            self.density = float(self.densityVal.get())
            self.width = int(self.xVal.get())
            self.height = int(self.yVal.get())
        except:
            return False
        return self.density>0 and self.width>0 and self.height>0
    def plotScatter(self,var=None,index=None,mode=None):
        if not self.createSource2d():
            return
        try:
            self.scatterHandle.remove()
        except:
            pass
        self.scatterHandle = self.scatterPlot.scatter(self.X,self.Y)
        self.scatterPlot.set_xlim(self.X.min()-1,self.X.max()+1)
        self.scatterPlot.set_ylim(self.Y.min()-1,self.Y.max()+1)
        self.scatterCanvas.draw()
    def collectVector(self):
        try:
            self.x = float(self.directionXVal.get())
        except:
            self.x = 0
        try:
            self.y = float(self.directionYVal.get())
        except:
            self.y = 0
        try:
            self.z = float(self.directionZVal.get())
        except:
            self.z = 0
        self.v = np.array([self.x,self.y,self.z])
    def plotVector(self,var=None,index=None,mode=None):
        self.collectVector()
        try:
            self.quiverAxes.remove()
            self.quiverVector.remove()
        except:
            pass
        self.quiverAxes = self.vectorPlot.quiver([0,0,0],
                               [0,0,0],
                               [0,0,0],
                               [0.5,0,0],
                               [0,0.5,0],
                               [0,0,0.5])
        self.quiverVector = self.vectorPlot.quiver([0],[0],[0],
                                                   [self.x],
                                                   [self.y],
                                                   [self.z],
                               normalize=True)
        self.vectorPlot.scatter([0],[0],[0])
        self.vectorCanvas.draw()
    def plotDivergence(self,var=None,index=None,mode=None):
        angleStr = self.divergenceVal.get()
        if angleStr == '':
            return
        else:
            angle = float(angleStr)
        angle *= np.pi/180 # convert degrees to radians
        h = np.tan(angle/2) #height
        try:
            self.divergenceQuiver.remove()
        except:
            pass
        # normalize manually
        l = np.sqrt(1+h**2)
        self.divergenceQuiver = self.divergencePlot.quiver(
            [0,0],[0,0],[-1/l,-1/l],[h/l,-h/l],scale=4)
        self.divergencePlot.get_xaxis().set_visible(False)
        self.divergencePlot.get_yaxis().set_visible(False)
        self.divergencePlot.set_xlim(-1,0.1)
        self.divergencePlot.set_ylim(-1.1,1.1)
        self.divergenceCanvas.draw()
    def initialisePlots(self):
        self.initialiseScatterPlot()
        self.initialiseVectorPlot()
        self.initialiseDivergencePlot()
    def initialiseScatterPlot(self):
        self.scatterFig = Figure(figsize=(3,3))
        self.scatterPlot = self.scatterFig.add_subplot(111)
        self.scatterPlot.set_aspect('equal')
        self.scatterCanvas = FigureCanvasTkAgg(self.scatterFig,
                                            master=self.middleFrame)
        self.plotScatter()
    def initialiseVectorPlot(self):
        self.vectorFig = Figure(figsize=(3,3))
        self.vectorPlot = self.vectorFig.add_subplot(projection='3d')
        self.vectorPlot.set_xlim(-1,1)
        self.vectorPlot.set_ylim(-1,1)
        self.vectorPlot.set_zlim(-1,1)
        self.vectorCanvas = FigureCanvasTkAgg(self.vectorFig,
                                                master=self.rightFrame)
        self.plotVector()
    def initialiseDivergencePlot(self):
        self.divergenceFig = Figure(figsize=(3,2))
        self.divergencePlot = self.divergenceFig.add_subplot()
        self.divergenceCanvas = FigureCanvasTkAgg(self.divergenceFig,
                                                  master=self.middleFrame)
        self.plotDivergence()
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
        self.nameEntry.pack()
        self.leftFrame.grid(row=0,column=0)
    def packMiddleFrame(self):
        self.scatterCanvas.get_tk_widget().pack()
        self.divergenceCanvas.get_tk_widget().pack()
        self.createSourceButton.pack()
        self.middleFrame.grid(row=0,column=1)
    def packRightFrame(self):
        self.directionLabel.pack()
        self.packDirectionXFrame()
        self.packDirectionYFrame()
        self.packDirectionZFrame()
        self.vectorCanvas.get_tk_widget().pack()
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