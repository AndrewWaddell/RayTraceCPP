# -*- coding: utf-8 -*-
"""
Created on Wed Feb 21 17:06:46 2024

@author: ihipt
"""

import matplotlib.pyplot as plt
import csv

# import gi
# gi.require_version('Gtk','3.0')
# from gi.repository import Gtk
# from matplotlib.figure import Figure
# from matplotlib.backends.backend_gtk3agg import FigureCanvas
# from matplotlib.backends.backend_gtk3 import (NavigationToolbar2GTK3 as NavigationToolbar)


def importData(filename):
    data = []
    with open(filename) as csvfile:
        document = csv.reader(csvfile)
        for row in document:
            row_reader = csv.reader(row, delimiter=' ')
            for row_list in row_reader:
                for number_str in row_list:
                    if number_str != '':
                        number = float(number_str)
                        data.append(number)
    return data

            
x = importData('../src/x.txt')
y = importData('../src/y.txt')
z = importData('../src/z.txt')
dx = importData('../src/dx.txt')
dy = importData('../src/dy.txt')
dz = importData('../src/dz.txt')


ax = plt.figure().add_subplot(projection='3d')
ax.quiver(x,y,z,dx,dy,dz)
ax.set_xlim(0,6)
ax.set_ylim(-3,3)
ax.set_zlim(0,6)
plt.show()


# win = Gtk.window()
# win.connect("destroy",lambda x: Gtk.main_quit())
# win.set_default_size(400,300)
# win.set_title("Vector Plot 3D")
# vbox = Gtk.VBox()
# win.add(vbox)
# fig = Figure(figsize=(5,4),dpi=100)
# ax = fig.add_subplot(111)
# ax.plot([1,2,3])
# canvas = FigureCanvas(fig)
# vbox.pack_start(canvas,True,True,0)
# toolbar = NavigationToolbar(canvas,win)
# vbox.pack_start(toolbar,False,False,0)
# win.show_all()
# Gtk.main()
