# Compiler and linker
CC := gcc
AS := as

# Compiler and assembler flags
CFLAGS := -Wall -g
LDFLAGS := -no-pie

# Source and object files
SRC := calc3i.c
OBJ := $(SRC:.c=.o) mathlib.o
ASM_SRC := mathlib.s

# Shared library name
LIB := libmathlib.so

# Default target
all: $(LIB)

# Compile the C source file
%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# Assemble the assembly source file
%.o: %.s
	$(AS) -o $@ $<

# Target for creating the shared library
$(LIB): $(OBJ)
	$(CC) $(LDFLAGS) -shared $^ -o $@

# Clean target
clean:
	rm -f $(OBJ) $(LIB)

.PHONY: all clean

