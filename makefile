COMPILER = gcc
FLAGS = -Wall -O3 -mtune=native

LIB = -lgsl -lgslcblas -lm

rps:
	@${COMPILER} ${FLAGS} src/rps.c src/ic.c src/op.c -static ${LIB} -o rps.out

clean:
	@rm -f rps.out
	@rm -f dat/*.dat

clean-fig:
	@rm -f plt/*.png
	@rm -f plt/*.pdf
	@rm -f plt/*.mp4
