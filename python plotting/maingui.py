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
        for source in sources:
            source['location'].