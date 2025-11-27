#!/bin/bash

echo "=== Environment Debug ==="
echo "PWD: $(pwd)"
echo "SHELL: $SHELL"
echo "USER: $USER"
echo ""
echo "=== Library Check ==="
ls -la *.dylib 2>/dev/null | head -5
echo ""
echo "=== Running sfml-app ==="
./sfml-app
echo "Exit code: $?"





