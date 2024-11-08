CC=gcc
WA=-Werror -Wpedantic -Wextra
OUT=-g -o main.o
IN=sort.c main.c
RUN=./main.o

main.o: main.c sort.c
	$(CC) $(IN) $(OUT)
run:
	$(RUN)
clean:
	rm *.o
