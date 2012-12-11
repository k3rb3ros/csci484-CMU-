CC:=gcc#C Compiler
CFLAGS:=-std=c99 -O0 -g -Wall -Wextra#C Compiler flags
CXX:=g++#C++ Compiler
CXXFLAGS:=-DTFM_DESC -std=gnu++0x -O0 -I/home/k3rb3ros/csci484/csci484-CMU-/libtomcrypt-1.17/src/headers/ -g -Wall -Wextra#C++ Compiler flags
LPATHS:=-L./libs
LDFLAGS:=-lSDL -lSDL_net -ltomcrypt -ltfm
CSOURCES= #C files used in this program
CXXSOURCES=connection.cpp chat.cpp crypt.cpp #CPP files used in this prgram
COBJECTS=$(CSOURCES:.c=.o)
CXXOBJECTS=$(CXXSOURCES:.cpp=.o)
BINARY=down_low

all: $(BINARY) $(COBJECTS) $(CXXOBJECTS)
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BINARY): $(COBJETS) $(CXXOBJECTS)
	 $(CXX) $(CXXFLAGS) $(LPATHS) $(COBJECTS) $(CXXOBJECTS) -o $@ $(LDFLAGS)

clean:
	 rm -rv $(BINARY) $(COBJECTS) $(CXXOBJECTS) *.o
