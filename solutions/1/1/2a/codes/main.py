import numpy as np
import math
A = np.array([1,-1])
B = np.array([-4,6])
C = np.array([-3,-5])

V1 = A - B
V2 = V1.reshape(-1,1)
print("The length of AB is:")
print(math.sqrt(V1@V2))

V3 = B - C
V4 = V3.reshape(-1,1)
print("The length of BC is:")
print(math.sqrt(V3@V4))

V5 = A - C
V6 = V5.reshape(-1,1)
print("The length of AC is:")
print(math.sqrt(V5@V6))
