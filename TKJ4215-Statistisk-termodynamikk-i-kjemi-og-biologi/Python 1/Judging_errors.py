from math import factorial, log
import matplotlib.pyplot as plt

def stirling(n):
    return n*log(n)-n

def exact_sol(n):
    return sum([log(i) for i in range(1,n+1)] )

n = [10,100,1000,10000,100000,1000000] #Fill in the values of n that you wish to test

file = open("Stirlings.txt", "w") # Creates the file Stirlings.txt to be written
file.write( "           n      " + "Exact solution      " + "       Stirling     " + "Absolute error     " + "Relative error" +'\n') #Sets up the file header and adjusts column width

for i in n:
	file.write( "%12d      %14.4f       %14.4f     %14.4f     %14.4f" % (i, exact_sol(i), stirling(i), exact_sol(i) - stirling(i), (1 - stirling(i)/exact_sol(i)) )+ '\n') #Calculates n factorial, the approximation and corresponding errors.

#n er stor, relativ error er tilnærmet null