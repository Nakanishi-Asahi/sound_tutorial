CC:= gcc

fft.png: fft.txt
	gnuplot gnu_cmd.plt

fft.txt: fft impulse_notch.raw
	./fft impulse_notch.raw wave.txt fft.txt

fft: fft.c
	$(CC) fft.c -o fft -lm -lfftw3

impulse_notch.raw: notch impulse.raw
	./notch impulse.raw impulse_notch.raw

impulse.raw: make_raw_impulse
	./make_raw_impulse impulse.raw

make_raw_impulse: make_raw_impulse.c
	$(CC) make_raw_impulse.c -o make_raw_impulse

notch: notch.c
	$(CC) notch.c -o notch -lm

clean:
	$(RM) wave.txt
	$(RM) impulse_notch.raw
	$(RM) fft
	$(RM) notch
	$(RM) fft.txt
	$(RM) wave.txt
	$(RM) fft.png
	$(RM) wave.png
	$(RM) impulse.raw
	$(RM) make_raw_impulse
