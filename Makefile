debug=1
GCC_FLAGS = -Wall -std=c89 -DDEBUG -g3
CLANG_FLAGS = -Wall -std=c89 -DDEBUG -g -O0
ifeq ($(debug), 0)
	GCC_FLAGS = -Wall -std=c89 -DNDEBUG 
	CLANG_FLAGS = -Wall -std=c89 -DNDEBUG
endif

GCC = gcc
CLANG = clang

COMPILER = $(GCC)
CFLAGS = $(GCC_FLAGS)
ifeq ($(compiler), clang)
	COMPILER = $(CLANG)
	CFLAGS = $(CLANG_FLAGS)
endif

CC = $(COMPILER)

ifndef ex
	ex = 1.1
endif

.PHONY: clean all

all:
	$(CC) $(CFLAGS) -o $(ex).o $(ex).c

clean:
	rm -f *.o a.out
