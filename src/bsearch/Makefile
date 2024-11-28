CFLAGS+=-Wall -Wextra -std=c11 -pedantic -g

objects = bsearch main \

all: $(objects)

build:
	cc $(CFLAGS) bsearch.c main.c -o main

run:
	./main

clean:
	$(RM) $(objects)
	$(RM) vgcore.*
