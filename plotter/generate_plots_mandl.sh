echo "Generar grafico Hipervolumen"
python plot_hyp.py ./results/resultados_Mandl_hyp.csv Mandl
echo "Generar frentes de pareto"
echo "semilla 4"
python plot_frente.py ./results/resultados_Mandl.csv ./results/resultados_Mandl_hyp.csv Mandl 4
echo "semilla 45"
python plot_frente.py ./results/resultados_Mandl.csv ./results/resultados_Mandl_hyp.csv Mandl 45
echo "semilla 12"
python plot_frente.py ./results/resultados_Mandl.csv ./results/resultados_Mandl_hyp.csv Mandl 12
echo "semilla 34"
python plot_frente.py ./results/resultados_Mandl.csv ./results/resultados_Mandl_hyp.csv Mandl 34


