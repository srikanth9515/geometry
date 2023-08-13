import numpy as np

# Coordinates of points A,B and C
A = np.array([1, -1])
B = np.array([-4, 6])
C = np.array([-3, -5])

# Calculate the matrix B-C
BC_matrix = B - C

length_BC = np.linalg.norm(BC_matrix)

print("Length of side BC:", length_BC)
