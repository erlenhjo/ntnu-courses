# -*- coding: utf-8 -*-
"""
Created on Wed Mar 23 16:21:17 2022

@author: Erlend Johansen
"""

import numpy as np
import matplotlib.pyplot as plt

xmax = 2
sq2 = np.sqrt(2)

#blå
points_x = np.arange(start=-xmax, stop=xmax,step=1)
points_y= np.arange(start=0, stop=1,step=1)
xA1, yA1= np.meshgrid(points_x, points_y)
#rød
points_x = np.arange(start=-xmax, stop=xmax-1,step=1)
points_y= np.arange(start=0, stop=1,step=1)
xB1, yB1= np.meshgrid(points_x, points_y)
xB1, yB1= xB1+1/2, yB1
#grønn
points_x = np.arange(start=-xmax, stop=xmax-1,step=1)
points_y= np.arange(start=-xmax+3, stop=xmax+1,step=1)
xA2, yA2= np.meshgrid(points_x, points_y)
xA2_1, yA2_1= xA2+1/2, yA2-1/2

#gul
points_x = np.arange(start=-xmax+1, stop=xmax-1,step=1)
points_y= np.arange(start=-xmax+1, stop=xmax-2,step=1)
xB2, yB2= np.meshgrid(points_x, points_y)
xB2_1, yB2_1= xB2, yB2+2





fig = plt.figure(figsize=(8,6))
ax = plt.axes()
ax.set_xlim(-2.5,1.5)
ax.set_ylim(-1,2)
ax.scatter(xA1,yA1, s=200,c='b')
ax.scatter(xB1,yB1, s=200,c='r')
ax.scatter(xA2_1,yA2_1, s=800,c='g',marker="s")
ax.scatter(xB2_1,yB2_1, s=800,c='y',marker="x")

plt.axis("off")