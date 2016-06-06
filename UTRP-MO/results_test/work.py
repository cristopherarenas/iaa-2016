archivo = open("1_pareto2_2000_alpha_10_beta_90.txt")
archivo2 = open("1_pareto3_2000_alpha_10_beta_90.txt","w")
contador = 0
for linea in archivo:
	if contador%7==0:
		archivo2.write(linea)
	contador+=1
archivo.close()
archivo2.close()
