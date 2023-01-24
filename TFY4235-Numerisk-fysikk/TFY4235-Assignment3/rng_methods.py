# -*- coding: utf-8 -*-
"""
Created on Sat Apr 23 16:05:12 2022

@author: Erlend Johansen
"""
import numpy as np
import matplotlib.pyplot as plt
from numba import njit

@njit(cache=True)
def iterate_MSM(seed,n):
    random_number=((seed**2)%(10**(n+n//2))) // int(10**(n//2))
    new_seed=random_number
    return new_seed, random_number

@njit(cache=True)
def middle_square_method(initial_seed,n,desired_numbers):
    random_numbers=np.zeros(desired_numbers,dtype=np.int64)
    seed=int(initial_seed)
    for i in range(desired_numbers):
        seed, random_numbers[i]=iterate_MSM(seed,n)
    return random_numbers

def test_middle_square_method(initial_seed):
    n=4
    desired_numbers=int(60)
    
    random_numbers=middle_square_method(initial_seed,n,desired_numbers)
    print(random_numbers)
    unique_numbers,number_count=np.unique(random_numbers, return_counts=True)
    print("Appears more than once:",[a[0] for a in unique_numbers[np.argwhere(number_count>1)]])
    
    plt.figure()
    plt.plot(range(desired_numbers),random_numbers)

def iterate_LCM(seed,a,c,m):
    random_number=(a*seed+c)%m
    new_seed=random_number
    return new_seed, random_number

def linear_congruential_method(initial_seed,a,c,m,desired_numbers):
    random_numbers=np.zeros(desired_numbers,dtype=np.int64)
    seed=int(initial_seed)
    for i in range(desired_numbers):
        seed, random_numbers[i]=iterate_LCM(seed,a,c,m)
    return random_numbers


def test_linear_congruential_method():
    initial_seed=42
    m=1234
    a=123
    c=234
    
    desired_numbers=int(1000)
    
    random_numbers=linear_congruential_method(initial_seed, a, c, m, desired_numbers)
    print(random_numbers)
    unique_numbers,number_count=np.unique(random_numbers, return_counts=True)
    print("Appears more than once:",[a[0] for a in unique_numbers[np.argwhere(number_count>1)]])
    
    plt.figure()
    plt.scatter(range(desired_numbers),random_numbers%10)
    
    desired_numbers=int(20000)
    
    random_numbers=linear_congruential_method(initial_seed, a, c, m, desired_numbers)
    unique_numbers,number_count=np.unique(random_numbers, return_counts=True)
    print("Appears more than once:",[a[0] for a in unique_numbers[np.argwhere(number_count>1)]])
    
    plt.figure()
    plt.scatter(random_numbers[:desired_numbers//2],random_numbers[desired_numbers//2:],marker = 'o', s = 1, alpha = 0.5, color = 'k')
    
    
    initial_seed=12345678
    m=2**16+1
    a=75
    c=74
    
    desired_numbers=int(20000)
    
    random_numbers=linear_congruential_method(initial_seed, a, c, m, desired_numbers)
    unique_numbers,number_count=np.unique(random_numbers, return_counts=True)
    print("Appears more than once:",[a[0] for a in unique_numbers[np.argwhere(number_count>1)]])
    
    plt.figure()
    plt.scatter(random_numbers[:desired_numbers//2],random_numbers[desired_numbers//2:],marker = 'o', s = 1, alpha = 0.5, color = 'k')
    
    
    
    
    
    
    












if __name__=="__main__":
    test_middle_square_method(123)
    test_middle_square_method(1234)
    test_linear_congruential_method()









