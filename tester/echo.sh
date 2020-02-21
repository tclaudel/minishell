#!/bin/bash

echo 'echo pouet'
sleep "$1"

echo 'echo "pouet'
sleep 0.1
echo '"'
sleep "$1"

echo 'echo "pouet"str""'
sleep "$1"

echo 'echo "po  uet"str""'
sleep "$1"

echo 'echo euh NTM'
sleep "$1"

echo 'echo "pouet" "str"'
sleep "$1"

echo 'echo $PWD'
sleep "$1"

echo 'echo "$PWD"'
sleep "$1"

echo 'echo '$PWD''
sleep "$1"

echo 'echo E$PWD'
sleep "$1"
