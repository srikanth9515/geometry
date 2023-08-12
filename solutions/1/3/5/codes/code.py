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

A = np.array([[1,1],[5,-7]])             #Defining the matrix A
B = np.array([2,20])                     #Defining the vector B
H = np.linalg.solve(A,B) 

A = np.array([1,-1])
B = np.array([-4, 6])
C = np.array([-3,-5])
D = alt_foot(A,B,C)
E = alt_foot(B,A,C)
F = alt_foot(C,A,B)

x_AB = line_gen(A,B)	
x_BC = line_gen(B,C)
x_CA = line_gen(C,A)
x_AD = line_gen(A,D)
x_AE = line_gen(A,E)
x_BE = line_gen(B,E)
x_CF = line_gen(C,F)
x_AF = line_gen(A,F)
x_CH = line_gen(C,H)
x_BH = line_gen(B,H)
x_AH = line_gen(A,H)

#Triangle coordinates
#[A,B,C] = tri_vert(a,b,c)


#Plotting all lines
plt.plot(x_AB[0,:],x_AB[1,:],label='$AB$')
plt.plot(x_BC[0,:],x_BC[1,:],label='$BC$')
plt.plot(x_CA[0,:],x_CA[1,:],label='$CA$')
plt.plot(x_AD[0,:],x_AD[1,:],label='$AD_1$')
plt.plot(x_BE[0,:],x_BE[1,:],label='$BE_1$')
plt.plot(x_AE[0,:],x_AE[1,:],linestyle = 'dashed',label='$AE_1$')
plt.plot(x_CF[0,:],x_CF[1,:],label='$CF_1$')
plt.plot(x_AF[0,:],x_AF[1,:],linestyle = 'dashed',label='$AF_1$')
plt.plot(x_CH[0,:],x_CH[1,:],label='$CH$')
plt.plot(x_BH[0,:],x_BH[1,:],label='$BH$')
plt.plot(x_AH[0,:],x_AH[1,:],linestyle = 'dashed',label='$AH$')

#Labeling the coordinates
A = A.reshape(-1,1)
B = B.reshape(-1,1)
C = C.reshape(-1,1)
D = D.reshape(-1,1)
E = E.reshape(-1,1)
F = F.reshape(-1,1)
H = H.reshape(-1,1)
tri_coords = np.block([[A,B,C,D,E,F,H]])
plt.scatter(tri_coords[0,:], tri_coords[1,:])
vert_labels = ['A','B','C','D_1','E_1','F_1','H']
for i, txt in enumerate(vert_labels):
    plt.annotate(txt, # this is the text
                 (tri_coords[0,i], tri_coords[1,i]), # this is the point to label
                 textcoords="offset points", # how to position the text
                 xytext=(0,10), # distance from text to points (x,y)
                 ha='center') # horizontal alignment can be left, right or center

plt.xlabel('$x$')
plt.ylabel('$y$')
plt.title('Plot')
plt.legend(loc='best')
plt.grid() # minor
plt.axis('equal')

#code for calculations starts from here
A = np.array([1,-1])
print("Point A is : ",A)
B = np.array([-4,6])
print("Point B is : ",B)
C = np.array([-3,-5])
print("Point C is : ",C)
H = np.array([17/6,-5/6])
print("Point H is : ",H)

val1 = A-H
val2 = B-C

result = val1@val2

#Result will come in the form of e-16, we can use round function to round it off to 0
rounded = round(result,6)

print("The resultant of the product is : ",rounded)

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







