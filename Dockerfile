FROM ubuntu:18.04
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y gcc
RUN apt-get install -y zsh
RUN apt-get install -y curl
RUN apt-get install -y vim
RUN apt-get install -y make
RUN apt-get install -y valgrind

WORKDIR /home/

COPY ./ ./

RUN		make
RUN		touch valgrind_output
# PLEASE CHANGE THIS LINE TO COMPILE YOUR CORRECT FILES
RUN		gcc test.c libftprintf.a > /dev/null 2>&1
# PLEASE CHANGE ./a.out FOR YOUR CORRECT EXE
RUN		valgrind --leak-check=full --log-file="valgrind_output" ./minishell > /dev/null 2>&1
RUN		cat valgrind_output
CMD		exit