import numpy as np

#for finding the direction vector
def dir_vec(A, B):
    return B - A

#for finding the norm of the vector
def norm_vec(A,B):
    N = np.array([0.0,0.0])
    N = np.linalg.norm(B-A)
    return N

#section formula
def line_section(A,B,k):
    P = np.array([0.0,0.0])
    P[0] = ((B[0]*k)+A[0])/(k+1)
    P[1] = ((B[1]*k)+A[1])/(k+1)

    return P

#intersection of lines
def line_intersect(B,E,C,F):
    m1 = dir_vec(B,E)
    m2 = dir_vec(C,F)
    p = np.zeros(2) 
    p[0] = (m2[0]*B[0]-m1[0]*C[0])/(m2[0]-m1[0])
    p[1] = (m2[1]*B[1]-m1[1]*C[1])/(m2[1]-m1[1])
    
    return p
    

