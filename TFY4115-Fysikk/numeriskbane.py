from pylab import *
from numpy import *

A=array([[4,1,0,0,0,0],
         [1,4,1,0,0,0],
         [0,1,4,1,0,0],
         [0,0,1,4,1,0],
         [0,0,0,1,4,1],
         [0,0,0,0,1,4]])

h=0.200 # steglengde i x retning i mm
x=[]
for n in range(8):
    x.append(round(n*h,3))

y=[0.645,0.331,0.176,0.112,0.124,0.213,0.365,0.726]   #put inn y-verdier fra målinger her
 
b=[]
for j in range(1,7):
    b.append(6/(h**2)*(y[j+1]-2*y[j]+y[j-1]))
b=array(b)

y2der=linalg.solve(A,b)
y2der=list(y2der)
y2der.append(0)
y2der.reverse()
y2der.append(0)
y2der.reverse()
print(y2der)

def S(j,x_s):
    linje1=y2der[j]/(6*h)*(x[j+1]-x_s)**3
    linje2=y2der[j+1]/(6*h)*(x_s-x[j])**3
    linje3=(y[j+1]/h-y2der[j+1]*h/6)*(x_s-x[j])
    linje4=(y[j]/h-y2der[j]*h/6)*(x[j+1]-x_s)
    return linje1+linje2+linje3+linje4
    
x_1=linspace(x[0],x[len(x)-1],14001)
x_1=list(x_1)
x_1.pop()
y_1=[]
for n in range(len(x_1)):
    y_1.append(S(int(x_1[n]*100)//int(h*100),x_1[n]))

plot(x_1,y_1)




