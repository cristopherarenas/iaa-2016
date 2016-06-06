import matplotlib
import matplotlib.pyplot as plt
import numpy as np

matplotlib.rcParams.update({'font.size': 24})

f = 10
seeds = set()
Data = []
for i in range(1,10):
	archivo  = open("data/hypervolumen_alpha_"+str(f*i)+"_beta_"+str(100-f*i)+".txt")
	data = {}
	for linea in archivo:
		data[int(linea.strip().split()[0])]=(float(linea.strip().split()[1]))
		seeds.add(int(linea.strip().split()[0]))
	archivo.close()	

	Data.append(data)

i = 1
s = list(seeds)
s.sort()
#print s

for d in Data:
	print np.percentile(d.values(),75)," ",np.percentile(d.values(),25),"=",np.percentile(d.values(),75)-np.percentile(d.values(),25)

"""
for se in s:
	a = str(se) + " & "
	c = 0
	for d in Data:
		c+=1
		if c<=len(Data)-1:
			a += str(d[se]) + " & " 
		else:
			a += str(d[se]) + "\\\\"
	print a
	print "\\hline"

print "Num","data" ,"Prom", "Med", "Var", "Q3-Q1"
for d in Data:
	print i , float(sum(d.values()))/len(d), np.percentile(d.values(),50)
	i+=1
"""
#plt.title("Mandl 6:2:8")
#plt.xlabel("Combinaciones de alpha y beta")
#plt.ylabel("Hipervolumen")
#plt.boxplot(Data, 0, 'bs')
#plt.show()
