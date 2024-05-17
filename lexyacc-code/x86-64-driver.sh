#!/bin/bash

# Check if an input file is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <input_file>"
    exit 1
fi

input_file=$1
output_file="${input_file%.s}"

# Assemble the input assembly code
as -o ${output_file}.o $input_file

# Set the library path to include the current directory
export LD_LIBRARY_PATH=.

# Link the object file with calc3i.c, libmathlib.so, and main.c
gcc -no-pie -o $output_file calc3i.c main.c ${output_file}.o -L. -lmathlib

# Run the generated executable
./$output_file
