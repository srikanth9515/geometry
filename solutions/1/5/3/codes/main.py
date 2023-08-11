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
sys.path.insert(0, '/home/sayyam/EE23010/Qn1.5.3/codes/CoordGeo')        #path to my scripts
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

#local imports
from line.funcs import *

from triangle.funcs import *
from conics.funcs import circ_gen


#sys.path.insert(0, '/home/user/txhome/storage/shared/gitlab/res2021/july/conics/codes/CoordGeo')        #path to my scripts

#if using termux
import subprocess
import shlex
#end if

#Triangle sides
#a = 6
#b = 5
#c = 4


#Triangle coordinates
#[A,B,C] = tri_vert(a,b,c)

A = np.array([1, -1])
B = np.array([-4, 6])
C = np.array([-3, -5])

#Generating the incircle
[I,r] = icircle(A,B,C)
x_icirc= circ_gen(I,r)

#Generating all lines
x_AB = line_gen(A,B)
x_BC = line_gen(B,C)
x_CA = line_gen(C,A)
x_IA = line_gen(I,A)
#Generating the circumcircle
#[O,R] = ccircle(A,B,C)
#x_circ= circ_gen(O,R)


#Plotting all lines
plt.plot(x_AB[0,:],x_AB[1,:],label='$AB$')
plt.plot(x_BC[0,:],x_BC[1,:],label='$BC$')
plt.plot(x_CA[0,:],x_CA[1,:],label='$CA$')
plt.plot(x_IA[0,:],x_IA[1,:],label='$IA$')
#Plotting the circumcircle
#plt.plot(x_circ[0,:],x_circ[1,:],label='$circumcircle$')

#Plotting the circumcircle
#plt.plot(x_icirc[0,:],x_icirc[1,:],label='$incircle$')

#BA, CA, and IA in vector form
BA = A - B
CA = A - C
IA = A - I

def angle_btw_vectors(v1, v2):
    dot_product = v1 @ v2
    norm = np.linalg.norm(v1) * np.linalg.norm(v2)
    angle = np.arccos(dot_product / norm)
    angle_in_deg = np.degrees(angle)
    return angle_in_deg

#Calculating the angles BAI and CAI
angle_BAI = angle_btw_vectors(BA, IA)
angle_CAI = angle_btw_vectors(CA, IA)

# Print the angles
print("Angle BAI:", angle_BAI)
print("Angle CAI:", angle_CAI)

if np.isclose(angle_BAI, angle_CAI):
    print("Angle BAI is approximately equal to angle CAI.")
else:
    print("error")

#Labeling the coordinates
A = A.reshape(-1,1)
B = B.reshape(-1,1)
C = C.reshape(-1,1)
I = I.reshape(-1,1)
tri_coords = np.block([[A,B,C,I]])
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

#if using termux
#plt.savefig('tri_sss.pdf')
plt.savefig('/home/sayyam/EE23010/Qn1.5.3/fig/main.png')
#subprocess.run(shlex.split("termux-open ./figs/tri_sss.pdf"))
#else
# image = mpimg.imread('tri_sss.png')
# plt.imshow(image)
#plt.show()






