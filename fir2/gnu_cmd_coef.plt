set term png size 960, 720
set output "wave_coef.png"
set xlabel "sample"
set ylabel "linear"
plot [-1:1200] [-0.2:0.2] "wave_coef.txt" w lp pointtype 6
set logscale x
set xlabel "frequency"
set ylabel "dB"
set output "fft_coef.png"
set mxtics
set grid xtics mxtics ytics
plot [10:24000] [-30:30] "fft_coef.txt" w l
