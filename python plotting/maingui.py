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
import matplotlib.pyplot as plt
from matplotlib.figure import Figure
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
        # self.plotCanvas.get_tk_widget().pack()
        # toolbar = NavigationToolbar2Tk(self.plotCanvas,self.window)
        # toolbar.update()
        # self.plotCanvas.get_tk_widget().pack()
    def createSource(self):
        self.sourceWindow = sourceGUI(self)
        print("source openend")
    def trace(self):
        self.loading = loadingBox()
        self.save()
        subprocess.run([self.traceCpp])
        self.loading.destroy()
    def save(self): # save data in the files
        pass
    def plotSources(self):
        x = []
        y = []
        z = []
        dx = []
        dy = []
        dz = []
        for source in self.sources:
            x.append(source['location'][0])
            y.append(source['location'][1])
            z.append(source['location'][2])
            dx.append(source['unit'][0])
            dy.append(source['unit'][1])
            dz.append(source['unit'][2])
        try:
            self.quiverAxes.remove()
        except:
            pass
        self.quiverAxes = self.vectorPlot.quiver(x,y,z,dx,dy,dz)
        self.vectorCanvas.draw()
        
        # ax = plt.figure().add_subplot(projection='3d')
        # ax.quiver(x,y,z,dx,dy,dz)
        # ax.set_xlim(0,6)
        # ax.set_ylim(-3,3)
        # ax.set_zlim(0,6)
        # plt.show()
    def initialisePlots(self):
        self.initialiseVectorPlot()
    def initialiseVectorPlot(self):
        self.vectorFig = Figure(figsize=(3,3))
        self.vectorPlot = self.vectorFig.add_subplot(projection='3d')
        self.vectorPlot.set_xlim(-1,1)
        self.vectorPlot.set_ylim(-1,1)
        self.vectorPlot.set_zlim(-1,1)
        self.vectorCanvas = FigureCanvasTkAgg(self.vectorFig,
                                                master=self.window)
        
        
        
        