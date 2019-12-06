CC = gcc
BASE = $(shell git rev-parse --show-toplevel)
MAIN = $(BASE)/matrix_t/src/main
UTILS = $(BASE)/utils/src
CFLAGS = -g3 -Wall -I$(MAIN) -I$(UTILS)
HDRS = $(MAIN)/matrix.h $(UTILS)/utils.h
OBJS = $(MAIN)/matrix.o $(UTILS)/mem_utils.o $(UTILS)/math_utils.o
OUT = main

all: $(OUT)  

# main program
main: $(OBJS) $(HDRS)

clean: 
	rm -f $(OBJS) $(OUT) 