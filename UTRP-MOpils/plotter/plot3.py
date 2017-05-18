#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import matplotlib.pyplot as plt

if len(sys.argv)!=2:
	print "Ingrese un parametro"
else:
	try:
		puntos = []
		for i in range(10,100,10):
			archivo = open(sys.argv[1]+"hypervolumen_alpha_"+str(i)+"_beta_"+str(100-i)+".txt")
			datos = []
			for linea in archivo:
				datos.append(linea.strip())
			archivo.close()
			puntos.append(datos)
		
		plt.grid(True)
		plt.title(u'Gráfico comparativo del hipervolumen para la instancia Mumford0')
		plt.xlabel('Iteraciones')
		plt.ylabel('Hipervolumen')
		colors = ['b','g','r','0.5','0.6','c','m','y','k','0.90','0.75','0.45']

		plot1, = plt.plot(puntos[0],'-',c=colors[0],lw=2.0)
		plot2, = plt.plot(puntos[1],'-',c=colors[1],lw=2.0)
		plot3, = plt.plot(puntos[2],'-',c=colors[2],lw=2.0)
		plot4, = plt.plot(puntos[3],'-',c=colors[3],lw=2.0)
		plot5, = plt.plot(puntos[4],'-',c=colors[4],lw=2.0)
		plot6, = plt.plot(puntos[5],'-',c=colors[5],lw=2.0)
		plot7, = plt.plot(puntos[6],'-',c=colors[6],lw=2.0)
		plot8, = plt.plot(puntos[7],'-',c=colors[7],lw=2.0)
		plot9, = plt.plot(puntos[8],'-',c=colors[8],lw=2.0)
		
		plt.legend(	[plot1,plot2,plot3,plot4,plot5,plot6,plot7,plot8,plot9],
					["alpha: 10 beta: 90","alpha: 20 beta: 80","alpha: 30 beta: 70","alpha: 40 beta: 60","alpha: 50 beta: 50","alpha: 60 beta: 40","alpha: 70 beta: 30","alpha: 80 beta: 20","alpha: 90 beta: 10"],
					loc = 'best')
		plt.show()
		
		
	except:
		print "ERROR: ",sys.argv[1], "no existe"
		exit(1) 
