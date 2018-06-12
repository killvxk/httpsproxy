.PHONY: clean 
HTTPSPROXY = ../obj/hpy
PRODUCTS = $(HTTPSPROXY)
default: $(PRODUCTS)

OBJDIR = ../obj

include collections/makefile
include core/makefile
include utils/makefile
include logging/makefile

include unittest/makefile
include unittest/utils/makefile
include unittest/logging/makefile


# OBJS can deal with either .cc or .c 
OBJS = $(OBJDIR)/hpy_threadsafe_queue.o 
OBJS += $(OBJDIR)/hpy_tcp.o $(OBJDIR)/hpy_connection.o $(OBJDIR)/hpy_handler.o $(OBJDIR)/hpy_proxy.o 
OBJS += $(OBJDIR)/hpy_logging.o $(OBJDIR)/hpy_config.o 
OBJS += $(OBJDIR)/hpy_stringutil.o
OBJS += $(OBJDIR)/hpy_main.o

JUNK = *~ $(OBJDIR)/*.o $(OBJDIR)/*.a  

# Define the tools we are going to use
CC= g++
LD = g++

CFLAGS = -g -Wall -Wno-unused -Wno-sign-compare -std=c++11 -I.

LIBS = -lm -lc

$(OBJDIR)/hpy_main.o: hpy_main.cc
	$(CC) $(CFLAGS) -c -o $@ $<

$(PRODUCTS): $(OBJDIR)/hpy_config.o $(OBJDIR)/hpy_logging.o $(OBJDIR)/hpy_main.o  $(OBJDIR)/hpy_stringutil.o     
	$(LD) -o $@  $^  $(LIBS)
	cp $(PRODUCTS) ./

#unittest,using googletest:https://github.com/google/googletest/blob/master/googletest/docs/Primer.md
#this make no sense, and just test googletest
UNITTEST = ut-utils-stringutil

ut-utils-stringutil: $(OBJDIR)/hpy_stringutil_ut
	./$(OBJDIR)/hpy_stringutil_ut

ut-logging-logging: $(OBJDIR)/hpy_logging_ut 
	./$(OBJDIR)/hpy_logging_ut  

ut-logging-config: $(OBJDIR)/hpy_config_ut
	./$(OBJDIR)/hpy_config_ut

clean:
	@rm -f $(JUNK) $(PRODUCTS)


