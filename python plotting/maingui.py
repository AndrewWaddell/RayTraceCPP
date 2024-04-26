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
        self.plotButton = tk.Button(master=self.window,
                                    text="Plot",
                                    command=self.plot)
    def initialiseData(self):
        self.sources = []
    def pack(self):
        self.sourceButton.pack()
        self.plotButton.pack()
        # self.plotCanvas.get_tk_widget().pack()
        # toolbar = NavigationToolbar2Tk(self.plotCanvas,self.window)
        # toolbar.update()
        # self.plotCanvas.get_tk_widget().pack()
    def createSource(self):
        self.sourceWindow = sourceGUI(self)
    def plot(self):
        # Path to the compiled C++ program
        cpp_program = r"C:\Users\ihipt\Documents\1Ray_Optics_Application\Code\cpp\RayTraceCpp\bin\RayTrace.exe"
        
        self.loading = loadingBox()
        # Run the compiled C++ program
        subprocess.run([cpp_program])
        self.loading.destroy()
        print("now display data")