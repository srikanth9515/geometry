import numpy as np
A=np.array([1,-1])
B=np.array([-4,6])
C=np.array([-3,-5])

m1=(B-A)
m2=(C-B)
m3=(A-C)
print("parametric of AB form is x:",A,"+ k",m1)
print("parametric of BC form is x:",B,"+ k",m2)
print("parametric of CA form is x:",C,"+ k",m3)
