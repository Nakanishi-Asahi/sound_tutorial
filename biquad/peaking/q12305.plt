set term png size 960, 720
set logscale x
set xlabel "frequency"
set ylabel "dB"
set output "fft_q12305.png"
set mxtics
set grid xtics mxtics ytics
plot [10:24000] [-10:10] "fft_q05.txt" w lp pointtype 2, "fft_q1.txt" w lp pointtype 3, "fft_q2.txt" w lp pointtype 4, "fft_q3.txt" w lp pointtype 6
