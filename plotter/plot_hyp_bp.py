import matplotlib.pyplot as plt
import matplotlib as mpl
import sys
import numpy as np

mpl.rcParams['font.size'] = 20
mpl.rcParams['axes.labelsize'] = 20
mpl.rcParams['xtick.labelsize'] = 20
mpl.rcParams['ytick.labelsize'] = 20


#print("This is the name of the script: ", sys.argv[0])
#print("Number of arguments: ", len(sys.argv))
#print("The arguments are: " , str(sys.argv))

datos = {}
generacion = [1,50,100,1000]
archivo = open(sys.argv[1])
for linea in archivo:
	linea = linea.strip()
	data = linea.split(",")
	if data[0] != "instancia" and int(data[2]) in generacion:
		if int(data[2]) not in datos:
			datos[int(data[2])]=list()
		datos[int(data[2])].append(float(data[10]))
archivo.close()

semillas = datos.keys()
semillas.sort()
#generar grafico

l = []
for g in generacion:
	l.append(datos[g])

fig = plt.figure(1, figsize=(9, 6))



fig = plt.figure(figsize=(11,7), dpi=50)
ax = fig.add_subplot(111)

bp = ax.boxplot(l)

for out in bp['fliers']:
    out.set(marker='x', color="k", ms=20.0)


plt.ylabel("Hipervolumen")
plt.xlabel("Generaciones")
plt.grid(True)
ax.set_xticklabels(map(str,generacion))
fig.savefig("hyp_"+str(sys.argv[2])+"_bp.pdf",format="pdf")

"""
i = len(semillas)-1


plt.grid(True)
plt.xlabel("Generaciones")
plt.ylabel("Hipervolumen")
plt.legend(loc='center left', bbox_to_anchor=(1.02, 0.5))
plt.subplots_adjust(bottom=0.12,right=0.80,left=0.10,top=0.93)
plt.savefig("hyp_"+str(sys.argv[2])+".pdf",format="pdf")
"""
