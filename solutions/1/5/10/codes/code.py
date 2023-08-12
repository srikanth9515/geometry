import numpy as np
import math 
A=np.array([1,-1])
B=np.array([-4,6])
C=np.array([-3,-5])
D_3=np.array([-3.367,-0.967])
E_3=np.array([-0.136,-2.136])
F_3=np.array([0.066,0.308])
def norm(X,Y):
    magnitude=round(float(np.linalg.norm([X-Y])),3)
    return magnitude 
print("AE_3=", norm(A,E_3) ,"\nAF_3=", norm(A,F_3) ,"\nBD_3=", norm(B,D_3) ,"\nBF_3=", norm(B,F_3) ,"\nCD_3=", norm(C,D_3) ,"\nCE_3=",norm(C,E_3))
