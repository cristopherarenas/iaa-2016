#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import matplotlib
import sys
import numpy as np

datos = {}
arch2 = open("frente_"+str(sys.argv[3])+".txt","a")
archivo = open(sys.argv[1])
for linea in archivo:
	linea = linea.strip()
	data = linea.split(",")
	if data[0] != "instancia":
		if data[1] == sys.argv[4]:
			if int(data[2]) not in datos:
				datos[int(data[2])]=list()
			datos[int(data[2])].append(tuple(map(float,[data[10],data[11]])))
archivo.close()

hyper = {}
time = {}

arch3 = open(sys.argv[2])
for li in arch3:
	li = li.strip()
	data2 = li.split(",")
	#print data2
	if data2[0] != "instancia":
		if data2[1] == sys.argv[4]:
			hyper[int(data2[2])] = float(data2[10])
			time[int(data2[2])] = float(data2[11])
arch3.close()

#print "hyper",hyper
#print "time",time

generacion = [1,50,100,1000]
plt.figure(figsize=(6,6), dpi=50)
plt.grid(True)
plt.xlabel(r"Costo del Pasajero $FO_1$ [min]")
plt.ylabel(r"Costo del Operador $FO_2$ [min]")

l = "{0} & {1} & {2} & {3} & {4} \\\\ \n"

col = ["b","r","g","c"]
mar = ["d","s","o","p"]
sizes = [15,14,12,10]

i=0
for g in generacion:
	if g in datos:
		arch2.write(l.format(str(sys.argv[4]),str(g),str(len(set(datos[g])))+" ("+str(len(datos[g]))+")",str(hyper[g]),str(time[g])))
		X = []
		Y = []
		for x,y in datos[g]:
			X.append(x)
			Y.append(y)
			
		plt.plot(X,Y,ls="",marker=mar[i],color=col[i],ms=sizes[i],label=u"Generación "+str(g))
		i+=1

plt.legend(loc="best",numpoints=1)
plt.title(u"Frente de Pareto: "+ str(sys.argv[3]) +" - Semilla "+str(sys.argv[4]))
plt.savefig("frente_"+str(sys.argv[3])+"_s"+str(sys.argv[4])+".pdf",format="pdf")
arch2.close()
"""

i = len(semillas)-1
for semilla in semillas:
	plt.plot(datos[semilla], label=semilla, linestyle = lineas[i%3])
	i-=1


plt.legend(loc='center left', bbox_to_anchor=(1.02, 0.5))
plt.subplots_adjust(bottom=0.12,right=0.88,left=0.07,top=0.93)
plt.savefig("frente_"+str(sys.argv[2])+"_"+str(sys.argv[3])+".pdf",format="pdf")
"""
