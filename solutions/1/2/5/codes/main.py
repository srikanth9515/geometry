import numpy as np

np.set_printoptions(precision=2)


a1 = int(input("Enter the first element of the first point on the triangle"))
a2 = int(input("Enter the second element of the first point on the triangle"))
b1 = int(input("Enter the first element of the second point on the triangle"))
b2 = int(input("Enter the second element of the second point on the triangle"))
c1 = int(input("Enter the first element of the third point on the triangle"))
c2 = int(input("Enter the second element of the third point on the triangle"))

A= np.array([a1,a2])
B= np.array([b1,b2])
C= np.array([c1,c2])

D=(B+C)/2

print(f"The mid point of B and C is {D}")

G=(A+B+C)/3

print(f"The centroid of triangleABC is {G}")

Mat = np.array([[1,1,1],[a1,D[0],G[0]],[a2,D[1],G[1]]])

rank = np.linalg.matrix_rank(Mat)

if (rank==2):
	print("Hence proved that points A,G,D in a triangle are collinear")
else:
	print("Error")



