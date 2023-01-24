from math import log
import matplotlib.pyplot as plt

def Stirling(n):
    return n*log(n)-n

points=20
N = 100
Particles = [N//points*i for i in range(1,points)]

logW = [Stirling(N)-Stirling(n)-Stirling(N-n) for n in Particles] #Tip: Use list comprehension

plt.plot(Particles,logW)
plt.title("Entropy by particles on lattice")
plt.ylabel("S/k")
plt.xlabel("Particles")
plt.show()

#n=N/2
#øker lineært med N
#Samme formel for høyest entropi, n=N/2, ikke samme verdi