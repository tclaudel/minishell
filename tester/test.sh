#!/bin/bash

BLUE="\033[0;38;5;123m"
LIGHT_PINK="\033[0;38;5;200m"
PINK="\033[0;38;5;198m"
DARK_BLUE="\033[1;38;5;110m"
GREEN="\033[1;32;111m"
LIGHT_GREEN="\033[0;38;5;121m"
LIGHT_RED="\033[0;31;5;110m"
FLASH_GREEN="\033[33;32m"
WHITE_BOLD="\033[37m"
GREY="\033[3;90m"
ORANGE="\033[3;91m"
YELLOW="\033[0;33m"
RESET="\033[0m"

make
printf "$BLUE TEST ECHO\n\n $GREY"
sleep 1
sh ./tester/echo.sh | ./minishell
printf "$BLUE TEST BUILTINS\n\n $GREY"
sleep 1
sh ./tester/builtin.sh | ./minishell