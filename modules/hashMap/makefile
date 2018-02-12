#valgrind -v --tool=memcheck --leak-check=full --num-callers=40
.PHONY: clean 
#This is a makefile for HashMap

CC = gcc
CFLAGS = -ansi -pedantic -Wall -Werror
INCDIR = ../../inc
ARCHLIB= ../../archLib

# specific definitions
CFLAGS += -I$(INCDIR) -g
OBJS = list/list.o list/list_itr.o hashMap.o 
TESTFILE = test/test_shani.o 
EXEFILE= test/hashMapTest


staticHash: $(OBJS)
	ar -cvq $(ARCHLIB)/staticHash.a $(OBJS)


test/hashMapTest : $(OBJS) 
	$(CC) $(CFLAGS) -o $(EXEFILE) $(OBJS) $(TESTFILE)

include depends

depends:
	$(CC) -MM -I$(INCDIR) $(OBJS:.o=.c) > depends


clean:
	rm -f depends
	rm -f $(OBJS)
	rm -f test/*.o
	rm -f test/hashMapTest	
	
	
	
	
	

