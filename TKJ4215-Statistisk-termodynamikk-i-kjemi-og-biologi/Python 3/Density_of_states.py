import numpy as np
import itertools as it
import matplotlib.pyplot as plt
import pickle

def Lattice_shape(N): #The function determines the lattice shapes that you will be using in this exercise, given N particles.
    if N == 4:
        return (2,2)
    elif N == 6:
        return (2,3)
    elif N == 8:
        return (2,4)
    elif N == 12:
        return (3,4)
    elif N == 16:
        return (4,4)
    elif N == 20:
        return (5,4)
    elif N == 24:
        return (6,4)


def Count_AB(Lattice):
    #Should take an array, representing the lattice, and find the number of AB-interactions. Use PERIODIC BOUNDARY conditions!
    #Tip: Make sure to avoid double counting. Concider only particles of a given type and count the oposite neighbours.
    m_AB=0
    for i in range(len(Lattice)):
        for j in range(len(Lattice[i])):
            if Lattice[i-1][j]!=Lattice[i][j]:
                m_AB+=1
            if Lattice[i][j-1]!=Lattice[i][j]:
                m_AB+=1
    return m_AB


def Create_arrays_and_count(Number_of_particles):
    m_AB = []#A list that keeps track of the number of AB-interactions for each configuration.
    shape=Lattice_shape(Number_of_particles)
    for config in it.product(it.product([0,1],repeat=shape[0]),repeat=shape[1]):
        #Use itertools.product() to generate all possible unique lattice configurations.
        #itertools returns all unique combinations, including thos with N_A not = N_B. Select those lists where N_A = N_B
        #itertools returns a list so you will have to convert the list to an array below.
        config=np.asarray(config)
        if np.sum(config)==Number_of_particles/2:
            m_AB.append(Count_AB(config))#should append the result of calling Count_AB(Lattice) on a given configuration config
    return m_AB

N_list=[4, 6, 8, 12, 16, 20, 24]

for i in N_list: #You will be calculating the density of states for the given system sizes
    print("Number of particles: "+str(i))
    m_AB = Create_arrays_and_count(i)#Call the correct function to create a list of all possible configuration AB-interactions
    Available_macrostates = list(set(m_AB)) #Finds all unique microstates
    Available_macrostates.sort() #Sorts this list in ascending order, for plotting purposes.
    m_AB_degeneracy = [m_AB.count(state) for state in Available_macrostates] #For each macrostate, this list should return the degeneracy. Use list_comprehension and list.count()
    #Creates a bar chart of density of states: x-axis = microstate, y-axis = degeneracy
    y_pos = np.arange(len(Available_macrostates))
    plt.bar(y_pos, m_AB_degeneracy)
    plt.xticks(y_pos, Available_macrostates, fontsize=7, rotation=30)
    plt.savefig('Density_of_states' + str(i))
    plt.clf()
    #To compare the variance of density of states as system size increases, you must normalize the interaction energies (number of AB-interactions)
    Normalization_factor = max(Available_macrostates) #The normalization factor should be the highest possible number of AB-interactions for a given system size
    Normalized_mAB = [i/Normalization_factor for i in m_AB] #Create a normalized version of m_AB by deviding each instance by the Normalization_factor
    print(np.var(Normalized_mAB)) #Calculate and print the variance of Normalized_mAB. Use np.var().


#Saves m_AB and i for future use for system size = i_max (in this case 24)
with open('m_AB.pkl', 'wb') as f:
    pickle.dump([m_AB,i], f)