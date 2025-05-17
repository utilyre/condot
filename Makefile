.PHONY: all clean
MAKEFLAGS+=-j

CXX=g++
CXXFLAGS=-std=c++20 -g -Wall -Wextra
LDFLAGS=-L./lib
LDLIBS=-lraylib

INCDIR=./include
SRCDIR=./src
OBJDIR=./obj
BINDIR=.

INC=$(wildcard $(INCDIR)/*.hpp) $(wildcard $(INCDIR)/*.h)
SRC=$(wildcard $(SRCDIR)/*.cpp)
OBJ=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
BIN=$(BINDIR)/condot

all: $(BIN)

$(BIN): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INC)
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -o $@ -c $<

clean:
	rm -f $(OBJ) $(BIN)
