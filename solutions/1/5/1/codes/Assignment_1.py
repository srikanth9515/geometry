import sys
sys.path.insert(0, "/home/lancelot/Latex/EE2102/CoordGeo")
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import math

from line.funcs import *
from triangle.funcs import *
from conics.funcs import circ_gen
def unit_vec(A,B):
	return ((B-A)/np.linalg.norm(B-A))




A=np.array([1, -1])
B=np.array([-4, 6])
C=np.array([-3, -5])

x_AB = line_gen(A, B)
x_BC = line_gen(B, C)
x_CA = line_gen(C, A)

[I,r] = icircle(A,B,C)
x_icirc= circ_gen(I,r)
x_AI = line_gen(A ,I)



plt.plot(x_AB[0,:],x_AB[1,:],label='$AB$')
plt.plot(x_BC[0,:],x_BC[1,:],label='$BC$')
plt.plot(x_CA[0,:],x_CA[1,:],label='$CA$')
plt.plot(x_AI[0,:],x_AI[1,:],label='$AI$')


tri_coords = np.vstack((A,B,C,I)).T
plt.scatter(tri_coords[0,:], tri_coords[1,:])
vert_labels = ['A','B','C','I']
for i, txt in enumerate(vert_labels):
    plt.annotate(txt,
                 (tri_coords[0,i], tri_coords[1,i]),
                 textcoords="offset points", 
                 xytext=(0,10), 
                 ha='center') 


plt.xlabel('$x$')
plt.ylabel('$y$')
plt.legend(loc='best')
plt.grid()
plt.axis('equal')
plt.savefig('/home/lancelot/Latex/EE2102/Assignment_1/figs/angular_bisector.png')
#code for finding angular bisector.
A=np.array([1, -1])
B=np.array([-4, 6])
C=np.array([-3, -5])
#using parallelogram theorem
E= unit_vec(A,B) + unit_vec(A,C)
#point generated to create parametric form
#generating normal form
F=np.array([E[1],(E[0]*(-1))])
#matrix multiplication
C1= F@(A.T)
print("Internal Angular bisector of angle A is:",F,"*x = ",C1)
