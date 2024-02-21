# -*- coding: utf-8 -*-
"""
Created on Wed Feb 21 17:06:46 2024

@author: ihipt
"""

import matplotlib.pyplot as plt
import csv


def importData(filename):
    data = []
    with open(filename) as csvfile:
        document = csv.reader(csvfile)
        i=-1
        for row in document:
            i+=1
            data.append([])
            row_reader = csv.reader(row, delimiter=' ')
            for row_list in row_reader:
                for number_str in row_list:
                    if number_str != '':
                        number = float(number_str)
                        data[i].append(number)
    return data
    
            
points = importData('../src/points.txt')
unit = importData('../src/unit.txt')
pointsAcc = importData('../src/pointsAcc.txt')
unitAcc = importData('../src/unitAcc.txt')
distancesAcc = importData('../src/distancesAcc.txt')


x = pointsAcc[0]
y = pointsAcc[1]
z = pointsAcc[2]
ux = unitAcc[0]
uy = unitAcc[1]
uz = unitAcc[2]
    

ax = plt.figure().add_subplot(projection='3d')
ax.quiver(x,y,z,ux,uy,uz)
plt.show()
