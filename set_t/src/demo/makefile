CC = gcc
BASE = $(shell git rev-parse --show-toplevel)
MAIN = $(BASE)/set_t/src/main
LIST = $(BASE)/list_t/src/main
VECTOR = $(BASE)/vector_t/src/main
PERSON = $(BASE)/list_t/src/demo
UTILS = $(BASE)/utils/src
CFLAGS = -g3 -I$(MAIN) -I$(UTILS) -I$(LIST) -I$(VECTOR) -I$(PERSON) -Wall

HDRS = $(MAIN)/set.h  $(UTILS)/utils.h $(LIST)/list.h $(PERSON)/person.h set_person.h
PRSN_OBJS = $(PERSON)/person.o set_person.o
LIST_OBJS = $(LIST)/list.o $(LIST)/list_utils.o $(LIST)/node.o
VECTOR_OBJS = $(VECTOR)/vector.o $(VECTOR)/vector_utils.o 
UTILS_OBJS = $(UTILS)/mem_utils.o  $(UTILS)/str_utils.o $(UTILS)/error_utils.o $(UTILS)/math_utils.o 
OBJS = $(MAIN)/set.o $(MAIN)/set_utils.o set_person.o $(PRSN_OBJS) $(LIST_OBJS) $(UTILS_OBJS) $(VECTOR_OBJS)
OUT = main eval

all: $(OUT)  

# main program
main: $(OBJS) $(HDRS)
eval: $(OBJS) $(HDRS)
info:
	@echo "\e[1m-->\e[0m Compile & run demos: ./main and ./eval"

clean: 
	rm -f $(OBJS) $(OUT) 