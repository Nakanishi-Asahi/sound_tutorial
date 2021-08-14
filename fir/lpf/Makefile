CC := gcc

wave.png fft.png : fft.txt
	gnuplot gnu_cmd.plt

wave.txt fft.txt: fft impulse_lpf.raw
	./fft impulse_lpf.raw wave.txt fft.txt

fft: fft.c
	$(CC) fft.c -o fft -lm -lfftw3

impulse_lpf.raw: lpf impulse.raw
	./lpf impulse.raw impulse_lpf.raw

impulse.raw: make_raw_impulse
	./make_raw_impulse impulse.raw

make_raw_impulse: make_raw_impulse.c
	$(CC) make_raw_impulse.c -o make_raw_impulse

lpf: lpf.c
	$(CC) lpf.c -o lpf -lm

read_raw : read_raw.c
	$(CC) read_raw.c -o read_raw

clean:
	$(RM) wave.txt
	$(RM) impulse_lpf.raw
	$(RM) fft
	$(RM) lpf
	$(RM) fft.txt
	$(RM) wave.txt
	$(RM) fft.png
	$(RM) wave.png
	$(RM) impulse.raw
	$(RM) make_raw_impulse
	$(RM) read_raw
