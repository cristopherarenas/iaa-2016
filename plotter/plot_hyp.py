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
archivo = open(sys.argv[1])
for linea in archivo:
	linea = linea.strip()
	data = linea.split(",")
	if data[0] != "instancia":
		if int(data[1]) not in datos:
			datos[int(data[1])]=list()
		datos[int(data[1])].append(float(data[10].replace('"','')))
archivo.close()

semillas = datos.keys()
semillas.sort()
#generar grafico

colores = np.linspace(0.3,0.6,len(semillas))
colores = map(str,colores)
lineas = ["-.","--","-"]

plt.figure(figsize=(12,9), dpi=50)
i = len(semillas)-1

for semilla in semillas:
	plt.plot(datos[semilla], label=semilla, linestyle = lineas[i%3],lw=2.0)
	i-=1

plt.grid(True)
plt.xlabel("Generaciones")
plt.ylabel("Hipervolumen")
plt.legend(loc='center left', bbox_to_anchor=(1.02, 0.5))
plt.subplots_adjust(bottom=0.12,right=0.80,left=0.10,top=0.93)
plt.savefig("hyp_"+str(sys.argv[2])+".pdf",format="pdf")
