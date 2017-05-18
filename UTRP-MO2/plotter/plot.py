import sys
import matplotlib.pyplot as plt

if len(sys.argv)!=2:
	print "Ingrese un parametro"
else:
	try:
		puntos_x = []
		puntos_y = [] 
		archivo = open(sys.argv[1])
		for linea in archivo:
			linea = linea.strip()
			data = linea.split()
			puntos_x.append(data[0])
			puntos_y.append(data[1])
		
		archivo.close()
		for i in range(len(puntos_x)):
			plt.plot(puntos_x[i],puntos_y[i],'o',c='b')
		
		plt.grid()
		plt.xlabel("fo1")
		plt.ylabel("fo2")
		plt.show()
		
	except:
		print "ERROR: ",sys.argv[1], "no existe"
		exit(1) 
