CC := gcc

fft.png: fft.txt
	gnuplot gnu_cmd.plt

fft.txt: fft impulse_hs.raw
	./fft impulse_hs.raw wave.txt fft.txt

fft: fft.c
	$(CC) fft.c -o fft -lm -lfftw3

impulse_hs.raw: hs impulse.raw
	./hs impulse.raw impulse_hs.raw

impulse.raw: make_raw_impulse
	./make_raw_impulse impulse.raw

make_raw_impulse: make_raw_impulse.c
	$(CC) make_raw_impulse.c -o make_raw_impulse

hs: hs.c
	$(CC) hs.c -o hs -lm

clean:
	$(RM) wave.txt
	$(RM) impulse_hs.raw
	$(RM) fft
	$(RM) hs
	$(RM) fft.txt
	$(RM) wave.txt
	$(RM) fft.png
	$(RM) wave.png
	$(RM) impulse.raw
	$(RM) make_raw_impulse
