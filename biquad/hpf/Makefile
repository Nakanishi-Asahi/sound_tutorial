CC := gcc

fft.png: fft.txt
	gnuplot gnu_cmd.plt

fft.txt: fft impulse_hpf.raw
	./fft impulse_hpf.raw wave.txt fft.txt

fft: fft.c
	$(CC) fft.c -o fft -lm -lfftw3

impulse_hpf.raw: hpf impulse.raw
	./hpf impulse.raw impulse_hpf.raw

impulse.raw: make_raw_impulse
	./make_raw_impulse impulse.raw

make_raw_impulse: make_raw_impulse.c
	$(CC) make_raw_impulse.c -o make_raw_impulse

hpf: hpf.c
	$(CC) hpf.c -o hpf -lm

clean:
	$(RM) wave.txt
	$(RM) impulse_hpf.raw
	$(RM) fft
	$(RM) hpf
	$(RM) fft.txt
	$(RM) wave.txt
	$(RM) fft.png
	$(RM) wave.png
	$(RM) impulse.raw
	$(RM) make_raw_impulse
