#!/bin/bash
for file in *.c;
do 
    gcc -std=gnu99 -Werror -c "$file"
done
string=''
for file in *.o;
do
    string+="$file "
done
eval gcc -o app.exe "$string" -lm
