import numpy as np

A = np.array([1, -1])
B = np.array([-4, 6])
C = np.array([-3, -5])
omat = np.array([[0, 1], [-1, 0]])

def dir_vec(A, B):
    return B - A

def norm_vec(A, B):
    return omat @ dir_vec(A, B)

k1=1
k2=1

p = np.zeros(2)
t = norm_vec(B, C)
n1 = t / np.linalg.norm(t)
t = norm_vec(C, A)
n2 = t / np.linalg.norm(t)
t = norm_vec(A, B)
n3 = t / np.linalg.norm(t)

p[0] = n1 @ B - k1 * n2 @ C
p[1] = n2 @ C - k2 * n3 @ A

N = np.block([[n1 - k1 * n2],[ n2 - k2 * n3]])
I = np.linalg.inv(N)@p
r = n1 @ (B-I)

print("Coordinates of point I:", I)
print(f"Distance from I to BC= {r}")
