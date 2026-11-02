"""  import what's necessary """
import numpy as np
from scipy.integrate import solve_ivp
import matplotlib.pyplot as plt


def evolution(t, z, a, b, c, d):
    """ 
    definition of equation
        # t : time, unsused but necessary for ODE
        # z : [x,y] vector, initial conditions
        # a,b,d,c: parameters
    """
    x, y = z
    return [a*x - b*x*y,  c*x*y - d*y]

# using SciPy Initial Value Problem solver
# args is a list of (a,b,c,d) values
X0   = 0
Y0   = 0
TMAX = 10.0
sol  = solve_ivp(evolution, 
                 [0,TMAX], 
                 [X0, Y0], 
                 args=(-1, 0, 0, 1),
                 dense_output=True)

# using result to draw something
t = np.linspace(0, TMAX, 300)
z = sol.sol(t)
plt.plot(t, z.T)
plt.xlabel('t')
plt.legend(['preys', 'predators'], shadow=True)
plt.title('Preys vs Predators')
plt.grid(color='g', linestyle='dotted', linewidth=1)
plt.show()

# plot phase space: y as a function of x
xy = np.split(z.T,2,axis=1)
plt.plot(xy[0],xy[1])
plt.title('Phase Space')
plt.xlabel('Preys')
plt.ylabel('Predators')
plt.grid(color='g', linestyle='dotted', linewidth=1)
