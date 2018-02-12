
# Controller makefile

# compulsory flags
CC = gcc
CFLAGS = -g -ansi -pedantic -Wall -Werror -pthread
INCDIR = ../../inc 

# local defs
CFLAGS += -I$(INCDIR)
OBJS =   ../channelCDR/channelCDR.o ../aggregator/aggregator.o  ../updater/updater.o
STLIB = ../../archLib/staticHash.a
TESTFILE= controller.o 
EXEFILE= runController


$(EXEFILE) : $(OBJS) $(STLIB)
	$(CC) $(CFLAGS) -o $(EXEFILE) $(TESTFILE:.o=.c) $^  
		
include depends
 
depends:
	$(CC) -MM -I$(INCLUDES) $(STLIB) -c $(OBJS:.o=.c)  > depends

clean:
	rm -f depends
	rm -f $(OBJS)
	rm -f runController




	
	
	
		

