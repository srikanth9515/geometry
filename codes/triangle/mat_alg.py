#Code by GVV Sharma
#September 7, 2023
#Revised October 1, 2023
#Revised October 2, 2023
#released under GNU GPL
#Matrix Algebra


import sys                                          #for path to external scripts
sys.path.insert(0, '/home/gadepall/github/geometry/codes/CoordGeo')        #path to my scripts
import numpy as np
import numpy.linalg as LA
import scipy.linalg as SA
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import pandas as pd

#local imports
from line.funcs import *
from triangle.funcs import *
from conics.funcs import circ_gen


#if using termux
import subprocess
import shlex
#end if


#Input parameters from excel file
df= pd.read_excel('tables/vertices.xlsx')
#print(df)

#Triangle Vertices
G_v= df.to_numpy()[:,:]
#print(G_v, C_m)

#Direction vector Matrix
G_d = G_v@C_m

#Normal vector matrix
G_n = R_o@G_v@C_m

#sides vector
d = np.linalg.norm(G_d, axis=0)

#Finding the angles of the triangle
dmat = np.diag(1/d)
G_dnorm = G_d@dmat
G_dgram = G_dnorm.T@G_dnorm
#print(np.degrees(np.arccos(G_dgram)))

#Find the line constants
cmat = np.diag(G_n.T@G_v).reshape(1,-1)

#line matrix
linmat = np.block([G_n.T,cmat.T])
#print(linmat)
