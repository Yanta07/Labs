set terminal pdf
set output "graph.pdf"
set xlabel "Количество элементов в массиве *10^3"
set ylabel "Время сортировки, с"
set logscale y 10
plot "sort.dat" using 1:2 with lines title "CountingSort", "sort.dat" using 1:3 with lines title "BubbleSort", "sort.dat" using 1:4 with lines title "HeapSort"