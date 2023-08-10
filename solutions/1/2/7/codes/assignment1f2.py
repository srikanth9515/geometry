import numpy as np
import matplotlib.pyplot as plt
from coeffs import *


if __name__ == "__main__":
    # Given points A,B,C,D,E,F
    A = np.array (([1,-1]))
    B = np.array (([-4,6]))
    C = np.array (([-3,-5]))
#computing D,E,F using A,B,C
D=(B+C)/2
E=(C+A)/2
F=(A+B)/2
    
LHS=(A-F)
RHS=(E-D)
#checking LHS and RHS 
if LHS.all()==RHS.all() :
   print("A-F=E-D")
else:
    print("Not equal")

#Generating all lines 
x_AB = line_gen(A,B)
x_BC = line_gen(B,C)
x_CA = line_gen(C,A)
x_AF = line_gen(A,F)
x_FD = line_gen(F,D)
x_DE = line_gen(D,E)
x_EA = line_gen(E,A)

#plotting all lines 

plt.plot(x_AB[0,:],x_AB[1,:],label='$AB$')
plt.plot(x_BC[0,:],x_BC[1,:],label='$BC$')
plt.plot(x_CA[0,:],x_CA[1,:],label='$CA$')
plt.plot(A[0], A[1], 'o')
plt.text(A[0] * (1.2 + 0.05), A[1] * (1 - 0.1) , 'A')
plt.plot(B[0], B[1], 'o')
plt.text(B[0] * (1.2 + 0.05), B[1] * (1 - 0.1) , 'B')
plt.plot(C[0], C[1], 'o')
plt.text(C[0] * (1.2 + 0.05), C[1] * (1 - 0.1) , 'C')

plt.plot(x_AF[0,:],x_AF[1,:],label='$AF$')
plt.plot(x_FD[0,:],x_FD[1,:],label='$FD$')
plt.plot(x_DE[0,:],x_DE[1,:],label='$DE$')
plt.plot(x_EA[0,:],x_EA[1,:],label='$EA$')

plt.plot(A[0], A[1], 'o')
plt.text(A[0] * (1.2 + 0.05), A[1] * (1 - 0.1) , 'A')
plt.plot(F[0], F[1], 'o')
plt.text(F[0] * (1.2 + 0.05), F[1] * (1 - 0.1) , 'F')
plt.plot(D[0], D[1], 'o')
plt.text(D[0] * (1.2 + 0.05), D[1] * (1 - 0.1) , 'D')
plt.plot(D[0], D[1], 'o')
plt.text(E[0] * (1.2 + 0.05), E[1] * (1 - 0.1) , 'E')


plt.xlabel('$x$')
plt.ylabel('$y$')
plt.legend(loc='best')
plt.grid() # minor
plt.axis('equal')

plt.show()
