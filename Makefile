.PHONY := all clean

CC := g++
CFLAGS := -std=c++23 -g -Wall -Wextra
LDFLAGS :=
LDLIBS :=

INCDIR := ./include
SRCDIR := ./src
OBJDIR := ./obj
BINDIR := .

INC := $(wildcard $(INCDIR)/*.h)
SRC := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
BIN := $(BINDIR)/condot

all: $(BIN)

$(BIN): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INC)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I $(INCDIR) -o $@ -c $<

clean:
	rm -rf $(OBJ) $(BIN)
