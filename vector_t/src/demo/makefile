CC = gcc
BASE = $(shell git rev-parse --show-toplevel)/vector_t/src/main
INCLUDE = $(BASE)/include
CFLAGS = -g3 -Wall -I$(INCLUDE)
HDRS = $(INCLUDE)/vector.h $(INCLUDE)/utils.h person.h
OUT = main order info

#### pre-requisites
VECTOR = $(BASE)/vector.o $(BASE)/utils.o $(BASE)/vector_utils.o 
PERSON = $(VECTOR) person.o
####

all: $(OUT)
main: $(PERSON) $(HDRS)
order: $(PERSON) $(HDRS)
info:
	@echo "\e[1m-->\e[0m Run demos: ./main and ./order"

clean:
	rm -rf $(OUT) $(BASE)/*.o *.o