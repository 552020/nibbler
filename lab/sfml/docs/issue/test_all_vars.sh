#!/bin/bash
# Test all environment variables by adding them to env -i

cd "$(dirname "$0")/../.."

# Read all variables from env_vars.txt and build env -i command
ENV_ARGS="PATH=$PATH HOME=$HOME TERM=$TERM"

while IFS='=' read -r key value; do
    # Skip empty lines and variables starting with _
    [[ -z "$key" || "$key" =~ ^_ ]] && continue
    # Skip PATH, HOME, TERM (already added)
    [[ "$key" == "PATH" || "$key" == "HOME" || "$key" == "TERM" ]] && continue
    # Add the variable
    ENV_ARGS="$ENV_ARGS $key=$value"
done < env_vars.txt

echo "Testing with all variables..."
eval "env -i $ENV_ARGS ./sfml-app"



