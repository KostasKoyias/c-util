CC = gcc
BASE = $(shell git rev-parse --show-toplevel)
MAIN = $(BASE)/list_t/src/main
UTILS = $(BASE)/utils/src
CFLAGS = -g3 -Wall -I$(MAIN) -I$(UTILS)

HDRS = $(MAIN)/list.h $(UTILS)/utils.h person.h
LIST_OBJS = $(MAIN)/list.o $(MAIN)/list_utils.o $(MAIN)/node.o
OBJS = $(LIST_OBJS) $(UTILS)/mem_utils.o $(UTILS)/str_utils.o $(UTILS)/error_utils.o person.o
OUT = main order

all: $(OUT)  

# main program
main: $(OBJS) $(HDRS)
order: $(OBJS) $(HDRS)

clean: 
	rm -f $(OBJS) $(OUT) 