import matplotlib.pyplot as plt
import matplotlib
import sys
import numpy as np

datos = {}
archivo = open(sys.argv[1])
for linea in archivo:
	linea = linea.strip()
	data = linea.split(",")
	if data[0] != "instancia":
		if data[1] == sys.argv[3]:
			if int(data[2]) not in datos:
				datos[int(data[2])]=list()
			datos[int(data[2])].append(map(float,data[10:12]))
archivo.close()


generacion = int(sys.argv[4])
plt.figure(figsize=(6,6), dpi=50)
plt.grid(True)
plt.xlabel("FO1")
plt.ylabel("FO2")

if generacion in datos:
	for x,y in datos[generacion]:
		plt.plot(x,y,marker="o",color="b")

plt.savefig("frente_"+str(sys.argv[2])+"_s"+str(sys.argv[3])+"_g"+str(sys.argv[4])+".pdf",format="pdf")

"""

i = len(semillas)-1
for semilla in semillas:
	plt.plot(datos[semilla], label=semilla, linestyle = lineas[i%3])
	i-=1


plt.legend(loc='center left', bbox_to_anchor=(1.02, 0.5))
plt.subplots_adjust(bottom=0.12,right=0.88,left=0.07,top=0.93)
plt.savefig("frente_"+str(sys.argv[2])+"_"+str(sys.argv[3])+".pdf",format="pdf")
"""
