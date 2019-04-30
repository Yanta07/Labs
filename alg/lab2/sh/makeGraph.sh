#!/usr/bin/gnuplot
set terminal png size 1366,768 enhanced font 'Arial, 16'
set output 'graph/Lookup.png'

set style line 1 linecolor rgb 'red' linetype 1 linewidth 2
set style line 2 linecolor rgb 'blue' linetype 1 linewidth 2

set border linewidth 2
set key top left
set grid
set logscale y
set mytics 1
set format y "%.6f"
set xlabel "Number of elements"
set format x "%3.0f" 
set ylabel "Execution time (mSec)"
set xtics 700
set ytics 0.4
set rmargin 4
set tmargin 2
set mxtics
plot "dat/bstreeLookup.dat" using 1:2 title "bsTree Lookup" with linespoints ls 1,\
 "dat/hashtabLookup.dat" using 1:2 title "hashtab Lookup" with linespoints ls 2
