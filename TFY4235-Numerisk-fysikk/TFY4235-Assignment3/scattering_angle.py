# -*- coding: utf-8 -*-
"""
Created on Thu Apr 21 14:19:04 2022

@author: Erlend Johansen
"""
import numpy as np
import matplotlib.pyplot as plt
import scipy.integrate as integrate
from numba import njit
from time import time

@njit(cache=True)
def differential_cross_section_shape(theta,k):
    a=1/(1+k-k*np.cos(theta))
    b=a+1+k*(1-np.cos(theta))-np.sin(theta)**2
    return (a**2)*b

def cumulative_probability_discretization(theta,k):
    P_of_theta=integrate.cumulative_trapezoid(differential_cross_section_shape(theta, k),initial=0,dx=theta[1]-theta[0])
    return P_of_theta/P_of_theta[-1]



def create_lookup_table(k_max, theta_max, k_steps, theta_steps):
    cumulativ_probability_lookup_table=np.empty(shape=(k_steps,theta_steps))
        
    theta=np.linspace(0, theta_max,theta_steps, endpoint=True)
    k_vals=np.linspace(0,k_max,k_steps,endpoint=True)   
    for n in range(k_steps):
        cumulativ_probability_lookup_table[n]=cumulative_probability_discretization(theta,k_vals[n])
    
    dk=k_max/(k_steps-1)
    dtheta=theta_max/(theta_steps-1)
    
    return cumulativ_probability_lookup_table, dk, dtheta 


@njit(cache=True)
def get_theta(k,random_number,P_lookup,dk,dtheta):
    k_index=int(k/dk)
    theta_index=np.searchsorted(P_lookup[k_index], random_number)-1
    theta=(theta_index+1/2)*dtheta
    return theta



def test_scattering_probability():
    E_gamma_max=1e3 #0.6 #keV
    E_e=511     #keV
    k_max=E_gamma_max/E_e
    k=k_max
    k_steps=int(1e6)
    
    theta_max=2*np.pi
    theta_steps=int(1e3)
    
    theta=np.linspace(0,theta_max,theta_steps)
    p_at_k=lambda theta : differential_cross_section_shape(theta,k)
    
    
    P_lookup, dk, dtheta=create_lookup_table(k_max, theta_max, k_steps, theta_steps)
    
    
    N=int(1e6)
    
    tic=time()
    random_numbers=np.random.random(N)
    toc=time()
    print(f"Draw time={toc-tic}")
    
    tic=time()
    thetas=get_theta(k, random_numbers, P_lookup, dk, dtheta)
    toc=time()
    print(f"Transformation time={toc-tic}")
    
    plt.plot(theta, p_at_k(theta)/integrate.quad(p_at_k,a=0,b=theta_max)[0])
    plt.hist(thetas, bins=(theta_steps-1), density=True)


if __name__=="__main__":
    test_scattering_probability()
    
    