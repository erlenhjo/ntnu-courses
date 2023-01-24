# -*- coding: utf-8 -*-
"""
Created on Mon Mar 14 16:40:59 2022

@author: Erlend Johansen
"""


from scipy.stats import linregress
import matplotlib.pyplot as plt
import numpy as np






def calculate_stuff(d,R,i):
    slope,intercept,r,p,se=linregress(d[i:],R[i:])
    
    plt.figure()
    plt.scatter(d*1e6,R,c="b",marker="x",label="Resistance meassurment data points")
    x=np.linspace(0,d.max(),1000)
    plt.plot(x*1e6,slope*x+intercept,c="r",label="Linear regression curve")
    plt.xlabel("Spacing [μm]")
    plt.ylabel("Resistance [Ω]")
    plt.ylim(0,100)
    plt.xlim(0,2200)
    plt.legend(loc="upper left")
    
    w=900e-6
    b=500e-6
    t=2e-6
    A=w*b
    
    resistivity=w*t*slope*1e2
    print(resistivity)
    
    contact_resistance=intercept/(2*A)*1e-4
    print(contact_resistance)

if __name__=="__main__":
    
    d=np.array([245,494,998,1997])*1e-6

    R_219=np.array([51.55,51.28,74.08,97.66])
    R_218=np.array([4.72,9.95,18.73,36.82])
    
    calculate_stuff(d, R_218,i=0)
    calculate_stuff(d, R_219,i=2)