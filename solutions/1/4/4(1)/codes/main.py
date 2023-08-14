import numpy as np
#PPoints of triangle
A = np.array ([ 1 ,-1 ])
B = np.array ([ -4 ,6 ])
C = np.array ([ -3 ,-5 ])
#Circumcentre
O = np.array ([ -4.4167 , 0.4167 ])
# OA, OB, OC
O_1 = O - A
O_2 = O - B
O_3 = O - C
a = np.linalg.norm(O_1)
b = np.linalg.norm(O_2)
c = np.linalg.norm(O_3)
print("Points of triangle A, B, C respectively are", A ,",", B ,",", C, ".")
print("Circumcentre of triangle is", O, ".")
print(" OA, OB, OC are respectively", a,",", b,",",c, ".")
print("Here, OA = OB = OC.")
print("Hence verified.")
