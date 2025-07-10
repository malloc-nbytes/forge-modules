#!/bin/bash

set -xe

for file in *.c; do
    # Check if any .c files exist
    if [[ -f "$file" ]]; then
        echo "Compiling $file..."

        gcc -shared -fPIC -o "${file%.c}.so" "$file"

        # Check if compilation was successful
        if [[ $? -eq 0 ]]; then echo "Successfully compiled $file to ${file%.c}.so"
        else echo "Failed to compile $file"
        fi
    else
        echo "No .c files found in the current directory"
        exit 1
    fi
done

echo "Removing all .so files..."
rm -f *.so
echo "Done."
