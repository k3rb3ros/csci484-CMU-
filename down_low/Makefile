CC:=gcc #C Compiler
CFLAGS:=-std=c99 -O0 -I/home/k3rb3ros/csci484-CMU-/libtomcrypt-1.17/src/headers -g -Wall -Wextra #C Compiler flags
CPP:=g++ #C++ Compiler
CPPFLAGS:=-std=gnu++0x -O0 -I/home/k3rb3ros/csci484/csci484-CMU-/libtomcrypt-1.17/src/headers -L. -g -Wall -Wextra #C++ Compiler flags
#CPPFLAGS:=-std=gnu++0x -O0 -g -Wall -Wextra #C++ Compiler flags
LDFLAGS:= -lSDL -lSDL_net -ltomcrypt -ltfm 
CSOURCES= #C files used in this program
CPPSOURCES=connection.cpp chat.cpp test_crypt.cpp #CPP files used in this prgram
#COBJECTS=$(CSOURCES:.c=.o)libtfm.a libtomcrypt.a
COBJECTS=$(CSOURCES:.c=.o)
CPPOBJECTS=$(CPPSOURCES:.cpp=.o)
BINARY=down_low

all: $(BINARY) $(COBJECTS) $(CPPOBJECTS)
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.cpp.o:
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(BINARY): $(COBJETS) $(CPPOBJECTS)
	 $(CPP) $(CPPFLAGS) $(COBJECTS) $(CPPOBJECTS) -o $@ $(LDFLAGS)

clean:
	 rm -rfv $(BINARY) $(COBJECTS) $(CPPOBJECTS)
