# Makefile is created by Ben
# 190n/asgn8
CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -O2 -g -I.
LFLAGS =
OBJS=bv.o field.o grass.o

all: grass

grass: $(OBJS)
	$(CC) $(LDFLAGS) -o grass $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) grass *.o

# --use-cc=clang allows it to run without GCC installed per @242 on Piazza
scan-build: clean
	scan-build --use-cc=clang make

# suggested by tutor Eric
format:
	clang-format -i -style=file *.[ch]

