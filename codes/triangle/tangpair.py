#Code by GVV Sharma
#June 12, 2022
#Revised November 14, 2023
#released under GNU GPL
#https://www.gnu.org/licenses/gpl-3.0.en.html

#Drawing a pair of tangents to a conic

import sys                                          #for path to external scripts
sys.path.insert(0, '/sdcard/github/geometry/codes/CoordGeo')        #path to my scripts
import numpy as np
import matplotlib.pyplot as plt
from numpy import linalg as LA

#local imports
from line.funcs import *
from triangle.funcs import *
from conics.funcs import *

#if using termux
import subprocess
import shlex
#end if



#Triangle vertices
A = np.array([1,-1]).reshape(-1,1)
B = np.array([-4,6]).reshape(-1,1) 
C = np.array([-3,-5]).reshape(-1,1) 

#Incircle parameters

h  = B
V = np.eye(2)
[I,r] = icircle(A,B,C)
u = -I
f = LA.norm(I)**2-r**2

[x1,x2] = contact(V,u,f,h)
print(x1,x2)

'''
#intermediate
gh = h.T@V@h+2*u.T@h+f 

#matrix of tangents
sigmat = (V@h+u)@(V@h+u).T-gh*V


#Spectral decomposition
D, P = LA.eig(sigmat)

u1 = np.array(([np.sqrt(np.abs(D[1])),np.sqrt(np.abs(D[0]))]))
u2 = np.array(([np.sqrt(np.abs(D[1])),-np.sqrt(np.abs(D[0]))]))

u1 = u1.reshape(-1,1)
u2 = u2.reshape(-1,1)

#direction vectors
m1 = P@u1
m2 = P@u2
#print(m1,m2)
# Converting 1D array to a 2D numpy array of incompatible shape will cause error
m1= np.reshape(m1, (2, 1))
m2= np.reshape(m2, (2, 1))
mu1 = -(m1.T@(V@h+u))/(m1.T@V@m1)
mu2 = -(m2.T@(V@h+u))/(m2.T@V@m2)
#print(mu1,mu2)
x1 = h + mu1*m1
x2 = h + mu2*m2

print(x1,x2)
'''
