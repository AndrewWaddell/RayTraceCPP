# -*- coding: utf-8 -*-
"""
Created on Fri Apr 26 14:29:14 2024

@author: ihipt
"""

import tkinter as tk
from gui import GUI


class loadingBox(GUI):
    def windowType(self):
        self.window = tk.Toplevel()
    def setTitle(self):
        self.window.title("Loading")
    def labels(self):
        self.loadingLabel = tk.Label(master=self.window,
                                     text="Please wait...",
                                     width=20)
    def pack(self):
        self.loadingLabel.pack()
    def geometry(self):
        self.window.geometry("300x200")