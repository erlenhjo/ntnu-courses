from sympy import diff, latex, symbols, plot

r = symbols('r')

eps = 1
sig = 5

V = 4*eps*((sig/r)**12-(sig/r)**6)

plot(V, (r, 0, 10), xlabel='Radial distance', ylabel='Potential', axis_center=(0,0), ylim=(-eps,eps))


#God tilnærming av potensiell energi overflate "utseendemessig"
#Teoretisk lettere å regne på da man har k*(a^2-a)