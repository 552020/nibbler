#!/bin/bash

echo "=== Environment Check ==="
echo "Current directory: $(pwd)"
echo "Shell: $SHELL"
echo "User: $USER"
echo ""
echo "=== Checking if we're in the right place ==="
if [ -f "./sfml-app" ] && [ -d "./assets" ] && [ -d "./src" ]; then
    echo "✅ In correct directory"
else
    echo "❌ Wrong directory! Please cd to lab/sfml"
    exit 1
fi
echo ""
echo "=== Checking libraries ==="
ls -1 *.dylib 2>/dev/null | wc -l | xargs echo "Found dylib files:"
echo ""
echo "=== Checking assets ==="
ls -1 assets/cabinet.jpg assets/arial/ARIAL.TTF 2>/dev/null && echo "✅ Assets found" || echo "❌ Assets missing"
echo ""
echo "=== Testing with wrapper script ==="
echo "Run: ./run.sh"
echo ""
echo "=== Or test directly ==="
echo "Run: ./sfml-app"




