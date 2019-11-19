CC = gcc
BASE = $(shell git rev-parse --show-toplevel)
MAIN = $(BASE)/vector_t/src/main
UTILS = $(BASE)/utils
CFLAGS = -g3 -Wall -I$(UTILS) -I$(MAIN)
HDRS = $(MAIN)/vector.h $(UTILS)/utils.h person.h
OUT = main order info

#### pre-requisites
VECTOR = $(MAIN)/vector.o $(UTILS)/mem_utils.o $(MAIN)/vector_utils.o 
PERSON = $(VECTOR) person.o
####

all: $(OUT)
main: $(PERSON) $(HDRS)
order: $(PERSON) $(HDRS)
info:
	@echo "\e[1m-->\e[0m Run demos: ./main and ./order"

clean:
	rm -rf $(OUT) $(MAIN)/*.o *.o