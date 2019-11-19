CC = gcc
BASE = $(shell git rev-parse --show-toplevel)
MAIN = $(BASE)/list_t/src/main
UTILS = $(BASE)/utils
CFLAGS = -g3 -Wall -I$(MAIN) -I$(UTILS)

HDRS = $(MAIN)/list.h $(UTILS)/utils.h person.h
OBJS = $(MAIN)/list.o $(MAIN)/list_utils.o $(UTILS)/mem_utils.o  $(UTILS)/str_utils.o $(UTILS)/error_utils.o person.o
OUT = main

all: $(OUT)  

# main program
main: $(OBJS) $(HDRS)

clean: 
	rm -f $(OBJS) $(OUT) 