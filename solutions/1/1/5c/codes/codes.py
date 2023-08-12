import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mping
#Orthogonal matrix
k = np.array([[0,1],[-1,0]])

A = np.array([1, -1])
C=np.array([-3, -5])
#Direction vector
def dir_vec(A, C):
  return A - C
#Normal vector
def norm_vec(A, C):
    return k @ dir_vec(A, C)

n = norm_vec(A, C)

l=n@C
print(n,"x=",l)

def line_gen(A,B):
  len =10
  dim = A.shape[0]
  x_AB = np.zeros((dim,len))
  lam_1 = np.linspace(0,1,len)
  for i in range(len):
    temp1 = A + lam_1[i]*(B-A)
    x_AB[:,i]= temp1.T
  return x_AB
  
x_CA = line_gen(C, A)
plt.plot(x_CA[0,:],x_CA[1,:],label='$CA$')
C = C.reshape(-1, 1)
A = A.reshape(-1, 1)
tri_coords = np.block([[C,A]])
plt.scatter(tri_coords[0,:], tri_coords[1,:])
vert_labels = ['C','A']

for i, txt in enumerate(vert_labels):
    plt.annotate(txt, (tri_coords[0,i], tri_coords[1,i]), textcoords="offset points", xytext=(0,10), ha='center') 
                
plt.xlabel('X axis')
plt.ylabel('Y axis')
plt.legend(loc='best')
plt.grid() 
plt.axis('equal')
plt.savefig("fig")
