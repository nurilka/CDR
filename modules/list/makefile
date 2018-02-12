

.Phony: clean 
CC = gcc
INCLUDES= ../../inc -I test/
ARCHLIB= ../../archLib

CFLAGS = -ansi -Werror -Wall -pedantic -pthread
OBJS = list.o list_itr.o  
CFLAGS += -I$(INCLUDES) -g 
TESTFILES= test/listTests.o test/listTestsCall.o
EXEFILE= test/listTestsCall

staticDS: $(OBJS)
	ar -cvq $(ARCHLIB)/staticDS.a $(OBJS)
	
test/listTestsCall : $(OBJS) $(TESTFILE)
	$(CC) $(CFLAGS) -o $(EXEFILE) $(TESTFILE:.o=.c) $^ 
	 
		
include depends
 
depends:
	$(CC) -MM -I$(INCLUDES) -c $(OBJS:.o=.c) > depends

clean :
	rm -f depends
	rm -f $(OBJS)
	rm -f test/*.o
	rm -f test/listTestsCall



