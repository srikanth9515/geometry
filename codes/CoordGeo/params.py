import numpy as np
import scipy.linalg as SA

#Orthogonal matrix
omat = np.array([[0,1],[-1,0]]) 

#Orthogonal matrix
R_o= np.array([[0,-1],[1,0]]) 

#Incircle circulant matrix
C_I = SA.circulant([1,1,0])

#Direction vector circulant matrix
C_m= SA.circulant([1,0,-1]).T


