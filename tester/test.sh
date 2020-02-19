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

function ft_echo {
	printf "$BLUETEST\nECHO\n\n$GREY";
	sleep "$1";
	sh ./tester/echo.sh "$1" | "$2";
	sh ./tester/echo.sh "$1" | "$3";
}

function ft_builtin {
	printf "$BLUETEST\nBUILTINS\n\n$GREY";
	sleep "$1";
	sh ./tester/builtin.sh "$1" | "$2";
	sh ./tester/builtin.sh "$1" | "$3";
}

function ft_env {
	printf "$BLUETEST\nENV\n\n$GREY";
	sleep "$1";
	sh ./tester/env.sh "$1" | "$2";
	sh ./tester/env.sh "$1" | "$3";
}

make

if ! [ -z $1 ] ; then
	var_sleep="$1";
else
	var_sleep="1";
fi
echo "var_sleep = $var_sleep";
if [ -z $2 ]; then
	cat "./coucou"
	default=1;
else
	default=0;
fi
if [ "$2" == "echo" ] || [ "$default" == "1" ]; then
	ft_echo "$var_sleep" "./minishell" "bash";

fi
if [ "$2" == "builtin" ] || [ "$default" == "1" ]; then
	ft_builtin "$var_sleep" "./minishell" "bash";
fi
if [ "$2" == "env" ] || [ "$default" == "1" ]; then
	ft_env "$var_sleep" "./minishell" "bash";
fi
