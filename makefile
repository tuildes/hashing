# Makefile to LBP IMAGE COMPARATION

OBJS	= src/main.o
SOURCE	= src/main.c
# HEADER	=
OUT	= myht
CC	 = gcc
FLAGS	 = -g -c -Wall -Wextra -Werror -Wpedantic -Walloc-zero -Wconversion -Wduplicated-branches -Wduplicated-cond -Wformat=2 -Wshadow
LFLAGS	 = -lm

all: hash

hash: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) $(LDFLAGS)

src/main.o: src/main.c
	$(CC) $(FLAGS) src/main.c -o src/main.o

clean:
	rm -f $(OBJS) $(OUT)

valgrind: hash
	valgrind ./hash

valgrind_leakcheck: hash
	valgrind --leak-check=full ./hash

valgrind_extreme: SNOW_IMPACT
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes ./hash
