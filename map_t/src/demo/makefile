CC = gcc
BASE = $(shell git rev-parse --show-toplevel)
MAIN = $(BASE)/map_t/src/main
LIST = $(BASE)/list_t/src/main
VECTOR = $(BASE)/vector_t/src/main
PERSON = $(BASE)/list_t/src/demo
UTILS = $(BASE)/utils/src
CFLAGS = -g3 -I$(MAIN) -I$(UTILS) -I$(LIST) -I$(VECTOR) -I$(PERSON) -Wall

HDRS = $(MAIN)/map.h  $(UTILS)/utils.h $(LIST)/list.h $(PERSON)/person.h map_person.h
PRSN_OBJS = $(PERSON)/person.o map_person.o
LIST_OBJS = $(LIST)/list.o $(LIST)/list_utils.o 
VECTOR_OBJS = $(VECTOR)/vector.o $(VECTOR)/vector_utils.o 
UTILS_OBJS = $(UTILS)/mem_utils.o  $(UTILS)/str_utils.o $(UTILS)/error_utils.o $(UTILS)/utils.o 
OBJS = $(MAIN)/map.o map_person.o $(PRSN_OBJS) $(LIST_OBJS) $(UTILS_OBJS) $(VECTOR_OBJS)
OUT = main

all: $(OUT)  

# main program
main: $(OBJS) $(HDRS)
info:
	@echo "\e[1m-->\e[0m Run demos: ./main"

clean: 
	rm -f $(OBJS) $(OUT) 