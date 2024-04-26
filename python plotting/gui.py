# -*- coding: utf-8 -*-
"""
Created on Fri Apr 26 13:59:12 2024

@author: ihipt
"""

import tkinter as tk

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
        self.callbacks()
        self.initialisePlots()
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
    def callbacks(self):
        pass
    def entryVals(self):
        pass
    def defaults(self):
        pass
    def initialisePlots(self):
        pass
    def pack(self):
        pass