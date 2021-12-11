CC = clang
CFLAGS= -Wall -Wextra -Werror -Wpedantic
OFILES = bv.o field.o
EXEC = grass

all: $(EXEC)
	$(CC) $(CFLAGS) -o $@ $^ $(OFILES)

grass.o: $(OFILES) grass.c
	$(CC) $(CFLAGS) -c grass.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

field.o: field.c
	$(CC) $(CFLAGS) -c field.c

clean:
	rm -f $(EXEC) *.o

format:
	clang-format -i -style=file *.[ch]

