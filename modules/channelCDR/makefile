
# ChannelCDR makefile

# compulsory flags
CC = gcc
CFLAGS = -g -ansi -pedantic -Wall -Werror
INCDIR = ../../inc 

# local defs
CFLAGS += -I$(INCDIR)
OBJS = channelCDR.o test/runChannel.o


test/runChannel : $(OBJS)
	$(CC) $(CFLAGS) -o test/runChannel $(OBJS:.o=.c) 
	
include depends

depends:
	$(CC) -MM -I$(INCDIR)  -c $(OBJS:.o=.c) > depends

clean:
	rm -f depends
	rm -f $(OBJS)
	rm -f test/runChannel

		

