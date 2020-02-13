echo 'env'
sleep 2

echo 'export TEST=test'
sleep 0.5

echo 'env'
sleep 2

echo 'unset TEST'
sleep 0.5

echo 'export TEST1= TEST2 TEST3=test3 TEST3=test4'
sleep 0.5

echo 'env'
sleep 2

echo 'echo $TEST3'
sleep 1.2

echo 'unset TEST1 TEST3'
sleep 1.2

echo 'env'
sleep 2

echo 'unset HOME ; cd ; pwd'
sleep 2

echo 'unset PWD OLDPWD USER PATH ; env ; sleep 2 ; pwd ; sleep 2 ; ls -la'
sleep 2

