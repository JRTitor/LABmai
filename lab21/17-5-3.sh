#!/bin/bash
ans="Y"
ask=0
while [ -n "$1" ]
do
case "$1" in
 -y) ask=1 ;;
 -"?") echo "NAME
 ww17.sh - labiratory work № 21 variant 17
SYNOPSIS
 sh ww17.sh [OPTION] -- [DIRECTORY] [FORMAT]
DESCRIPTION
 ww17.sh - recursive search in the entered direction and decoding of text files;
############################REMEMBER
 That Decoding format must contain at least the same amount of characters as the
basic format
OPTIONS
 -? descpition of the command;
 -y set confirmation mode"
 exit;;
 --) shift
 break ;;
esac
shift 
done
echo
 if [ $ask = 1 ]; then
 for a in $(find $1 -depth -type f -exec grep -Iq . {} \; -print ); do
 file $a
 read -p 'DECODE Y/N:' ans
 if [ "$ans" == "Y" ]; then
 iconv -t $2 $a -o $a
 fi
 done
 else
 find $1 -depth -type f -exec grep -Iq . {} \; -print | while read a; do iconv -
t $2 $a -o $a
 done
fi 
