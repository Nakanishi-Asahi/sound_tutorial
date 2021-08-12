CC := gcc

ifft.txt : mul2raw_ifft fft_imp.raw fft_coef.raw
	./mul2raw_ifft fft_coef.raw fft_imp.raw ifft.txt

mul2raw_ifft : mul2raw_ifft.c
	$(CC) mul2raw_ifft.c -o mul2raw_ifft -lfftw3 -lm

wave_imp.png fft_imp.png : wave_imp.txt fft_imp.txt
	gnuplot gnu_cmd_imp.plt

wave_imp.txt fft_imp.txt fft_imp.raw : fft impulse.raw
	./fft impulse.raw wave_imp.txt fft_imp.txt fft_imp.raw

impulse.raw : make_raw_impulse
	./make_raw_impulse impulse.raw

make_raw_impulse : make_raw_impulse.c
	$(CC) make_raw_impulse.c -o make_raw_impulse

wave_coef.png fft_coef.png : wave_coef.txt fft_coef.txt
	gnuplot gnu_cmd_coef.plt

wave_coef.txt fft_coef.txt fft_coef.raw : fft coef.raw
	./fft coef.raw wave_coef.txt fft_coef.txt fft_coef.raw

fft : fft.c
	$(CC) fft.c -o fft -lm -lfftw3

coef.raw : lpf_coef
	./lpf_coef coef.raw

lpf_coef : lpf_coef.c
	$(CC) lpf_coef.c -o lpf_coef -lm

clean :
	$(RM) coef.png
	$(RM) coef.txt
	$(RM) lpf_coef
	$(RM) *.raw
	$(RM) fft
	$(RM) mul2raw_ifft
	$(RM) *.txt
	$(RM) wave.png
	$(RM) fft.png
	$(RM) make_raw_impulse
