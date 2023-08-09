import numpy as np
from sympy import init_printing
init_printing(use_unicode=True)
from sympy.matrices import Matrix
from numpy import linalg as LA
import sys                                          #for path to external scripts
#sys.path.insert(0, '/home/user/txhome/storage/shared/gitlab/res2021/july/conics/codes/CoordGeo')        #path to my scripts
sys.path.insert(0, '/home/sujalgupat484/Desktop/probability/math/codes/CoordGeo')        #path to my scripts
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

#local imports
from line.funcs import *

from triangle.funcs import *
from conics.funcs import circ_gen
A=np.array([1,-1])
B=np.array([-4,6])
C=np.array([-3,-5])
D=C-B
a=np.linalg.norm(C-B)
b=np.linalg.norm(A-C)
c=np.linalg.norm(A-B)
I=np.array([-1.47756217,-0.79495069])
print("the incentre coordiantes are",I)
# by using the data from previous question we have inradius value r
radius=1.8968927705299559
p=pow(np.linalg.norm(C-B),2)
q=2*(D@(I-B))
r=pow(np.linalg.norm(I-B),2)-radius*radius

Discre=q*q-4*p*r

print("the Value of discriminant is ",abs(round(Discre,6)))
#  so the value of Discrimant is extremely small and tends to zero
#  the discriminant value rounded off to 6 decimal places is also zero
#  so it proves that there is only one solution of the point

#  the value of point is x=B+k(C-B)
k=((I-B)@(C-B))/((C-B)@(C-B))
print("the value of parameter k is ",k)
D3=B+k*(C-B)
print("the point of tangency of incircle by side BC is ",D3)
#  to check we also check the value of dot product of ID3 and BC
#print("the dot product of ID3 and BC",abs(round(((D3-I)@(C-B),6))))
#  so this comes out to be zero
print("Hence we prove that side BC is tangent To incircle and also found the value of k!")

# #Code by GVV Sharma
# #December 7, 2019
# #released under GNU GPL
# #Drawing a triangle given 3 sides

# import matplotlib.pyplot as plt
# import matplotlib.image as mpimg
# image = mpimg.imread('exit-ramp.jpg')
# plt.imshow(image)
# plt.show()
#Triangle coordinates
[A,B,C] = tri_vert(a,b,c)
A=np.array([1,-1])
B=np.array([-4,6])
C=np.array([-3,-5])
a=np.linalg.norm(C-B)
b=np.linalg.norm(A-C)
c=np.linalg.norm(A-B)
#Generating all lines
x_AB = line_gen(A,B)
x_BC = line_gen(B,C)
x_CA = line_gen(C,A)

#Generating the incircle
[I,r] = icircle(A,B,C)
x_icirc= circ_gen(I,radius)
#Plotting all lines
plt.plot(x_AB[0,:],x_AB[1,:],label='$AB$')
plt.plot(x_BC[0,:],x_BC[1,:],label='$BC$')
plt.plot(x_CA[0,:],x_CA[1,:],label='$CA$')
# plt.plot(x_BD[0,:],x_BD[1,:],label='$BD$')
#Plotting the incircle
plt.plot(x_icirc[0,:],x_icirc[1,:],label='$incircle$')
plt.plot(D3[0],D3[1],label='$D_3$')
A = A.reshape(-1,1)
B = B.reshape(-1,1)
C = C.reshape(-1,1)
I = I.reshape(-1,1)
D3=D3.reshape(-1,1)
#Labeling the coordinates
tri_coords = np.block([[A,B,C,D3,I]])
plt.scatter(tri_coords[0,:], tri_coords[1,:])
vert_labels = ['A','B','C','D3','I']
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
plt.savefig('/home/sujalgupat484/Desktop/probability/assgn1_1.5.8/figs/incircle.png')
#subprocess.run(shlex.split("termux-open ./figs/tri_sss.pdf"))
#else
# image = mpimg.imread('tri_sss.png')
# plt.imshow(image)
#plt.show()







