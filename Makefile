all: mbp-fn-flip

mbp-fn-flip: mbp-fn-flip.o
	gcc -o mbp-fn-flip mbp-fn-flip.o

clean:
	rm -f *.o mbp-fn-flip

install: mbp-fn-flip
	install -g root -o root -m 4755 ./mbp-fn-flip /usr/local/bin/mbp-fn-flip
