from sympy import symbols, diff, nsolve, Symbol, log

x, y, L = symbols('x, y, L') #Defines the mathematical variable symbols to be used. L represents lambda, because lambda is a reserved keyword in Python.
f = x**2-8*x+y**2-12*y+48#Insert function f to be maximised/minimised.
g = x+y-8#Insert constraint function g in the form g(x1,x2,...) - constant

def finding_equations(f, g):
    Equations=[]
    for symbol in f.atoms(Symbol): #f.atoms(Symbol) picks out the symbols that represent our variables.
        Equations.append(diff(f,symbol)-L*diff(g,symbol))

    Equations.append(g)
    print(Equations)
    return Equations

Result = nsolve(finding_equations(f, g), [x, y, L], [1,1,1]) 
#nsolve takes a set of equations (determined by finding_equations(f,g) and solves for the given variables. 
#Takes at least three arguments: equations, symbols, strting estimate)
print(Result)


p1,p2,p3=symbols('p1,p2,p3')
Variables=[p1,p2,p3]
f=-sum([i*log(i) for i in Variables])
g=sum(Variables)-1

Result = nsolve(finding_equations(f, g), [p1,p2,p3,L], [1,1,1,1]) 
print(Result)
