CC = gcc
INCLUDE = include
CFLAGS = -g3 -Wall -I$(INCLUDE)

HDRS = $(INCLUDE)/define.h $(INCLUDE)/list.h
SRCS = list.c listUtils.c utils.c
OBJS = $(SRCS:.c=.o) # OBJS are same as sources but with a .o extension

all: demo $(OBJS)  

# main program
demo: demo.c $(OBJS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ $< $(SRCS)

# data structures and utilities	
list.o: $(HDRS)
listUtils.o: $(HDRS)
utils.o: $(INCLUDE)/utils.h

clean: 
	rm -f $(OBJS) demo 