echo "Generar grafico Hipervolumen"
python plot_hyp.py ./results/resultados_Mumford0_hyp.csv Mumford0
echo "Generar frentes de pareto"
echo "semilla 4"
python plot_frente.py ./results/resultados_Mumford0.csv ./results/resultados_Mumford0_hyp.csv Mumford0 4
echo "semilla 45"
python plot_frente.py ./results/resultados_Mumford0.csv ./results/resultados_Mumford0_hyp.csv Mumford0 45
echo "semilla 12"
python plot_frente.py ./results/resultados_Mumford0.csv ./results/resultados_Mumford0_hyp.csv Mumford0 12
echo "semilla 34"
python plot_frente.py ./results/resultados_Mumford0.csv ./results/resultados_Mumford0_hyp.csv Mumford0 34


