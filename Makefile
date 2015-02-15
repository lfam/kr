.PHONY: clean all

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

ex ?= 1.1

LIBDIR = lib/
LIBNAME = kr
LIBC = $(LIBDIR)reverse.c $(LIBDIR)getline.c
LIB = $(LIBDIR)libkr.a
LIBH = $(LIB:a=h)

all: $(LIB)
	$(CC) $(CFLAGS) -o $(ex).o $(ex).c -L$(LIBDIR) -l$(LIBNAME) -I$(LIBDIR) -lm

$(LIB): $(LIBC) $(LIBH)
	cd $(LIBDIR); make;

clean:
	rm -f *.o a.out
	cd $(LIBDIR); make clean;
