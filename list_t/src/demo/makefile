CC = gcc
MAIN = $(shell git rev-parse --show-toplevel)/list_t/src/main
INCLUDE = $(MAIN)/include
CFLAGS = -g3 -Wall -I$(INCLUDE)

HDRS = $(INCLUDE)/define.h $(INCLUDE)/list.h person.h
OBJS = $(MAIN)/list.o $(MAIN)/listUtils.o $(MAIN)/utils.o person.o
OUT = main

all: $(OUT)  

# main program
main: $(OBJS) $(HDRS)

clean: 
	rm -f $(OBJS) $(OUT) 