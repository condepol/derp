# Gnuplot script file for plotting data in file "force.dat"
# This file is called   force.p
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set xtic 8                          # set xtics automatically
unset ytic                         # set ytics automatically
set title "mysql <4.1 hashes, average bit status"
set xlabel "Bit number"
set ylabel "always 0                    Occurences                      always 1"
set xr [0:64]
set terminal png
unset border
plot \
"1_scaled.txt" using 1 title '1 byte'  lt 2 with points ,\
"2_scaled.txt" using 1 title '2 bytes' lt 1 with points ,\
"3_scaled.txt" using 1 title '3 bytes' lt 3 with points ,\
"4_scaled.txt" using 1 title '4 bytes' lt 4 with points
