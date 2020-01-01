CC = gcc
BASE = $(shell git rev-parse --show-toplevel)
MAIN = $(BASE)/utils/src
CFLAGS = -g3 -Wall -I$(MAIN)

HDRS = $(MAIN)/utils.h
MEM = $(MAIN)/mem_utils.o
STR_OBJS = $(MAIN)/str_utils.o $(MEM)
SORT_OBJS = $(MAIN)/msort.o $(MAIN)/hsort.o $(MEM)
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