import numpy as np
import sympy as sp
import math
#points 
A=np.array([1,-1])
B=np.array([-4,6])
C=np.array([-3,-5])

#sides
bc=C-B
print(bc)
t=np.array([0,1,-1,0]).reshape(2,2)

#AD_1
AD_1=t@bc

#normal vector of AD_1
AD_p=t@AD_1

print(AD_p)


