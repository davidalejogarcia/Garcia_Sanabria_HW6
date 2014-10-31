import sys
import matplotlib.pyplot as plt
import numpy as np


entrada=sys.argv[1]


entrada1=entrada.split(".")
data=np.loadtxt(entrada)

plt.ylabel("Y")
plt.xlabel("X")

plt.plot(data[:,0], data[:,1])



plt.savefig(entrada1[0]+".pdf")


