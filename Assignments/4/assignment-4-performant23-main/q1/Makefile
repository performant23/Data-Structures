CC = gcc
CFLAGS = -Wall
EXEC_FILE=asmnt4

$(EXEC_FILE): main.o q1a.o q1b.o ../prng/mt19937-64.o ../helpers/helpers.o
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f *.o $(EXEC_FILE)