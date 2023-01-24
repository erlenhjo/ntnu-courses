from random import uniform #will be used to pick random numbers between 0 and 1
from math import log
import matplotlib.pyplot as plt #Will be used to create the relevant plots


#Part 1
N_a = 1000
N_b = 700
N_c = 0
V=1
k_f = 1
k_r = 100



def Probability_forward(k_f, k_r, N_a, N_b, N_c, V): #To simplify later on. Calculates the probability of a forward transition. NOTE: the reverse probability is 1 - forward.
    return k_f*N_a*N_b/(k_f*N_a*N_b + k_r*N_c*V)

def Time_step(k_f, k_r, N_a, N_b, N_c, V):
    return -log(uniform(0,1))/(k_f*N_a*N_b + k_r*N_c*V)

#Part 2
Num_trans = 10000
equilibrium = False
N_a_time = [N_a]
N_b_time = [N_b]
N_c_time = [N_c]
t = [0]
decimal_precision=2
while not equilibrium:
    if(uniform(0, 1)<Probability_forward(k_f, k_r, N_a, N_b, N_c, V)):
        N_a-=1
        N_b-=1
        N_c+=1
    else: 
        N_a+=1
        N_b+=1
        N_c-=1

    N_a_time.append(N_a)
    N_b_time.append(N_b)
    N_c_time.append(N_c)
    t.append(t[-1]+Time_step(k_f, k_r, N_a, N_b, N_c, V))
    
    Num_trans-=1
    if(Num_trans<1):
        break
    
    if(round(Probability_forward(k_f, k_r, N_a, N_b, N_c, V),decimal_precision)==0.5):
        equilibrium=True

#Part 3
#Show plot of number of each particle as a function of time. plt.plot(x-axis, y-axis, color)
plt.plot(t, N_a_time, 'r',label="N_a")
plt.plot(t, N_b_time, 'b',label="N_b")
plt.plot(t, N_c_time, 'g',label="N_c")
plt.legend()
plt.show()

