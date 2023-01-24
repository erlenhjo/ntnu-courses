from sympy import diff, symbols, solve, evalf, plot

r = symbols('r')

eps=0.997
sig=3.4

V = 4*eps*((sig/r)**12-(sig/r)**6)
Fr=-diff(V, r)
print(solve(V, r))
print(solve(Fr, r))
r1=4
print(V.evalf(subs={r:r1}))
print(Fr.evalf(subs={r:r1}))

plot(V, (r, 0, 2*r1), xlabel='Radial distance', ylabel='Potential', axis_center=(0,0), ylim=(-eps,eps))
plot(Fr, (r, 0, 2*r1), xlabel='Radial distance', ylabel='Force', axis_center=(0,0), ylim=(-eps,eps))