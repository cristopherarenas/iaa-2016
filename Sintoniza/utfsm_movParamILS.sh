#
# Este archivo debe llamarse nombre_algoritmovParamILS.sh
#
#!/bin/bash

#bench=$1
seed=$5

#input_file = ARGV[0]
#instance_specifics = ARGV[1]
#timeout = ARGV[2].to_i
#cutoff_length = ARGV[3].to_i
#seed = ARGV[4].to_i

shift 5

while [ $# != 0 ]; do
    flag="$1"
    case "$flag" in
        -mejores) if [ $# -gt 1 ]; then
              arg="$2"
              shift
	      mejores=$arg
            fi
            ;;
        -clones) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              clones=$arg
            fi
            ;;
        -reemplazo) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              reemplazo=$arg
            fi
            ;;
        -popsize) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              popsize=$arg
            fi
            ;;
        -clonsize) if [ $# -gt 1 ]; then
              arg="$2"
              shift
              clonsize=$arg
            fi
            ;;
        *) echo "Unrecognized flag or argument: $flag"
            ;;
        esac
    shift
done

#tries=1
#tours=100 -s ${tours}
#nnants=10 -g ${nnants}
#ttime=5
start=`date +%s`
outfile=data/data_${start}.dat
#crea carpeta data/ donde almacena los outputs de todas las corridas que ejecute ParamsILS (a modo de respaldo)
#echo "./utrpmo -i instances/Mandl -s ${seed} -r "6:2:8" -p ${popsize} -c ${clonsize} -g 250 -a ${clones} -b ${reemplazo} -d ${mejores} -f 101 > ${outfile}"
#./utrpmo -i instances/Mandl -s ${seed} -r "6:2:8" -p ${popsize} -c ${clonsize} -g 250 -a ${clones} -b ${reemplazo} -d ${mejores} -f 101 > ${outfile}
echo "./utrpmo -i instances/Mumford0 -s ${seed} -r "12:2:15" -p ${popsize} -c ${clonsize} -g 250 -a ${clones} -b ${reemplazo} -d ${mejores} -f 101 > ${outfile}"
./utrpmo -i instances/Mumford0 -s ${seed} -r "12:2:15" -p ${popsize} -c ${clonsize} -g 250 -a ${clones} -b ${reemplazo} -d ${mejores} -f 101 > ${outfile}
end=`date +%s`

solved="SAT"
runlength=`cat ${outfile}`
runtime=0
best_sol=0

echo "Result for ParamILS: ${solved}, ${runtime}, ${runlength}, ${best_sol}, ${seed}"
