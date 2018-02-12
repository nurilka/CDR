
.PHONY: clean 
CC = gcc
INCLUDES= ../../inc 

CFLAGS = -ansi -Werror -Wall -pedantic -pthread
OBJS =  ../channelCDR/channelCDR.o ../aggregator/aggregator.o
CFLAGS += -I$(INCLUDES) -g 
TESTFILE= mainRcvFromCH.o 
EXEFILE= runRcvFromCH
STLIB = ../../archLib/staticHash.a

$(EXEFILE) : $(OBJS) $(STLIB)
	$(CC) $(CFLAGS) -o $(EXEFILE) $(TESTFILE:.o=.c) $^  
		
include depends
 
depends:
	$(CC) -MM -I$(INCLUDES) -c $(OBJS:.o=.c) $(STLIB) > depends


clean :
	rm -f depends
	rm -f $(OBJS)
	rm -f *.o
	rm -f runRcvFromCH	



