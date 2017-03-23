import os
import numpy as np
import matplotlib.pyplot as plt

cmd = "./obj_func"
s = os.system(cmd)
sss = "./obj_func 1.2 3.4"
print "shaocong", os.popen(sss).read()

def objFunc(x,y):
	sys_cmd = cmd+' '+str(x)+' '+str(y)
	return float(os.popen(sys_cmd).read())

print objFunc(1.2,1.5)

x = y = np.arange(-20.0, 20.0, 5.0)
X, Y = np.meshgrid(x, y)
'''
zs = np.array([objFunc(x,y) for x,y in zip(np.ravel(X), np.ravel(Y))])
Z = zs.reshape(X.shape)

"""plotting"""
plt.figure()
cp = plt.contourf(X,Y,Z)
plt.colorbar(cp)
plt.show()
'''
L = -20.
R = 20.
U = 20.
B = -20.
ResX = L
ResY = U
Ans = objFunc(ResX, ResY)
ERROR = 1.E-3
C1 = 0.53
C2 = 0.47

def opti_X(y):
	l = L
	r = R
	while(r-l >= ERROR):
		x1 = l*C1 + r*C2
		x2 = l*C2 + r*C1
		z1 = objFunc(x1, y)
		z2 = objFunc(x2, y)
		if(z1 > z2):
			l = x1
		else:
			r = x2
	return l

def opti():
	b = B
	u = U
	while(u-b >= ERROR):
		y1 = b*C1 + u*C2
		y2 = b*C2 + u*C1
		z1 = objFunc(opti_X(y1),y1)
		z2 = objFunc(opti_X(y2),y2)
		if(z1 > z2):
			b = y1
		else:
			u = y2
		print u
	return opti_X(u),u,objFunc(opti_X(u),u)

ResX,ResY,Ans = opti()

print "(",ResX,",",ResY,")-> Minimal: ",Ans


a = "1.23"
b = float(a)
print b
print max(1.2 ,1.5)
