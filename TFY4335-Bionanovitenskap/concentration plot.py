"""
Created on Thu Oct  7 19:29:04 2021

@author: Erlend Johansen
"""
from math import sqrt, erf
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm, rcParams

rcParams.update({'figure.autolayout':True})

C_0=1
D=10**(-11)

def c(x,t):
    return C_0/2-C_0/2*erf(x/sqrt(4*D*t))

C=np.vectorize(c)

x=np.linspace(-0.00003,0.00003,100)
t=np.linspace(0.001,10,1000)

x,t=np.meshgrid(x,t)

z=C(x,t)

fig=plt.figure()
ax=fig.add_subplot(111,projection='3d')
ax.plot_surface(x*(10**6),t,z,cmap=cm.Blues)
ax.set_xlabel("Offset [$\mu$m]")
ax.set_ylabel("Time in contact [s]")
ax.set_zlabel("$C/C_{0}$")
