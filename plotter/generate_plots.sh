echo "Generar grafico Hipervolumen"
python plot_hyp.py ./results/resultados_Mandl_hyp.csv Mandl
echo "Generar frentes de pareto"
echo "semilla 1"
echo "Generacion 1"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 1 1
echo "Generacion 250"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 1 250
echo "Generacion 500"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 1 500
echo "Generacion 750"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 1 750
echo "Generacion 1000"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 1 1000
echo "semilla 2"
echo "Generacion 1"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 2 1
echo "Generacion 250"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 2 250
echo "Generacion 500"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 2 500
echo "Generacion 750"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 2 750
echo "Generacion 1000"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 2 1000
echo "semilla 3"
echo "Generacion 1"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 3 1
echo "Generacion 250"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 3 250
echo "Generacion 500"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 3 500
echo "Generacion 750"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 3 750
echo "Generacion 1000"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 3 1000
echo "semilla 4"
echo "Generacion 1"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 4 1
echo "Generacion 250"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 4 250
echo "Generacion 500"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 4 500
echo "Generacion 750"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 4 750
echo "Generacion 1000"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 4 1000
echo "semilla 5"
echo "Generacion 1"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 5 1
echo "Generacion 250"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 5 250
echo "Generacion 500"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 5 500
echo "Generacion 750"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 5 750
echo "Generacion 1000"
python plot_frente.py ./results/resultados_Mandl.csv Mandl 5 1000

