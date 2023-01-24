from math import *
from numpy import *
from pylab import *

k=0.0001
delta_t=0.001
c=5/2
g=9.81

x_m=[-1]
v_m=[0]
y_m=[1]
t_m=[0]

for n in range(10000):
    x_m.append(x_m[n]+v_m[n]*cos(math.atan(-2*x_m[n]))*delta_t)
    v_m.append(v_m[n]+g*sin(math.atan(-2*x_m[n]))/(1+c)*delta_t-k*v_m[n])
    y_m.append(x_m[n+1]**2)
    t_m.append(t_m[n]+delta_t)

plot(t_m,y_m)