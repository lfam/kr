debug=1
GCC_FLAGS = -Wall -std=c89 -DDEBUG -g3
CLANG_FLAGS = -std=c89 -DDEBUG -g -O0
ifeq ($(debug), 0)
	GCC_FLAGS = -Wall -Wextra -DNDEBUG 
	CLANG_FLAGS = -Weverything -DNDEBUG
endif

GCC = gcc $(GCC_FLAGS)
CLANG = clang $(CLANG_FLAGS)

COMPILER = $(GCC)
ifeq ($(compiler), clang)
	COMPILER = $(CLANG)
endif

CC = $(COMPILER)


ifndef ex
	ex = 1.1
endif

.PHONY: clean

all:
	$(CC) -o $(ex).o $(ex).c

clean:
	rm -f *.o
