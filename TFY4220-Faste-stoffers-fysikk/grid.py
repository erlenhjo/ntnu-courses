# -*- coding: utf-8 -*-
"""
Created on Wed Mar 23 15:12:46 2022

@author: Erlend Johansen
"""
import numpy as np
import matplotlib.pyplot as plt

xmax = 2
sq2 = np.sqrt(2)

#blå
points_x = np.arange(start=-xmax, stop=xmax)
points_y= np.arange(start=-xmax+1, stop=xmax)
xA1, yA1= np.meshgrid(points_x, points_y)
#rød
points_x = np.arange(start=-xmax, stop=xmax-1)
points_y= np.arange(start=-xmax, stop=xmax)
xB1, yB1= np.meshgrid(points_x, points_y)
xB1, yB1= xB1+1/2, yB1+1/2
#grønn
points_x = np.arange(start=-xmax, stop=xmax-1,step=2)
points_y= np.arange(start=-xmax+2, stop=xmax-1,step=2)
xA2, yA2= np.meshgrid(points_x, points_y)
xA2_1, yA2_1= xA2+1/2, yA2
#mer grønn
points_x = np.arange(start=-xmax+1, stop=xmax-1,step=2)
points_y= np.arange(start=-xmax+1, stop=xmax,step=2)
xA2, yA2= np.meshgrid(points_x, points_y)
xA2_2, yA2_2= xA2+1/2, yA2
#gul
points = np.arange(start=-xmax, stop=xmax-1,step=2)
xB2, yB2= np.meshgrid(points, points)
xB2_1, yB2_1= xB2+1/2, yB2+1
#mer gul?
points = np.arange(start=-xmax+1, stop=xmax-1,step=2)
xB2, yB2= np.meshgrid(points, points)
xB2_2, yB2_2= xB2+1/2, yB2+1




fig = plt.figure(figsize=(8,8))
ax = plt.axes()
ax.set_xlim(-2.5,1.5)
ax.set_ylim(-2,2)
ax.scatter(xA1,yA1, s=200,c='b')
ax.scatter(xB1,yB1, s=200,c='r')
ax.scatter(xA2_1,yA2_1, s=800,c='g',marker="s")
ax.scatter(xA2_2,yA2_2, s=800,c='g',marker="s")
#ax.scatter(xB2_1,yB2_1, s=800,c='y',marker="x")
#ax.scatter(xB2_2,yB2_2, s=800,c='y',marker="x")

plt.axis("off")
plt.show()