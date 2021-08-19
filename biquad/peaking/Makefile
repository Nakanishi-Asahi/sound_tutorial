CC := gcc

fft.png: fft.txt
	gnuplot gnu_cmd.plt

fft.txt: fft impulse_peaking.raw
	./fft impulse_peaking.raw wave.txt fft.txt

fft: fft.c
	$(CC) fft.c -o fft -lm -lfftw3

impulse_peaking.raw: peaking impulse.raw
	./peaking impulse.raw impulse_peaking.raw

impulse.raw : make_raw_impulse
	./make_raw_impulse impulse.raw

make_raw_impulse : make_raw_impulse.c
	$(CC) make_raw_impulse.c -o make_raw_impulse

peaking : peaking.c
	$(CC) peaking.c -o peaking -lm

clean:
	$(RM) wave.txt
	$(RM) impulse_peaking.raw
	$(RM) fft
	$(RM) peaking
	$(RM) fft.txt
	$(RM) wave.txt
	$(RM) fft.png
	$(RM) wave.png
	$(RM) impulse.raw
	$(RM) make_raw_impulse
