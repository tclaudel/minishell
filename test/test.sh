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

function tab_space {
	lenvar=${#1}
	if [ $lenvar -lt 8 ]; then
		printf "\t\t\t\t\t\t\t\t\t\t\t\t"
	elif [ $lenvar -lt 16 ]; then
		printf "\t\t\t\t\t\t\t\t\t\t\t"
	elif [ $lenvar -lt 24 ]; then
		printf "\t\t\t\t\t\t\t\t\t\t"
	elif [ $lenvar -lt 32 ]; then
		printf "\t\t\t\t\t\t\t\t\t"
	elif [ $lenvar -lt 40 ]; then
		printf "\t\t\t\t\t\t\t\t"
	elif [ $lenvar -lt 48 ]; then
		printf "\t\t\t\t\t\t\t"
	elif [ $lenvar -lt 56 ]; then
		printf "\t\t\t\t\t\t" 
	elif [ $lenvar -lt 64 ]; then
		printf "\t\t\t\t\t"
	elif [ $lenvar -lt 72 ]; then
		printf "\t\t\t\t"
	elif [ $lenvar -lt 80 ]; then
		printf "\t\t\t"
	elif [ $lenvar -lt 88 ]; then
		printf "\t\t"
	else
		printf "\n"
	fi
}

function refactoring {
	pouet="'"$1"'"
	echo 'printf "\33[2K\r\n###############\ntesting : %s\n###############\n\n"' $pouet >&3
	echo 'echo "pouet"' >&4
	echo 'echo "pouet"' >&4
	echo 'echo "pouet"' >&4
	echo 'echo "pouet"' >&4
	printf "%s\n" $1 >&3
	printf "%s\n" $1 >&4
}

commands_file="./test/commands";
commands_refactored="./test/commands_refactored"
commands_bash_refactored="./test/commands_bash_refactored"
declare -a COMMANDS;
declare -a USER_OUTPUT_TAB;
declare -a BASH_OUTPUT_TAB;
make;
exec 3<>$commands_refactored
exec 4<>$commands_bash_refactored
> $commands_refactored
> $commands_bash_refactored
IFS=$'\n'
while read commands;
do
	refactoring $commands
done < ./test/commands
nb_of_commands=${#COMMANDS[*]};
printf "testing %d commands\n" $nb_of_commands;
USER_OUTPUT_TAB=( $(./minishell < $commands_refactored | sed 's/\x1b\[[0-9;]*m//g') )
BASH_OUTPUT_TAB=( $(bash < $commands_bash_refactored) )
for (( i=0; i<${#USER_OUTPUT_TAB[@]}; i++ ));
do
	printf "${USER_OUTPUT_TAB[$i]}"
	tab_space ${USER_OUTPUT_TAB[$i]}
	printf "${BASH_OUTPUT_TAB[$i]}\n" | sed 's/pouet/\n/g'
done
printf $RESET
