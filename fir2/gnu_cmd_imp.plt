set term png size 960, 720
set output "wave_imp.png"
set xlabel "sample"
set ylabel "linear"
plot [-1:1200] [-0.2:0.2] "wave_imp.txt" w lp pointtype 6
set logscale x
set xlabel "frequency"
set ylabel "dB"
set output "fft_imp.png"
set mxtics
set grid xtics mxtics ytics
plot [10:24000] [-30:30] "fft_imp.txt" w l
