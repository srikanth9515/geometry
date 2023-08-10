import numpy as np

A = np.array([1, -1])
B = np.array([-4, 6])
C = np.array([-3, -5])
# O is a point of intersection of perpendicular bisectors of AB and AC
O = np.array([-53 / 12, 5 / 12])

#To find angle BOC
dot_pt_O = (B - O) @ ((C - O).T)
norm_pt_O = np.linalg.norm(B - O) * np.linalg.norm(C - O)
cos_theta_O = dot_pt_O / norm_pt_O
angle_BOC = round(360-np.degrees(np.arccos(cos_theta_O)),5)  #Round is used to round of number till 5 decimal places
print("angle BOC = " + str(angle_BOC))

#To find angle BAC
dot_pt_A = (B - A) @ ((C - A).T)
norm_pt_A = np.linalg.norm(B - A) * np.linalg.norm(C - A)
cos_theta_A = dot_pt_A / norm_pt_A
angle_BAC = round(np.degrees(np.arccos(cos_theta_A)),5)  #Round is used to round of number till 5 decimal places
print("angle BAC = " + str(angle_BAC))
#To check whether the answer is correct
if angle_BOC == 2 * angle_BAC:
  print("\nangle BOC = 2 times angle BAC\nHence the give statement is correct")
else:
  print("\nangle BOC ≠ 2 times angle BAC\nHence the given statement is wrong")
import sys                                        
sys.path.insert(0, '/home/peter/math/codes/CoordGeo')
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from line.funcs import *
from triangle.funcs import *
from conics.funcs import circ_gen
import subprocess
import shlex
#end if

O = np.array([-53/12, 5/12])
A = np.array([1, -1])
B = np.array([-3, -5])
C = np.array([-4, 6])

#Generating all lines
x_AB = line_gen(A,B)
x_AC = line_gen(A,C)
x_OB = line_gen(O,B)
x_OC = line_gen(O,C)

#Generating the circumcircle
[O,R] = ccircle(A,B,C)
x_circ= circ_gen(O,R)

#Plotting all lines
plt.plot(x_AB[0,:],x_AB[1,:],label='$AB$')
plt.plot(x_AC[0,:],x_AC[1,:],label='$BC$')
plt.plot(x_OB[0,:],x_OB[1,:],label='$OB$')
plt.plot(x_OC[0,:],x_OC[1,:],label='$OB$')
#Plotting the circumcircle
plt.plot(x_circ[0,:],x_circ[1,:],label='$circumcircle$')


#Labeling the coordinates
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
plt.grid() 
plt.axis('equal')
plt.savefig('fig_1.png')







