from numpy import zeros
from random import choice, uniform
import matplotlib.pyplot as plt
from math import log, factorial

row = 100
col = 200
N = 50
Num_steps = 100000
Dump_interval = Num_steps//10       # should be around 1/10 of Num_steps, a bad choice (too frequent) can make the calculation very slow 
Data_interval=Num_steps//100
def Initialize(row,col,N):
    # Put all the particles on for example the left-hand side
    Positions_of_particles=[]
    particles_placed=0
    for x in range(col):
        for y in range(row):
            Positions_of_particles.append((x,y))
            particles_placed+=1
            if(particles_placed==N):
                return Positions_of_particles

def Possible_transitions(Positions_of_particles,row,col):
    x=0
    y=1
    Transitions=[]
    for position in Positions_of_particles:
        if(position[0]>0):
            if((position[x]-1,position[y]) not in Positions_of_particles):
                Transitions.append((position,(position[x]-1,position[y])))
        if(position[0]<col-1):
            if((position[x]+1,position[y]) not in Positions_of_particles):
                Transitions.append((position,(position[x]+1,position[y])))
        if(position[1]>0):
            if((position[x],position[y]-1) not in Positions_of_particles):
                Transitions.append((position,(position[x],position[y]-1)))
        if(position[1]<row-1):
            if((position[x],position[y]+1) not in Positions_of_particles):
                Transitions.append((position,(position[x],position[y]+1)))
    return Transitions

def Perform_Transition(Positions_of_particles, Transitions):
    Chosen_Transition=choice(Transitions)
    Positions_of_particles.remove(Chosen_Transition[0])
    Positions_of_particles.append(Chosen_Transition[1])
    return Positions_of_particles

def Entropy_calc(Positions_of_particles, N):
    # use the min and max functions to obtain "Lattice_spread"
    x_vals=[]
    y_vals=[]
    for p in Positions_of_particles:
        x_vals.append(p[0])
        y_vals.append(p[1])
    Lattice_spread=(max(x_vals)-min(x_vals)+1)*(max(y_vals)-min(y_vals)+1)
    return log(factorial(Lattice_spread)/(factorial(N)*factorial(Lattice_spread - N)))

def Create_image(Positions_of_particles, TrNum, row, col): #TrNum keeps track of the step number in the loop. 
    Current_state=zeros((row,col))
    for p in Positions_of_particles:
        Current_state[p[1]][p[0]]=1
    imgplot = plt.imshow(Current_state, cmap='binary')
    plt.savefig('Lattice' + str(TrNum) + '.png')

#Use the initialize function to create a list of all the particles positions
Positions_of_particles=Initialize(row, col, N)
#Set up the list with possible transitions
Transitions=[]
#Remember to set up lists for the time stamp and the local entropy that can be updated inside the loop
time=0
t=[0]
local_entropy=[Entropy_calc(Positions_of_particles, N)]

#Start the loop. Both a for-loop and a while-loop will work.
for TrNum in range(1,Num_steps):
    #Update the positions lists using Perform_Transition()
    Transitions=Possible_transitions(Positions_of_particles, row, col)
    Positions_of_particles=Perform_Transition(Positions_of_particles, Transitions)
    #Calculate the present time: time += "KMC equation for time". Note that the time is updated in every step but only stored when the entropy is stored
    time+=-log(uniform(0,1))/N
    #Recalculate the possible transitions (too complex to update, just recalculate from scratch
        #Remember to store an image at a regular interval. Use for example: if TrNum % Dump_interval == 0:
        #Update the entropy and time stamp lists, also at a regular interval. Make sure that the time step list reflects the total time passed at any given point.
    if(TrNum%Dump_interval==0):
        Create_image(Positions_of_particles, TrNum, row, col)
    if(TrNum%Data_interval==0):
        t.append(time)
        local_entropy.append(Entropy_calc(Positions_of_particles, N))
#The code below creates the plots the local entropy as a function of time.

plt.clf()
plt.plot(t, local_entropy)
plt.show()
