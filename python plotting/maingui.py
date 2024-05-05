# -*- coding: utf-8 -*-
"""
Created on Fri Apr 26 14:01:18 2024

@author: ihipt
"""

import tkinter as tk
from sourcegui import sourceGUI
from loadingbox import loadingBox
from gui import GUI
import subprocess
from matplotlib.figure import Figure
import numpy as np
from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg,
                                               NavigationToolbar2Tk)

class mainGUI(GUI):
    def mainloop(self):
        self.window.mainloop()
    def setTitle(self):
        self.window.title("Ray Trace")
    def buttons(self):
        self.sourceButton = tk.Button(master=self.window,
                                      text="Create Source",
                                      command=self.createSource)
        self.traceButton = tk.Button(master=self.window,
                                    text="Trace",
                                    command=self.trace)
    def initialiseData(self):
        self.sources = []
        self.traceCpp = r"C:\Users\ihipt\Documents\1Ray_Optics_Application\Code\cpp\RayTraceCpp\bin\RayTrace.exe"
    def pack(self):
        self.sourceButton.pack()
        self.traceButton.pack()
        self.vectorCanvas.get_tk_widget().pack()
        self.packToolbar()
    def packToolbar(self):
        toolbar = NavigationToolbar2Tk(self.vectorCanvas,self.window)
        toolbar.update()
        self.vectorCanvas.get_tk_widget().pack()
    def createSource(self):
        self.sourceWindow = sourceGUI(self)
    def trace(self):
        self.loading = loadingBox()
        self.save()
        subprocess.run([self.traceCpp])
        self.loading.destroy()
    def save(self): # save data in the files
        pass
    def plotSources(self):
        x = np.array([])
        y = np.array([])
        z = np.array([])
        dx = np.array([])
        dy = np.array([])
        dz = np.array([])
        for source in self.sources:
            x = np.append(x,source['location'][0])
            y = np.append(y,source['location'][1])
            z = np.append(z,source['location'][2])
            dx = np.append(dx,source['unit'][0])
            dy = np.append(dy,source['unit'][1])
            dz = np.append(dz,source['unit'][2])
        try:
            self.quiverAxes.remove()
        except:
            pass
        xdiff = np.max(x)-np.min(x)
        ydiff = np.max(y)-np.min(y)
        zdiff = np.max(z)-np.min(z)
        maxdiff = np.max([xdiff,ydiff,zdiff])
        np.multiply(dx,maxdiff)
        np.multiply(dy,maxdiff)
        np.multiply(dz,maxdiff)
        self.vectorPlot.set_xlim(np.min(x),np.min(x)+maxdiff)
        self.vectorPlot.set_ylim(np.min(y),np.min(y)+maxdiff)
        self.vectorPlot.set_zlim(np.min(z),np.min(z)+maxdiff)
        self.quiverAxes = self.vectorPlot.quiver(x,y,z,dx,dy,dz)
        self.vectorCanvas.draw()
    def initialisePlots(self):
        self.initialiseVectorPlot()
    def initialiseVectorPlot(self):
        self.vectorFig = Figure(figsize=(9,6))
        self.vectorPlot = self.vectorFig.add_subplot(projection='3d')
        self.vectorPlot.set_xlim(-5,5)
        self.vectorPlot.set_ylim(-5,5)
        self.vectorPlot.set_zlim(-5,5)
        self.vectorCanvas = FigureCanvasTkAgg(self.vectorFig,
                                                master=self.window)
        
        
        
        