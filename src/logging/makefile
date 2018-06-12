LOGGINGDIR := logging


$(OBJDIR)/hpy_config.o: $(LOGGINGDIR)/hpy_config.cc
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/hpy_logging.o: $(LOGGINGDIR)/hpy_logging.cc $(LOGGINGDIR)/hpy_logging.ini ../logs
	$(CC) $(CFLAGS) -c -o $@ $<

../logs: 
	mkdir ../logs



