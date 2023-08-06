import numpy as np
import matplotlib.pyplot as plt
from coeffs import *

def direction_vector (point_1 , point_2):
    return point_2 - point_1
def parametric_form (A,B,k):
    direction_vector_AB = direction_vector(A,B)
    x = A + k * direction_vector_AB
    return x

if __name__ == "__main__":
    # Given points A,B,C
    A = np.array (([1,-1]))
    B = np.array (([-4,6]))
    C = np.array (([-3,-5]))

    k_values = np.linspace(0,1,10)  #Given range and number of points
    
    print("parametric form of line AB:")
    for k in k_values:
        parametric_point_AB = parametric_form(A,B,k)
        print (f"(k) = {k},Parametric_form_AB:",parametric_point_AB)
    

    print("\nparametric form of line BC:")
    for k in k_values:
        parametric_point_BC = parametric_form(B,C,k)
        print (f"(k) = {k},Parametric_form_BC:",parametric_point_BC)

    print ("\nparametric form of line CA:")
    for k in k_values:
        parametric_point_CA = parametric_form(C,A,k)
        print (f"(k) = {k},Parametric_form_CA:",parametric_point_CA)
#Generating all lines 
x_AB = line_gen(A,B)
x_BC = line_gen(B,C)
x_CA = line_gen(C,A)
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

plt.xlabel('$x$')
plt.ylabel('$y$')
plt.legend(loc='best')
plt.grid() # minor
plt.axis('equal')

plt.show()
