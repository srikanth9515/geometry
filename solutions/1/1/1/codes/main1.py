import numpy 

A = numpy.array([1,-1])
B = numpy.array([-4,6])
C = numpy.array([-3,-5])

d = B- A
e = C - B
f = A - C

print("The direction vector of AB is ",d)
print("The direction vector of BC is ",e)
print("The direction vector of CA is ",f)


