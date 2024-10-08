.PHONY: all clean
MAKEFLAGS+=-j

CC=g++
CFLAGS=-std=c++20 -g -Wall -Wextra
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
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INC)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ -c $<

clean:
	rm -f $(OBJ) $(BIN)
