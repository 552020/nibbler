#!/bin/bash

echo "=== Checking for shell interference ==="
echo ""

echo "1. Checking for aliases:"
alias | grep -E "sfml|\.\/" || echo "  No relevant aliases found"
echo ""

echo "2. Checking for functions:"
functions | grep -E "sfml|command_not_found|precmd|preexec" || echo "  No relevant functions found"
echo ""

echo "3. Checking if ./sfml-app is actually the file:"
type ./sfml-app
echo ""

echo "4. Checking file directly:"
ls -la ./sfml-app
file ./sfml-app
echo ""

echo "5. Try running with explicit path:"
echo "   $(pwd)/sfml-app"
echo ""

echo "6. Check if it's being backgrounded:"
echo "   Run: ./sfml-app &"
echo "   Then: fg"
echo "   Or: ./sfml-app; echo 'Exit code: $?'"



