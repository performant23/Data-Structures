CC = gcc
CFLAGS = -Wall
EXEC_FILE=asmnt2

$(EXEC_FILE): main.o mt19937-64.o
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f *.o $(EXEC_FILE)