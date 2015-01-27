.PHONY: clean all

GCC = gcc
CLANG = clang
COMPILER = $(GCC)
ifeq ($(compiler), clang)
	COMPILER = $(CLANG)
endif
CC = $(COMPILER)

CFLAGS = -Wall -std=c89

OBJS = reverse.o getline.o
LIBKR = libkr

$(LIBKR): $(OBJS)
	ar Trcs $(LIBKR).a $(OBJS) 

%.o: %.c $(LIBKR).h
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.a
