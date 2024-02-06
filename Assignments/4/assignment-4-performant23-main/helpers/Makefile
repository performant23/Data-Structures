CC = gcc
DEBUG_FILE = testhelpers-debug
EXEC_FILE = testhelpers
INCLUDES = ../hashing/hashing.o ../hashing/hashmap.o ../helpers/helpers.o ../prng/mt19937-64.o
CURRENT = helpers.o

debug: CFLAGS = -Wall -g

debug: main.o $(CURRENT) $(INCLUDES)
	$(CC) $(CFLAGS) $^ -o $(DEBUG_FILE)

$(EXEC_FILE): CFLAGS = -Wall

$(EXEC_FILE): main.o $(CURRENT) $(INCLUDES)
	$(CC) $(CFLAGS) $^ -o $@
	rm -f $^

clean:
	rm -f *.o $(INCLUDES) $(EXEC_FILE) $(DEBUG_FILE)