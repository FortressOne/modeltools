##### Common variables #####

CC=gcc
CFLAGS=-MD -Wall
#CFLAGS=-MD -Wall -g
LDFLAGS=-lm
COMMON=util.o file.o

ifdef windir
CMD_RM=del
else
CMD_RM=rm -f
endif

WIN32_EXES=modeltool.exe makesp2.exe
UNIX_EXES=modeltool makesp2

##### Commands #####

.PHONY: all mingw clean

all:
ifdef windir
	@$(MAKE) $(WIN32_EXES)
else
	@$(MAKE) $(UNIX_EXES)
endif

mingw:
	@$(MAKE) $(WIN32_EXES)

.c.o:
	$(CC) $(CFLAGS) -c $*.c

modeltool.exe: modeltool.o $(COMMON)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

modeltool: modeltool.o $(COMMON)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

makesp2.exe: makesp2.o $(COMMON)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

makesp2: makesp2.o $(COMMON)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	-$(CMD_RM) $(WIN32_EXES) $(UNIX_EXES) *.o *.d

