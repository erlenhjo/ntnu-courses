# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import numpy as np
import matplotlib.pyplot as plt

L=8.5e-3
t=2e-6
q=1.6e-19
B=0.5

R_low=3100
R_high=1
R_wire=50

my_high=3000e-4
my_low=5000e-4

n_high=1e25
n_low=1e23








def V_hall(I,n):
    return I*B/(q*t*n)

def R_bar(w,n,my):
    return L/(w*t*n*q*my)


#w=np.linspace(100e-6,1000e-6)

w=800e-6

I=2e-3

n=np.linspace(n_low,n_high,10001)

my=my_low+(my_high-my_low)*(n-n_low)/(n_high-n_low)

R_sys=R_low+(R_high-R_low)*(n-n_low)/(n_high-n_low) + R_wire

#vi skal maksimere w

V_source=(L/(n*q*my*t*w)+R_sys)*I
V_source[V_source>7]=7

plt.figure(1)
plt.plot(n,V_source)
plt.xscale("log")
    
I_capped=7/(L/(n*q*my*t*w)+R_sys)
I_capped[I_capped>0.002]=0.002


plt.figure(2)
plt.plot(n,I_capped)
plt.xscale("log")

plt.figure(3)
plt.plot(n,V_hall(I_capped,n))
plt.plot(n,[0.001 for val in n])
plt.xscale("log")


sigma=my*n*q
resistivity=1/sigma