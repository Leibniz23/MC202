CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: matrioscas

matrioscas: matrioscas.o func5.o
	gcc $(CFLAGS) matrioscas.o func5.o -o matrioscas $(LDFLAGS)

matrioscas.o: matrioscas.c func5.h
	gcc $(CFLAGS) -c matrioscas.c $(LDFLAGS)

func5.o: func5.c func5.h
	gcc $(CFLAGS) -c func5.c $(LDFLAGS)

clean:
	rm -f matrioscas
