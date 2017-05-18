import sys
import matplotlib.pyplot as plt

if len(sys.argv)!=2:
	print "Ingrese un parametro"
else:
	try:
		puntos = []
		archivo = open(sys.argv[1])
		for linea in archivo:
			puntos.append(linea.strip())
		
		archivo.close()
		plt.plot(puntos)
		plt.xlabel("Iteraciones")
		plt.ylabel("Hipervolumen")
		plt.grid()
		plt.show()
		
		
	except:
		print "ERROR: ",sys.argv[1], "no existe"
		exit(1) 
