#Find the distance between I(incentre) and AB, and I and AC.
import numpy as np
A = np.array([[1],[-1]])  
C = np.array([[-3],[-5]])
I=(1/(np.sqrt(37) + 4 + np.sqrt(61)))*np.array([[np.sqrt(61) - 16 - 3*np.sqrt(37)],[-np.sqrt(61) + 24 - 5*np.sqrt(37)]])    #Here I is incentre (point of intersection of angle bisectors)
n1 = np.array([[7], [5]])   #n1 is normal vector of AB
n2 = np.array([[4], [-4]])  #n2 is normal vector of AC
n1T = n1.T   #taking transpose of n1
n2T = n2.T   #taking transpose of n2
r1 = abs((n1T @ I) - (n1T @ A))/(np.linalg.norm(n1))   #r1 is distance between I and AB (n1T.I - n1T.A=0, n1 and I are vectors)
r2 = abs((n2T @ I) - (n2T @ C))/(np.linalg.norm(n2))   #r2 is distance between I and AC (n2T.I - n2T.C=0, n2 and I are vectors)
print("Distance between I and AB is",r1)
print("Distance between I and AC is",r2)
