.PHONY: clean 
HTTPSPROXY = ../obj/hpy
PRODUCTS = $(HTTPSPROXY)
default: $(PRODUCTS)

OBJDIR = ../obj

include collections/makefile
include core/makefile


# OBJS can deal with either .cc or .c 
OBJS = $(OBJDIR)/hpy_threadsafe_queue.o 
OBJS += $(OBJDIR)/hpy_tcp.o $(OBJDIR)/hpy_connection.o $(OBJDIR)/hpy_handler.o $(OBJDIR)/hpy_proxy.o 
OBJS += $(OBJDIR)/hpy_main.o

JUNK = *~ $(OBJDIR)/*.o $(OBJDIR)/*.a  

# Define the tools we are going to use
CC= g++
LD = g++

CFLAGS = -g -Wall -Wno-unused -Wno-sign-compare -std=c++11 -I.

LIBS = -lc -lm -ll -lpthread

$(OBJDIR)/hpy_main.o: hpy_main.cc
	$(CC) $(CFLAGS) -c -o $@ $<

$(PRODUCTS) : $(OBJS)
	$(LD) -o $@ $(OBJS) $(LIBS)
	cp $(PRODUCTS) ./



#unittest,using googletest:https://github.com/google/googletest/blob/master/googletest/docs/Primer.md
#this make no sense, and just test googletest

clean:
	@rm -f $(JUNK) $(PRODUCTS) 


