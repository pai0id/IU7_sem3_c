#!/bin/bash

graph_dir="graphs"
mkdir -p graphs

sort_types="my q"
arr_types="sorted rand"

for arr in $arr_types; do
        gnuplot -persist <<-EOF
            set terminal svg
            set output "graph_${arr}.svg"
            set xlabel "Число элементов массива"
            set ylabel "Время выполнения, нс"
            set grid
            plot "./${graph_dir}/my_${arr}.txt" with linespoints title "mysort", \
            "./${graph_dir}/q_${arr}.txt" with linespoints title "qsort"
EOF
done

echo "DONE"

