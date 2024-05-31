CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: caminho

caminho: func9.o caminho.o
	gcc $(CFLAGS) caminho.o func9.o -o caminho $(LDFLAGS)

caminho.o: caminho.c func9.h
	gcc $(CFLAGS) -c caminho.c $(LDFLAGS)

func9.o: func9.c func9.h
	gcc $(CFLAGS) -c func9.c $(LDFLAGS)

clean:
	rm -f caminho
	rm -f caminho.o
	rm -f func9.o
