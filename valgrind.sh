#!/bin/bash/
DARK_BLUE="\033[1;38;5;110m"
LIGHT_GREEN="\033[0;38;5;121m"

echo "	\033[2K\r $DARK_BLUE Welcome to valgring\n\033[0m"
docker build -t tmp .
docker run --rm --name $USER -ti tmp