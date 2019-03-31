#!/bin/bash

clear
echo -e "\n********** Scenario １ **********\n"
./bufcache <<EOS
init
hash
free
getblk 4
hash 
free
EOS
echo -e "\n\n"
read -r -p "Press Enter key to continue ..." key
echo -e "\n\n\n\n\n\n\n\n"

clear
echo -e "\n ********** Scenario 2 **********\n"
./bufcache <<EOS
init
hash
free
getblk 18
hash
free
EOS
echo -e "\n\n"
read -r -p "Press Enter key to continue ..." key
echo -e "\n\n\n\n\n\n\n\n"

clear
echo -e "\n ********** Scenario 3 **********\n"
./bufcache <<EOS
init
hash
free
set 3 stat D
set 5 stat D
hash
free
getblk 18
hash
free
EOS
echo -e "\n\n"
read -r -p "Press Enter key to continue ..." key
echo -e "\n\n\n\n\n\n\n\n"

clear
echo -e "\n ********** Scenario 4 **********\n"
./bufcache <<EOS
init
hash
free
getblk 3
getblk 5
getblk 4
getblk 28
getblk 97
getblk 10
free
getblk 18
hash
free
EOS
echo -e "\n\n"
read -r -p "Press Enter key to continue ..." key
echo -e "\n\n\n\n\n\n\n\n"

clear
echo -e "\n ********** Scenario 5 **********\n"
./bufcache <<EOS
init
hash
free
getblk 64
hash
free
EOS
echo -e "\n\n"
read -r -p "Press Enter key to continue ..." key
echo -e "\n\n"