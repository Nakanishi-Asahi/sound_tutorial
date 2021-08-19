CC := gcc

fft.png: fft.txt
	gnuplot gnu_cmd.plt

fft.txt: fft impulse_process.raw
	./fft impulse_process.raw wave.txt fft.txt

fft: fft.c
	$(CC) fft.c -o fft -lm -lfftw3

impulse_process.raw : process impulse.raw
	./process impulse.raw impulse_process.raw

impulse.raw: make_raw_impulse
	./make_raw_impulse impulse.raw

make_raw_impulse: make_raw_impulse.c
	$(CC) make_raw_impulse.c -o make_raw_impulse

process : process.c
	$(CC) process.c -o process -lm

clean:
	$(RM) wave.txt
	$(RM) impulse_process.raw
	$(RM) fft
	$(RM) process
	$(RM) fft.txt
	$(RM) wave.txt
	$(RM) fft.png
	$(RM) wave.png
	$(RM) impulse.raw
	$(RM) make_raw_impulse
