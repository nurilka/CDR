
.Phony: clean 
CC = gcc
INCLUDES= ../../inc 

CFLAGS = -ansi -Werror -Wall -pedantic -pthread
OBJS =  ../channelCDR/channelCDR.o
CFLAGS += -I$(INCLUDES) -g 
TESTFILE= mainSend2CH.o
EXEFILE= runSend2CH


$(EXEFILE) : $(OBJS) 
	$(CC) $(CFLAGS) -o $(EXEFILE) $(TESTFILE:.o=.c) $^  
		
include depends
 
depends:
	$(CC) -MM -I$(INCLUDES) -c $(OBJS:.o=.c) $(LIB) > depends

#$(LIB):
#	cd .. && cd hashMap && $(MAKE) -f makefile 


clean :
	rm -f depends
	rm -f $(OBJS)
	rm -f *.o
	rm -f runSend2CH	


