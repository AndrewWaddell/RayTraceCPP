# -*- coding: utf-8 -*-
"""
Created on Wed Feb 21 17:06:46 2024

@author: ihipt
"""

import matplotlib.pyplot as plt
import csv


# for the original points unit. but change for separate rows

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
plt.show()
