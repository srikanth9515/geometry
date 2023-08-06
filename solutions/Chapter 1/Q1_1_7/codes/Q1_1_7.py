import numpy as np
A=np.array([[1],[-1]])
B=np.array([[-4],[6]])
C=np.array([[-3],[-5]])

dotA=((B-A).T)@(C-A)
dotA=dotA[0,0]
NormA=(np.linalg.norm(B-A))*(np.linalg.norm(C-A))
print('value of angle A: ', np.degrees(np.arccos((dotA)/NormA)))


dotB=(A-B).T@(C-B)
dotB=dotB[0,0]
NormB=(np.linalg.norm(A-B))*(np.linalg.norm(C-B))
print('value of angle B: ', np.degrees(np.arccos((dotB)/NormB)))

dotC=(A-C).T@(B-C)
dotC=dotC[0,0]
NormC=(np.linalg.norm(A-C))*(np.linalg.norm(B-C))
print('value of angle C: ', np.degrees(np.arccos((dotC)/NormC)))
