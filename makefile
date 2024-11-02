# Makefile to LBP IMAGE COMPARATION

OBJS	= src/myht.o src/hash.o
SOURCE	= src/myht.c src/hash.c
HEADER	= src/hash.h
OUT	= myht
CC	 = gcc
FLAGS	 = -g -c -Wall -Wextra -Werror -Wpedantic -Walloc-zero -Wconversion -Wduplicated-branches -Wduplicated-cond -Wformat=2 -Wshadow
LFLAGS	 = -lm

all: hash

hash: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) $(LDFLAGS)

src/myht.o: src/myht.c
	$(CC) $(FLAGS) src/myht.c -o src/myht.o

src/hash.o: src/hash.c
	$(CC) $(FLAGS) src/hash.c -o src/hash.o

clean:
	rm -f $(OBJS) $(OUT)

valgrind: hash
	valgrind ./hash

valgrind_leakcheck: hash
	valgrind --leak-check=full ./hash

valgrind_extreme: SNOW_IMPACT
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes ./hash
