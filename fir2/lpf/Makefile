CC := gcc

wave.png fft.png : wave.txt fft.txt
	gnuplot gnu_cmd.plt

wave.txt fft.txt : fft impulse_lpf.raw
	./fft impulse_lpf.raw wave.txt fft.txt

fft : fft.c
	$(CC) fft.c -o fft -lm -lfftw3

impulse_lpf.raw : lpf impulse.raw
	./lpf impulse.raw impulse_lpf.raw

lpf : lpf.c
	$(CC) lpf.c -o lpf -lm -lfftw3

impulse.raw : make_raw_impulse
	./make_raw_impulse impulse.raw

make_raw_impulse : make_raw_impulse.c
	$(CC) make_raw_impulse.c -o make_raw_impulse

clean :
	$(RM) wave.png
	$(RM) fft.png
	$(RM) wave.txt
	$(RM) fft.txt
	$(RM) fft
	$(RM) impulse_lpf.raw
	$(RM) lpf
	$(RM) impulse.raw
	$(RM) make_raw_impulse
