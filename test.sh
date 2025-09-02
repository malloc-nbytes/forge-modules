#!/bin/bash

set -e

for file in *.c; do
    if [[ -f "$file" ]]; then
        echo "gcc -shared -fPIC -o \"${file%.c}.so\" \"$file\""
        cc -shared -fPIC -o "${file%.c}.so" "$file"

        if ! [[ $? -eq 0 ]]; then
                echo "Failed to compile $file"
                exit 1
        fi
    else
        echo "No .c files found in the current directory"
        exit 1
    fi
done

echo "Removing all .so files..."
rm -f *.so
echo "Done."
