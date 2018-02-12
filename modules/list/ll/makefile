
# List makefile


NAME = list

#path and lib name
LIBPATH = ../../shLib
DYNAMICLIB = lib$(NAME).so
LINK2 = $(DYNAMICLIB).1.0
LINK1 = $(DYNAMICLIB).1
MOVETOLIB = mv $(LINK2) $(LIBPATH)

#include ../makefile.symbols
CC = gcc
CFLAGS = -ansi -pedantic -Wall -Werror
INCDIR = ../../inc

#flag for shared lib
FPIC = -fPIC
LARGE64 = -mcmodel=large
LIBFLAGS = -shared -Wl,-soname,$(LINK1) -o 

# local defs
CFLAGS+= -I$(INCDIR) -g
OBJS= $(NAME).o $(NAME)_itr.o

lib : $(LINK2)
	@$(MOVETOLIB)
	@ln -sf $(LINK2) $(LIBPATH)/$(DYNAMICLIB)
	@ln -sf $(LINK2) $(LIBPATH)/$(LINK1)
	
$(LINK2): $(OBJS)
	$(CC) $(LARGE64) $(LIBFLAGS) $(LINK2) $(OBJS)

include depends

depends:
	$(CC) -MM  $(FPIC) -I$(INCDIR) -c $(OBJS:.o=.c) -L$(LIBPATH) -llist > depends

clean:
	rm -f depends
	rm -f $(OBJS)

# export LD_LIBRARY_PATH = ~/Experis/IPC/lib
