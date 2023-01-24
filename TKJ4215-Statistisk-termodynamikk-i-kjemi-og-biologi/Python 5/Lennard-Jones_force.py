from sympy import diff, symbols, solve, plot

eps, sig, r = symbols('eps sig r')

#Removing # from eps and sig below will turn eps and sig into normal variables instead of python symbols.
eps = 1
sig = 5

V = 4*eps*((sig/r)**12-(sig/r)**6)

Fr=-diff(V, r)
print("Fr is: ", Fr)

print(solve(Fr, r)) #Den reelle, positive løsningen.

plot(Fr, (r, 0, 10), xlabel='Radial distance', ylabel='Force', axis_center=(0,0), ylim=(-eps,eps))




