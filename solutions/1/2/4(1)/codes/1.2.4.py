import numpy as np

from line_operations import line_section,dir_vec,norm_vec,line_intersect

A = np.array([1,-1])
B = np.array([-4,6])
C = np.array([-3,-5])

#initializing variables
G = np.zeros(2) 
D = np.zeros(2)
E = np.zeros(2)
F = np.zeros(2)

#find D,E,F
D = line_section(B,C,1.0)
E = line_section(C,A,1.0)
F = line_section(A,B,1.0)

G = line_intersect(B,E,C,F)

print("The vector G is",G)

#finding the direction of vector
BG = dir_vec(B,G)
GE = dir_vec(G,E)
GF = dir_vec(G,F)
CG = dir_vec(C,G)
AG = dir_vec(A,G)
GD = dir_vec(G,D)

#finding the norm of vector
n_BG = norm_vec(B,G)
n_GE = norm_vec(G,E)
n_GF = norm_vec(G,F)
n_CG = norm_vec(C,G)
n_AG = norm_vec(A,G)
n_GD = norm_vec(G,D)

print("The direction vector of BG is",BG)
print("The direction vector of GE is",GE)
print("The direction vector of GF is",GF)
print("The direction vector of CG is",CG)
print("The direction vector of AG is",AG)
print("The direction vector of GD is",GD)

print("The norm of the vector BG is",n_BG)
print("The norm of the vector GE is",n_GE)
print("The norm of the vector GF is",n_GF)
print("The norm of the vector CG is",n_CG)
print("The norm of the vector AG is",n_AG)
print("The norm of the vector GD is",n_GD)

print("The ratio BG/GE is",n_BG/n_GE)
print("The ratio CG/GF is",n_CG/n_GF)
print("The ratio AG/GD is",n_AG/n_GD)
