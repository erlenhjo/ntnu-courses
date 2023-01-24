# -*- coding: utf-8 -*-
"""
Created on Wed Sep  1 16:39:01 2021

@author: Erlend Johansen
"""

import numpy as np
import matplotlib.pyplot as plt

gamma=2*10**(-5)
rho=2.17
sigma=3*10**(-13)
m=1
entalpyOfFusion=520

def surfaceEnergy(a):
    return 6*m*gamma/(rho*a)

def edgeEnergy(a):
    return 8*m*sigma/(rho*a**2)

a=np.logspace(-7,-1,num=300)
surf=surfaceEnergy(a)
edge=edgeEnergy(a)
both=edge+surf

plt.figure(1)
plt.plot(a,surf,label="Surface energy")
plt.plot(a,both,label="Combined energy")
plt.plot(a,edge,label="Edge energy")
plt.hlines(entalpyOfFusion,0,0.1,label="Entalpy of fusion")
plt.xscale("log")
plt.xlabel("a [cm]")
plt.ylabel("Energy [J]")
plt.legend()



r=1.37*10**(-10)
NA=6.022*10**23
Mm=106.4
rho=12*10**6


def numberOfParticles(a):
    volume=4*3.14/3*(a/2)**3
    mass=rho*volume
    moles=mass/Mm
    number=NA*moles
    return number

def numberOfSurfaceParticles(a):
    surfaceArea=4*3.14*(a/2)**2
    particleArea=(2*r)**2
    return surfaceArea/particleArea

def diameterFromNumber(N):
    return 2*(N*3*Mm/(NA*rho*4*3.14))**(1/3)

fractions=np.array([92,76,63,52,45,35])/100
atoms=np.array([13,55,147,309,561,1415])
diameters=diameterFromNumber(atoms)


a=np.logspace(-9,-3,num=300)
fractionOnSurface=numberOfSurfaceParticles(a)/numberOfParticles(a)


plt.figure(2)
plt.plot(a, fractionOnSurface)
plt.hlines(1,0,0.001)
plt.scatter(diameters,fractions,c="k",marker=".")
plt.xscale("log")
plt.xlabel("a [m]")
plt.ylabel("Fraction of particles on surface")

plt.show()



