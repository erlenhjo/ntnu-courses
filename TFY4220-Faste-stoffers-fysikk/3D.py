# -*- coding: utf-8 -*-
"""
Created on Thu Mar 24 08:59:20 2022

@author: Erlend Johansen
"""

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def plotSphere(center_x,center_y,center_z,r,ax,c):
    detail=25
    u = np.linspace(0, 2 * np.pi, detail)
    v = np.linspace(0, np.pi, detail)
    x = r * np.outer(np.cos(u), np.sin(v))+center_x
    y = r * np.outer(np.sin(u), np.sin(v))+center_y
    z = r * np.outer(np.ones(np.size(u)), np.cos(v))+center_z
    ax.plot_surface(x, y, z, color=c)

def plotMultipleSpheres(X,Y,Z,r,ax,c):
    for x in X.flatten():
        for y in Y.flatten():
            for z in Z.flatten():
                plotSphere(x, y, z, r, ax,c)


xmax = 2
sq2=np.sqrt(2)
#blå
points_x = np.arange(start=-xmax, stop=xmax)
points_y= np.arange(start=-xmax+1, stop=xmax)
xA1, yA1,zA1= np.meshgrid(points_x, points_y,[-1,0])
#rød
points_x = np.arange(start=-xmax, stop=xmax-1)
points_y= np.arange(start=-xmax, stop=xmax)
xB1, yB1,zB1= np.meshgrid(points_x, points_y,[-1,0])
xB1, yB1,zB1= xB1+1/2, yB1+1/2,zB1
#grønn
points_x = np.arange(start=-xmax, stop=xmax-1,step=2)
points_y= np.arange(start=-xmax+2, stop=xmax-1,step=2)
xA2, yA2,zA2= np.meshgrid(points_x, points_y,[0,sq2])
xA2_1, yA2_1,zA2_1= xA2+1/2, yA2,zA2+0.5
#mer grønn
points_x = np.arange(start=-xmax+1, stop=xmax-1,step=2)
points_y= np.arange(start=-xmax+1, stop=xmax,step=2)
xA2, yA2,zA2= np.meshgrid(points_x, points_y,[0,sq2])
xA2_2, yA2_2,zA2_2= xA2+1/2, yA2,zA2+0.5
#gul
points = np.arange(start=-xmax+2, stop=xmax-3,step=2)
xB2, yB2,zB2= np.meshgrid(points, points,[0])
xB2_1, yB2_1,zB2_1= xB2+1/2, yB2+1,zB2+0.5*(1+sq2)
#mer gul?
points = np.arange(start=-xmax+1, stop=xmax-1,step=2)
xB2, yB2,zB2= np.meshgrid(points, points,[0])
xB2_2, yB2_2,zB2_2= xB2+1/2, yB2+1,zB2+0.5*(1+sq2)
print(np.append(xA2_1.flatten(),xA2_2.flatten()))
r=0.3
fig = plt.figure(figsize=(8,8))
ax = plt.axes(projection="3d")
plotMultipleSpheres(xA1, yA1, zA1, r, ax,c="b")
plotMultipleSpheres(xB1, yB1, zB1, r, ax,c="r")
plotMultipleSpheres(xA2_1,yA2_1,zA2_1, r,ax,c='g')
plotMultipleSpheres(xA2_2,yA2_2,zA2_2, r,ax,c='g')
plotMultipleSpheres(xB2_1,yB2_1,zB2_1, r,ax,c='y')
plotMultipleSpheres(xB2_2,yB2_2,zB2_2, r,ax,c='y')
ax.set_xlim(-2.5,1.5)
ax.set_ylim(-2,2)
ax.set_zlim(-0.5,2.5)

"""
ax.set_xlim(-2.5,1.5)
ax.set_ylim(-2,2)
ax.set_zlim(-0.2,3)

ax.scatter3D(xA1,yA1,zA1, s=200,c='b')
ax.scatter3D(xB1,yB1,zB1, s=200,c='r')
ax.scatter3D(xA2_1,yA2_1,zA2_1, s=800,c='g',marker="s")
ax.scatter3D(xA2_2,yA2_2,zA2_2, s=800,c='g',marker="s")
"""
#ax.scatter(xB2_1,yB2_1, s=800,c='y',marker="x")
#ax.scatter(xB2_2,yB2_2, s=800,c='y',marker="x")

plt.axis("off")
plt.show()