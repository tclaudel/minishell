#!/bin/bash

echo 'env'
sleep "$1"

echo 'export TEST=test'
sleep "$1"

echo 'env'
sleep "$1"

echo 'unset TEST'
sleep "$1"

echo 'export TEST1= TEST2 TEST3=test3 TEST3=test4'
sleep "$1"

echo 'env'
sleep "$1"

echo 'echo $TEST3'
sleep "$1"

echo 'unset TEST1 TEST3'
sleep "$1"

echo 'env'
sleep "$1"

echo 'unset HOME ; cd ; pwd'
sleep "$1"

echo 'unset PWD OLDPWD USER PATH ; env ; sleep "$1" ; pwd ; sleep "$1" ; ls -la'
sleep "$1"

echo 'unset PWD ; ./minishell ; echo $PWD'
sleep "$1"
