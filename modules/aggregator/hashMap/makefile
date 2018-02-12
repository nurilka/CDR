#valgrind -v --tool=memcheck --leak-check=full --num-callers=40

#This is a makefile for HashMap

CC = gcc
CFLAGS = -ansi -pedantic -Wall -Werror
INCDIR = ../incl
#LIBDIR = ../lib/ds.a

# specific definitions
CFLAGS += -I$(INCDIR) -g
OBJS = test/test_shani.o list/list.o list/list_itr.o hashMap.o 
EXEFILE= test/hashMapTest


test/hashMapTest : $(OBJS) 
	$(CC) $(CFLAGS) -o $(EXEFILE) $(OBJS) 

include depends

depends:
	$(CC) -MM -I$(INCDIR) $(OBJS:.o=.c) > depends


clean:
	rm -f depends
	rm -f $(OBJS)
	rm -f test/*.o
	rm -f test/hashMapTest	
	
	
	
	
	

