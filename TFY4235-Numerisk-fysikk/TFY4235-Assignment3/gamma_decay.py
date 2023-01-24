# -*- coding: utf-8 -*-
"""
Created on Sat Apr 23 13:16:20 2022

@author: Erlend Johansen
"""
import numpy as np
import matplotlib.pyplot as plt
from numba import njit
from time import time

@njit(cache=True) 
def P_decay(decay_constant,dt):
    return 1-np.exp(-decay_constant*dt)

@njit(cache=True) 
def is_decay(random_number,decay_constant,dt):
    return random_number < P_decay(decay_constant, dt)

@njit(cache=True) 
def theoretical_N_1(N_1_0,decay_constant_1,t):
    return N_1_0*np.exp(-decay_constant_1*t)

@njit(cache=True)
def theoretical_N_2(N_1_0,decay_constant_1,decay_constant_2,t):
    h_1=1
    exp_1=np.exp(-decay_constant_1*t)
    h_2=decay_constant_1/(decay_constant_1-decay_constant_2)
    exp_2=np.exp(-decay_constant_2*t)
    return N_1_0*(h_1*exp_1+h_2*exp_2)


@njit(cache=True)    
def three_atom_decay_chain(N_1_0,decay_constant_1,decay_constant_2,t_max,time_steps):
    
    N_1=np.empty(time_steps,dtype=np.int64)
    N_2=np.empty(time_steps,dtype=np.int64)
    N_3=np.empty(time_steps,dtype=np.int64)
    
    N_1[0]=N_1_0
    N_2[0]=0
    N_3[0]=0
    
    dt=t_max/time_steps
    
    for i in range(time_steps-1):

        random_numbers=np.random.random(N_1[i])
        decay_of_atom_1=sum([is_decay(random_number, decay_constant_1, dt) for random_number in random_numbers])
        
        random_numbers=np.random.random(N_2[i])
        decay_of_atom_2=sum([is_decay(random_number, decay_constant_2, dt) for random_number in random_numbers])
        
        N_1[i+1]=N_1[i]-decay_of_atom_1
        N_2[i+1]=N_2[i]+decay_of_atom_1-decay_of_atom_2
        N_3[i+1]=N_3[i]+decay_of_atom_2

    return N_1,N_2,N_3
    
def test_gamma_decay():    
    N_1_0=int(1e6)
    decay_constant_1=0.003
    decay_constant_2=0.03
    t_max=20
    time_steps=1000
    
    t=np.linspace(0,t_max,time_steps)
    
    tic=time()
    N_1,N_2,N_3=three_atom_decay_chain(N_1_0, decay_constant_1, decay_constant_2, t_max, time_steps)
    toc=time()
    print(f"Decay simulation time: {toc-tic}")    
    
    plt.plot(t,N_1)
    plt.plot(t,N_2)
    plt.plot(t,theoretical_N_1(N_1_0,decay_constant_1,t),linestyle="dashed")
    plt.plot(t,theoretical_N_2(N_1_0,decay_constant_1,decay_constant_2,t),linestyle="dashdot")  
    plt.axhline(y=N_1_0*decay_constant_1/decay_constant_2,linestyle="dotted")
    plt.yscale("log")
    
    
if __name__=="__main__":
    test_gamma_decay()
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    