#!/bin/bash

# Get all environment variables that differ from clean env
ALL_VARS=$(diff <(env -i PATH=/usr/bin:/bin HOME=$HOME env | sort) <(env | sort) | grep "^>" | sed 's/^> //' | cut -d= -f1)

echo "Binary search approach: Testing halves of variables"
echo ""

# Build clean env base
CLEAN_BASE="env -i PATH=/usr/bin:/bin:/usr/sbin:/sbin HOME=\$HOME TERM=\$TERM"

# Convert to array for easier manipulation
vars_array=()
for var in $ALL_VARS; do
    [ -z "$var" ] && continue
    original_value=$(eval echo \$$var)
    [ -z "$original_value" ] && continue
    vars_array+=("$var=$original_value")
done

total=${#vars_array[@]}
echo "Total variables to test: $total"
echo ""

# Test first half
half=$((total / 2))
first_half="${vars_array[@]:0:$half}"
second_half="${vars_array[@]:$half}"

echo "Testing first half ($half variables)..."
eval "$CLEAN_BASE $(printf '%s ' $first_half)" timeout 2 ./sfml-app > /dev/null 2>&1
first_half_result=$?

echo "Testing second half ($((total - half)) variables)..."
eval "$CLEAN_BASE $(printf '%s ' $second_half)" timeout 2 ./sfml-app > /dev/null 2>&1
second_half_result=$?

if [ $first_half_result -eq 139 ]; then
    echo "❌ First half causes crash - narrowing down..."
    echo "Variables in first half:"
    printf '  %s\n' $first_half
elif [ $second_half_result -eq 139 ]; then
    echo "❌ Second half causes crash - narrowing down..."
    echo "Variables in second half:"
    printf '  %s\n' $second_half
else
    echo "⚠️  Neither half crashes individually - might be a combination"
    echo "Try testing with: env -i PATH=/usr/bin:/bin:/usr/sbin:/sbin HOME=\$HOME TERM=\$TERM ./sfml-app"
fi
