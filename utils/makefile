CC = gcc
BASE = $(shell git rev-parse --show-toplevel)
MAIN = $(BASE)/utils/src
HEAP = $(BASE)/heap_t/src/main
VECTOR = $(BASE)/vector_t/src/main
CFLAGS = -g3 -Wall -I$(MAIN) -I$(HEAP) -I$(VECTOR)

HDRS = $(MAIN)/utils.h
MEM = $(MAIN)/mem_utils.o
STR_OBJS = $(MAIN)/str_utils.o $(MEM)
VECTOR_OBJS = $(VECTOR)/vector.o $(VECTOR)/vector_utils.o
SORT_OBJS = $(HEAP)/heap_utils.o $(HEAP)/heap.o $(MEM) $(MAIN)/msort.o $(VECTOR_OBJS)
MATH_OBJS = $(MAIN)/math_utils.o
OBJS = $(STR_OBJS) $(MATH_OBJS) $(MEM) $(SORT_OBJS)
OUT = str_demo math_demo sort_demo

all: $(OUT)  

# main program
str_demo: $(STR_OBJS) $(HDRS)
sort_demo: $(SORT_OBJS) $(HDRS)
math_demo: $(MATH_OBJS) $(HDRS)

clean: 
	rm -f $(OBJS) $(OUT)
