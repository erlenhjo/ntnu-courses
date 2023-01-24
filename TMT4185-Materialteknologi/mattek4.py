import numpy as np
import matplotlib.pyplot as plt

A_0=np.pi*41*10**(-6)
load=np.array([0,7330,15100,23100,30400,34400,38400,41300,44800,46200,47300,47500,46100,44800,42600,36400])
stress=load/A_0
length=np.array([50.8,50.851,50.902,50.952,51.003,51.054,51.308,51.816,52.832,53.848,54.864,55.880,56.896,57.658,58.420,59.182])
delta_L=length-length[0]
strain=delta_L/length[0]
elastisity=stress[1:5]/strain[1:5]
plt.subplot(2,1,1)
plt.plot(strain, stress)
plt.subplot(2,1,2)
plt.plot(strain[:8],stress[:8])
plt.plot(strain[:6]+0.002,strain[:6]*elastisity[0])

plt.show()


print(sum(elastisity)/4/10**(9), "GPa")
print(strain[5]*elastisity[0]/10**6, "MPa")
print(max(stress)/10**6,"MPa")
print(max(strain))
print(1/2*strain[5]*elastisity[0]*(strain[5]+0.002))