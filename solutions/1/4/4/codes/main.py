import math
import numpy as np
import sys                                          
sys.path.insert(0, '/home/sameer/assignment3/CoordGeo')
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
#local imports
from line.funcs import *
from triangle.funcs import *
from conics.funcs import circ_gen
#if using termux
import subprocess
import shlex
A=np.array([1, -1])
B=np.array([-4, 6])
C=np.array([-3, -5])

#Generating all lines
x_AB = line_gen(A,B)
x_BC = line_gen(B,C)
x_CA = line_gen(C,A)

#Generating the circumcircle
[O,R] = ccircle(A,B,C)
x_circ= circ_gen(O,R)
x_OC = line_gen(O ,C)
x_OB = line_gen(O ,B)
x_OA = line_gen(O ,A)

#Generating the incircle
[I,r] = icircle(A,B,C)
x_icirc= circ_gen(I,r)

OA=np.linalg.norm(O-A)

OB=np.linalg.norm(O-B)

OC=np.linalg.norm(O-C)
 
if np.isclose(OA,OB,OC):
  print("Verified that OA=OB=OC")
else:
  print("error")
    


#Plotting all lines
plt.plot(x_AB[0,:],x_AB[1,:],label='$AB$')
plt.plot(x_BC[0,:],x_BC[1,:],label='$BC$')
plt.plot(x_CA[0,:],x_CA[1,:],label='$CA$')
plt.plot(x_OC[0,:],x_OC[1,:],label='$OC$')
plt.plot(x_OB[0,:],x_OB[1,:],label='$OB$')
plt.plot(x_OA[0,:],x_OA[1,:],label='$OA$')


A = A.reshape(-1,1)
B = B.reshape(-1,1)
C = C.reshape(-1,1)
O = O.reshape(-1,1)
tri_coords = np.block([[A,B,C,O]])
plt.scatter(tri_coords[0,:], tri_coords[1,:])
vert_labels = ['A','B','C','O']
for i, txt in enumerate(vert_labels):
    plt.annotate(txt, # this is the text
                 (tri_coords[0,i], tri_coords[1,i]), # this is the point to label
                 textcoords="offset points", # how to position the text
                 xytext=(0,10), # distance from text to points (x,y)
                 ha='center') # horizontal alignment can be left, right or center

plt.xlabel('$x$')
plt.ylabel('$y$')
plt.legend(loc='best')
plt.grid() # minor
plt.axis('equal')
plt.savefig('/home/sameer/assignment3/figs/circumcentre.png')

plt.show()





