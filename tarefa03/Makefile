CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: rainhas

rainhas: rainhas.o func3.o
	gcc $(CFLAGS) rainhas.o func3.o $(LDFLAGS) -o rainhas

rainhas.o: rainhas.c func3.h
	gcc $(CFLAGS) -c rainhas.c

func3.o: func3.c func3.h
	gcc $(CFLAGS) -c func3.c

clean:
	rm -f rainhas