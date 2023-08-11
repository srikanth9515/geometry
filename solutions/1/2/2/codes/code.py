# #Code by GVV Sharma
# #December 7, 2019
# #released under GNU GPL
# #Drawing a triangle given 3 sides

# import matplotlib.pyplot as plt
# import matplotlib.image as mpimg
# image = mpimg.imread('exit-ramp.jpg')
# plt.imshow(image)
# plt.show()

import sys                                          #for path to external scripts
#sys.path.insert(0, '/home/user/txhome/storage/shared/gitlab/res2021/july/conics/codes/CoordGeo')        #path to my scripts
sys.path.insert(0, '/home/quantum_fusion/math/codes/CoordGeo')        #path to my scripts
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

#local imports
from line.funcs import *

from triangle.funcs import *
from conics.funcs import circ_gen


#sys.path.insert(0, '/home/quantum_fusion/math/codes/CoordGeo')        #path to my scripts

#if using termux
import subprocess
import shlex
#end if

A = np.array([1,-1])
D = np.array([-3.5,0.5])

#Triangle coordinates
#[A,B,C] = tri_vert(a,b,c)

#Generating all lines
x_AB = line_gen(A,D)
#x_BC = line_gen(B,C)
#x_CA = line_gen(C,A)

#Plotting all lines
plt.plot(x_AB[0,:],x_AB[1,:],label='$AD$')

#Labeling the coordinates
A = A.reshape(-1,1)
D = D.reshape(-1,1)
tri_coords = np.block([[A,D]])
plt.scatter(tri_coords[0,:], tri_coords[1,:])
vert_labels = ['A','D']
for i, txt in enumerate(vert_labels):
    plt.annotate(txt, # this is the text
                 (tri_coords[0,i], tri_coords[1,i]), # this is the point to label
                 textcoords="offset points", # how to position the text
                 xytext=(0,10), # distance from text to points (x,y)
                 ha='center') # horizontal alignment can be left, right or center

plt.xlabel('$x$')
plt.ylabel('$y$')
plt.title('Plot of line AD')
plt.legend(loc='best')
plt.grid() # minor
plt.axis('equal')

#code for calculations starts from here
A = np.array([1,-1])
print("Point A is : ",A)
D = np.array([-3.5,0.5])
print("Mid point of BC(D) is : ",D)

m = D-A
print("m = ",m)

nt = np.array([m[1]*1+m[0]*0,m[0]*-1+m[1]*0])

#calculation of constant we get on multiplying n^T and A
nt = (nt*2)/3
#the above step is done to cancel out the factor of 1/2 on both sides of equation

const = nt@A
print("Value of n^T.A = ",const)

#calculation code ends here

#if using termux
#plt.savefig('tri_sss.pdf')
plt.savefig('/home/quantum_fusion/EE2102/Assignment_1/figs/tri_sss.png')
plt.savefig('/home/quantum_fusion/EE2102/Assignment_1/figs/tri_sss.pdf')
#subprocess.run(shlex.split("termux-open ./figs/tri_sss.pdf"))
#else
# image = mpimg.imread('tri_sss.png')
# plt.imshow(image)
#plt.show()







