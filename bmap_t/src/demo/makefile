CC = gcc
BASE = $(shell git rev-parse --show-toplevel)
MAIN = $(BASE)/bmap_t/src
UTILS = $(BASE)/utils/src
CFLAGS = -g3 -Wall -I$(MAIN) -I$(UTILS)
LFLAGS = -lm

HDRS = $(MAIN)/bmap.h
OBJS = $(MAIN)/bmap.o $(UTILS)/bit_utils.o $(UTILS)/str_utils.o $(UTILS)/mem_utils.o
OUT = demo

all: $(OUT)  

# main program
demo: demo.c $(OBJS) $(HDRS)
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS) 

clean: 
	rm -f $(OBJS) $(OUT)