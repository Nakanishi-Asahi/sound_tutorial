CC := gcc

fft.png: fft.txt
	gnuplot gnu_cmd.plt

fft.txt: fft impulse_apf.raw
	./fft impulse_apf.raw wave.txt fft.txt

fft: fft.c
	$(CC) fft.c -o fft -lm -lfftw3

impulse_apf.raw: apf impulse.raw
	./apf impulse.raw impulse_apf.raw

impulse.raw: make_raw_impulse
	./make_raw_impulse impulse.raw

make_raw_impulse: make_raw_impulse.c
	$(CC) make_raw_impulse.c -o make_raw_impulse

apf: apf.c
	$(CC) apf.c -o apf -lm

clean:
	$(RM) wave.txt
	$(RM) impulse_apf.raw
	$(RM) fft
	$(RM) apf
	$(RM) fft.txt
	$(RM) wave.txt
	$(RM) fft.png
	$(RM) wave.png
	$(RM) impulse.raw
	$(RM) make_raw_impulse
