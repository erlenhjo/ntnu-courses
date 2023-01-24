from pylab import *
import numpy
file=open("data","r")
t_tracker=[]
v_tracker=[]
y_tracker=[]
file.readline()
file.readline()

for n in range(16):
    file.readline()

for line in file:
    line=line.replace(",",".")
    line=line.replace("\n","")
    line=line.split("\t")
    try:
        t_tracker.append(float(line[0][:11])*10**int(line[0][12:])-1.140)
        v_tracker.append(float(line[1][:11])*10**int(line[1][12:]))
        y_tracker.append(float(line[2][:11])*10**int(line[2][12:])+0.1)
    except:
        t_tracker.pop()
        
file.close()

A=array([[4,1,0,0,0,0],
         [1,4,1,0,0,0],
         [0,1,4,1,0,0],
         [0,0,1,4,1,0],
         [0,0,0,1,4,1],
         [0,0,0,0,1,4]])

h=0.200 # steglengde i x retning i mm
x_b=[]
for n in range(8):
    x_b.append(round(n*h,3))

y_b=[0.645,0.331,0.176,0.112,0.124,0.213,0.365,0.726]   #put inn y-verdier fra målinger her
 
b=[]
for j in range(1,7):
    b.append(6/(h**2)*(y_b[j+1]-2*y_b[j]+y_b[j-1]))
b=array(b)

y2der=numpy.linalg.solve(A,b)
y2der=list(y2der)
y2der.append(0)
y2der.insert(0,0)

def S(x):
    j=min(int(5*x),6)
    linje1=y2der[j]/(6*h)*(x_b[j+1]-x)**3
    linje2=y2der[j+1]/(6*h)*(x-x_b[j])**3
    linje3=(y_b[j+1]/h-y2der[j+1]*h/6)*(x-x_b[j])
    linje4=(y_b[j]/h-y2der[j]*h/6)*(x_b[j+1]-x)
    
    
    return linje1+linje2+linje3+linje4

def Sder(x,dx):
    return (S(x+dx)-S(x))/dx

def S2der(x,dx):
    return (Sder(x+dx,dx)-Sder(x,dx))/dx


m=0.030
r=0.01
k=0.0041
delta_t=0.0001
c=0.4
g=9.81

x_m=[0.0555]
v_m=[0]
y_m=[S(x_m[0])]
t_m=[0]
a_m=[g*numpy.sin(-numpy.arctan(Sder(x_m[0],0.0001)))/(1+c)]

for n in range(190):
    t_m.append(t_m[n]+delta_t)
    a_m.append((g*numpy.sin(-numpy.arctan(Sder(x_m[n],0.0001)))-k*v_m[n]/m)/(1+c))
    v_m.append(v_m[n]+a_m[n]*delta_t)
    x_m.append(x_m[n]+v_m[n]*numpy.cos(-numpy.arctan(Sder(x_m[n],0.0001)))*delta_t)
    y_m.append(S(x_m[n]))
    
abs_v_m=[]
for v in v_m:
    abs_v_m.append(abs(v))

x_F=[0]
v_F=[0]
t_F=[0]
a_F=[g*numpy.sin(-numpy.arctan(Sder(x_F[0],0.1)))/(1+c)]
N_F=[m*v_F[0]**2/((1+Sder(0,0.1)**2)**(3/2)/S2der(0,0.1))+m*g*numpy.cos(-numpy.arctan(Sder(0,0.1)))]
f_F=[c*m*a_F[0]]
R=[m*v_F[0]**2/((1+Sder(0,0.1)**2)**(3/2)/S2der(0,0.1))]
n=0
while v_F[n]>=0:
    x_F.append(x_F[n]+v_F[n]*numpy.cos(-numpy.arctan(Sder(x_F[n],0.1)))*delta_t)
    v_F.append(v_F[n]+a_F[n]*delta_t)
    t_F.append(t_F[n]+delta_t)
    a_F.append((g*numpy.sin(-numpy.arctan(Sder(x_F[n],0.1)))-k*v_F[n]/m)/(1+c))
    N_F.append(m*v_F[n]**2/((1+Sder(x_F[n],0.05)**2)**(3/2)/S2der(x_F[n],0.05))+m*g*numpy.cos(-numpy.arctan(Sder(x_F[n],0.05))))
    R.append(m*v_F[n]**2/((1+Sder(x_F[n],0.05)**2)**(3/2)/S2der(x_F[n],0.05)))
    f_F.append(c*m*a_F[n])
    n+=1

x_bane=list(linspace(0,1.4,14001))
y_bane=[]
for n in range(len(x_bane)):
    y_bane.append(S(x_bane[n]))

gamma=[]
h_min=min(y_m)
for n in range(len(t_m)):
    gamma.append((y_m[0]-h_min)*exp(-0.088*t_m[n])+h_min)


rcParams.update({'font.size': 15})


figure(1)
plot(t_m,y_m, label="Numerisk")
plot(t_tracker,y_tracker,label="Eksperimentell")
plot(t_m, gamma, label="Energi uttrykt ved høyde")
legend(loc="upper right")
#title("Eksperimentell og numerisk høyde over tid")
ylabel("Høyde [m]")
xlabel("Tid [s]")
grid()

figure(2)
plot(t_m,abs_v_m, label="Numerisk")
plot(t_tracker,v_tracker, label="Eksperimentell")
legend()
#title("Eksperimentell og numerisk hastighet over tid")
legend(loc="upper right")
ylabel("Fart [m/s]")
xlabel("Tid [s]")
grid()

figure(3)
#title("Eksperimentell normalkraft")
plot(x_F,N_F,label="Normalkraft")
plot([],[],label="Bane",color="orange")
legend(loc="upper right")
xlabel("x-posisjon [m]")
ylabel("Normalkraft [N]")
grid(axis="x")
twinx()
plot(x_bane,y_bane,label="Bane",color="orange")
ylabel("y-posisjon [m]")




figure(4)
#title("Eksperimentell friksjon")
plot(x_F,f_F,label="Friksjon mot underlaget")
plot([],[],label="Bane",color="orange")
legend(loc="upper right")
xlabel("x-posisjon [m]")
ylabel("Friksjon mot underlaget [N]")
grid(axis="x")
twinx()
plot(x_bane,y_bane,label="Bane",color="orange")
ylabel("y-posisjon [m]")
