CC = gcc
BASE = $(shell git rev-parse --show-toplevel)
MAIN = $(BASE)/utils/src
CFLAGS = -g3 -Wall -I$(MAIN)

HDRS = $(MAIN)/utils.h
OBJS = $(MAIN)/str_utils.o $(MAIN)/mem_utils.o
OUT = demo

all: $(OUT)  

# main program
demo: $(OBJS) $(HDRS)

clean: 
	rm -f $(OBJS) $(OUT)