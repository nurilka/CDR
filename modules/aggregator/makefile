
# Aggregator makefile

.PHONY: clean 

CC = gcc
CFLAGS = -ansi -pedantic -Wall -Werror
INCLUDES= ../../inc 


# specific definitions
CFLAGS += -I$(INCDIR) -g
OBJS =  ../channelCDR/channelCDR.o ../aggregator/aggregator.o
STLIB = ../../archLib/staticHash.a
TESTFILE= mainRcvFromCH.o 
EXEFILE= runRcvFromCH


$(EXEFILE) : $(OBJS) $(STLIB)
	$(CC) $(CFLAGS) -o $(EXEFILE) $(TESTFILE:.o=.c) $^  
		
include depends
 
depends:
	$(CC) -MM -I$(INCLUDES) -c $(OBJS:.o=.c) $(STLIB) > depends


clean:
	rm -f depends
	rm -f $(OBJS)
	rm -f test/*.o
	rm -f test/hashMapTest	
	


	
	
	

