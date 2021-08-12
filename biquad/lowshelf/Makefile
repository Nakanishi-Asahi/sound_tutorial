CC := gcc

fft.png: fft.txt
	gnuplot gnu_cmd.plt

fft.txt: fft impulse_ls.raw
	./fft impulse_ls.raw wave.txt fft.txt

fft: fft.c
	$(CC) fft.c -o fft -lm -lfftw3

impulse_ls.raw: ls impulse.raw
	./ls impulse.raw impulse_ls.raw

impulse.raw: make_raw_impulse
	./make_raw_impulse impulse.raw

make_raw_impulse: make_raw_impulse.c
	$(CC) make_raw_impulse.c -o make_raw_impulse

ls: ls.c
	$(CC) ls.c -o ls -lm

clean:
	$(RM) wave.txt
	$(RM) impulse_ls.raw
	$(RM) fft
	$(RM) ls
	$(RM) fft.txt
	$(RM) wave.txt
	$(RM) fft.png
	$(RM) wave.png
	$(RM) impulse.raw
	$(RM) make_raw_impulse
