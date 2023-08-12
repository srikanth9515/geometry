import math
import sys
sys.path.insert(0, "./codes")
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import math

#local imports
from line.funcs import *
from triangle.funcs import *
from conics.funcs import circ_gen

A=np.array([1, -1])
B=np.array([-4, 6])
C=np.array([-3, -5])

x_AB = line_gen(A, B)
x_BC = line_gen(B, C)
x_CA = line_gen(C, A)

#generating the incircle
[I,r] = icircle(A,B,C)
x_icirc= circ_gen(I,r)

#plotiing the lines
plt.plot(x_AB[0,:],x_AB[1,:],label='$AB$')
plt.plot(x_BC[0,:],x_BC[1,:],label='$BC$')
plt.plot(x_CA[0,:],x_CA[1,:],label='$CA$')

#plotting the incircle
plt.plot(x_icirc[0,:],x_icirc[1,:],label='$incircle$')

#labelling the coordinates
tri_coords = np.block([[A],[B],[C],[I]]).T
tri_coords = tri_coords.reshape(2, -1)
plt.scatter(tri_coords[0,:], tri_coords[1,:])
vert_labels = ['A','B','C','I']

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

plt.savefig('./figs/Diagram.png')
