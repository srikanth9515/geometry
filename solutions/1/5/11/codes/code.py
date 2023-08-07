import numpy as np

#defining vertices of triangle in matrix format
A = np.array([1,-1])
B = np.array([-4,6])
C = np.array([-3,-5])

#finding sidelengths a, b & c
a = np.linalg.norm(B-C)
b = np.linalg.norm(C-A)
c = np.linalg.norm(A-B)

#creating array containing coefficients
Y = np.array([[1,1,0],[0,1,1],[1,0,1]])

#solving the equations
X = np.linalg.solve(Y,[c,a,b])

#printing output 
print(X)