#Code by GVV Sharma
#December 7, 2019
#Revised July 15, 2020
#released under GNU GPL
#Functions related to triangle

import numpy as np
from line.funcs import *
#from line.params import *
from params import *

#Triangle vertices
def tri_vert(a,b,c):
  p = (a**2 + c**2-b**2 )/(2*a)
  q = np.sqrt(c**2-p**2)
  A = np.array([p,q]) 
  B = np.array([0,0]) 
  C = np.array([a,0]) 
  return  A,B,C

#Triangle  mid points
def tri_mid_pt(A,B,C):
  D = (B+C)/2
  E = (C+A)/2
  F = (A+B)/2
  return  D,E,F


#Radius and centre of the circumcircle
#of triangle ABC
def ccircle(A,B,C):
    D,E,F = tri_mid_pt(A,B,C)
    m1 = dir_vec(A,B)
    m2 = dir_vec(A,C)
    O = line_intersect(m1,F,m2,E)
    r = np.linalg.norm(A -O)
    return O,r

#Radius and centre of the incircle
#of triangle ABC
def icircle(A,B,C):
  k1 = 1
  k2 = 1
  p = np.zeros(2)
  t = norm_vec(B,C)
  n1 = t/np.linalg.norm(t)
  t = norm_vec(C,A)
  n2 = t/np.linalg.norm(t)
  t = norm_vec(A,B)
  n3 = t/np.linalg.norm(t)
  p[0] = n1@B- k1*n2@C
  p[1] = n2@C- k2*n3@A
  #Intersection
  N=np.block([[n1 - k1 * n2],[ n2 - k2 * n3]])
  I=np.linalg.solve(N,p)
  r = n1@(I-B)
  return I,r
