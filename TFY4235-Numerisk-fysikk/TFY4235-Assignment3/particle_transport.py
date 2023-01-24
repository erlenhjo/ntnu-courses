# -*- coding: utf-8 -*-
"""
Created on Fri Apr 22 22:12:48 2022

@author: Erlend Johansen
"""
from numba import njit
import matplotlib.pyplot as plt
import numpy as np

import scattering_angle

###### Physical constants ######
eV=1.602e-19 #J
keV=1e3*eV
E_e=511*keV
e=1.6e-19
r_e=e**2/E_e
alpha=1/137
################################

####### Global lookup table #########
E_gamma_max=1*keV
k_max=E_gamma_max/E_e
k_steps=int(1e6)
theta_max=2*np.pi
theta_steps=int(1e3)

#P_lookup=scattering_angle.create_lookup_table(k_max, theta_max, k_steps, theta_steps)

#####################################

def alternative(Z,k):
    return 16/3*np.sqrt(2)*np.pi*r_e**2*alpha**4*Z**5/(k**3.5)

def photo_electric_cross_section(Z,E_gamma):
    return 3e12*Z**4/((E_gamma/eV)**3.5)

def P_photo_electric(Z,E_gamma,l):
    return 1e-2*(l*E_gamma*Z/(l*E_gamma*Z))
    #return 1-np.exp(-alternative(Z, E_gamma/E_e)*l)

def is_photo_electric(random_number,Z,E_gamma,l):
    return random_number < P_photo_electric(Z, E_gamma, l)

def energy_after_scattering(E_gamma,k,delta_theta):
    return E_gamma/(1+k*(1-np.cos(delta_theta)))

def nitrogen_gas():
    mu_Nitrogen=3.311e3*1.2506/10**3
    Z=7
    l_0=1/mu_Nitrogen
    return Z, l_0

def lead_solid():
    mu_Lead=5.210e3*11.34
    Z=82
    l_0=1/mu_Lead
    return Z,l_0
    
def scattering(E_gamma,Z,l,theta,x,y):
    global P_lookup,dk,dtheta,E_e
    k=E_gamma/E_e
    random_number=np.random.random()
    delta_theta=scattering_angle.get_theta(k,random_number,P_lookup,dk,dtheta)
    E_gamma_new=energy_after_scattering(E_gamma, k, delta_theta)
    theta_new=theta+delta_theta
    x_new=x+l*np.cos(theta_new)
    y_new=x+l*np.sin(theta_new)
    return E_gamma_new,theta_new,x_new,y_new

def photon_track(E_gamma_0,x_0,y_0,theta_0):
    
        
    if (x**2+y**2)<r_gas**2:
        



def test_absorbtion_probability():
    Z=1
    E_gamma=np.linspace(1*keV,1000*keV)
    k=E_gamma/E_e
    plt.figure()
    plt.plot(E_gamma, photo_electric_cross_section(Z, E_gamma),label="Org")
    plt.plot(E_gamma, alternative(Z, k),label="Alt")
    plt.legend()
    
    
    Z=100
    E_gamma=1*keV
    l=np.logspace(-62, 100)
    
    
    P_pe=P_photo_electric(Z, E_gamma, l)
    
    plt.figure()
    plt.plot(l, P_pe,label="P_pe")
    plt.legend()
    plt.xscale("log")
    plt.yscale("log")



if __name__=="__main__":
    test_absorbtion_probability()
