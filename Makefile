# Compiler and linker
CC := gcc
AS := as
LEX := flex
YACC := bison

# Compiler and assembler flags
CFLAGS := -Wall -g
LDFLAGS := -no-pie

# Source and object files
SRC := lexyacc-code/calc3i.c
OBJ := lexyacc-code/calc3i.o lexyacc-code/y.tab.o lexyacc-code/lex.yy.o src/mathlib.o

# Shared library name
LIB := lib/libmathlib.so

# Default target
all: $(LIB)

# Generate lex.yy.c from calc3.l
lexyacc-code/lex.yy.c: lexyacc-code/calc3.l
	$(LEX) -o $@ $<

# Generate y.tab.c and y.tab.h from calc3.y
lexyacc-code/y.tab.c lexyacc-code/y.tab.h: lexyacc-code/calc3.y
	$(YACC) -d -o lexyacc-code/y.tab.c $<

# Compile lex.yy.c with -fPIC flag
lexyacc-code/lex.yy.o: lexyacc-code/lex.yy.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# Compile y.tab.c with -fPIC flag
lexyacc-code/y.tab.o: lexyacc-code/y.tab.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# Compile the C source file
lexyacc-code/calc3i.o: lexyacc-code/calc3i.c lexyacc-code/y.tab.h
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# Assemble the assembly source file
src/mathlib.o: src/mathlib.s
	$(AS) -o $@ $<

# Target for creating the shared library
$(LIB): $(OBJ)
	$(CC) $(LDFLAGS) -shared $^ -o $@

# Clean target
clean:
	rm -f $(OBJ) lexyacc-code/lex.yy.c lexyacc-code/y.tab.c lexyacc-code/y.tab.h $(LIB)

.PHONY: all clean
