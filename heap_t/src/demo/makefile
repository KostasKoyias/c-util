CC = gcc
BASE = $(shell git rev-parse --show-toplevel)
MAIN = $(BASE)/heap_t/src/main
VECTOR = $(BASE)/vector_t/src/main
UTILS = $(BASE)/utils/src
INCLUDE = -I$(MAIN) -I$(UTILS) -I$(VECTOR) 
CFLAGS = -g3 -Wall $(INCLUDE)

HDRS = $(UTILS)/utils.h $(MAIN)/heap.h integer.h
MEM = $(UTILS)/mem_utils.o
HEAP = $(MAIN)/heap.o $(MAIN)/heap_utils.o $(MEM)
VECTOR_OBJS = $(VECTOR)/vector.o $(VECTOR)/vector_utils.o
OBJS = $(HEAP) $(MEM) $(VECTOR_OBJS) integer.o
OUT = demo sort

all: $(OUT)  

# main program
sort: $(OBJS) $(HDRS)
demo: $(OBJS) $(HDRS)

clean: 
	rm -f $(OBJS) $(OUT)