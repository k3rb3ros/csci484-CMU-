CC:=gcc #C Compiler
CFLAGS:=-std=c99 -O0 -g -Wall -Wextra #C Compiler flags
CPP:=g++ #C++ Compiler
CPPFLAGS:=-std=gnu++0x -O0 -g -Wall -Wextra #C++ Compiler flags
CPPEXTRA:= -lSDL -lSDL_net
CSOURCES= #C files used in this program
CPPSOURCES=network.cpp #CPP files used in this prgram
COBJECTS=$(CSOURCES:.c=.o) 
CPPOBJECTS=$(CPPSOURCES:.cpp=.o)
BINARY=down_low

all: $(BINARY) $(COBJECTS) $(CPPOBJECTS)
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ #Invoke gcc for C Files

.cpp.o:
	$(CPP) $(CPPFLAGS) -c $< -o $@ #Invke g++ for cpp files

$(BINARY): $(COBJETS) $(CPPOBJECTS)
	 $(CPP) $(CPPFLAGS) $(CPPEXTRA) $(COBJECTS) $(CPPOBJECTS) -o $@

clean:
	 rm -rfv $(BINARY) $(COBJECTS) $(CPPOBJECTS)
