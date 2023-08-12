import sys
sys.path.insert(0, "./codes/CoordGeo")
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import math

from line.funcs import *
from triangle.funcs import *
from conics.funcs import circ_gen

#function to generate points of contact

def pointOfContact(I, r, A, B):
    m = A-B
    n = A-I
    k = -((m@n)/(m@m))
    contactPoint = A + k*m
    return contactPoint

def discriminant(I, r, A, B):
    m = A-B
    n = A-I
    discr = 4*((m@n)**2) - 4*(m@m)*((n@n) - r**2)
    return discr

#vertices of triangle

A=np.array([1, -1])
B=np.array([-4, 6])
C=np.array([-3, -5])

#generating lines

x_AB = line_gen(A, B)
x_BC = line_gen(B, C)
x_CA = line_gen(C, A)

#generating incentre and finding inradius

[I,r] = icircle(A,B,C)
x_icirc= circ_gen(I,r)

#generating points of contact

d1 = discriminant(I, r, A, C)
d2 = discriminant(I, r, A, C)

print("the discriminants of the quadratics are, ",d1, d2, ", which are both approx 0")

E3 = pointOfContact(I, r, A, C)
F3 = pointOfContact(I, r, A, B)

#plotting sides

plt.plot(x_AB[0,:],x_AB[1,:],label='$AB$')
plt.plot(x_BC[0,:],x_BC[1,:],label='$BC$')
plt.plot(x_CA[0,:],x_CA[1,:],label='$CA$')

#plotting incircle

plt.plot(x_icirc[0,:],x_icirc[1,:],label='$incircle$')

#labeling points

tri_coords = np.block([[A],[B],[C],[E3],[F3],[I]]).T
plt.scatter(tri_coords[0,:], tri_coords[1,:])
vert_labels = ['A','B','C','E3', 'F3','I']
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

plt.savefig('./figs/Diagram.png')