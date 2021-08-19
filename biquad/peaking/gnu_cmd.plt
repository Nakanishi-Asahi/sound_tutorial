set term png size 960, 720
set output "wave.png"
set xlabel "sample"
set ylabel "linear"
plot [-1:2000] [-1.5:1.5] "wave.txt" w lp pointtype 6
set logscale x
set xlabel "frequency"
set ylabel "dB"
set output "fft.png"
set mxtics
set grid xtics mxtics ytics
plot [10:24000] [-10:10] "fft.txt" w l
