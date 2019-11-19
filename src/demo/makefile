CC = gcc
MAIN = $(shell git rev-parse --show-toplevel)/src/main
INCLUDE = $(MAIN)/include
CFLAGS = -g3 -Wall -I$(INCLUDE)

HDRS = $(INCLUDE)/define.h $(INCLUDE)/list.h
OBJS = $(MAIN)/list.o $(MAIN)/listUtils.o $(MAIN)/utils.o

all: demo $(OBJS)  

# main program
demo: $(OBJS) $(HDRS)

clean: 
	rm -f $(OBJS) demo 