#!/bin/bash

if [ $# -eq 1 ] ; then
    file="$1"
else
    read file
fi

long=0
while read -r line; do
    cur=$(echo $line | wc -c)

    if [ $cur -gt $long ] ; then
        long="$cur"
    fi
done < "$file"

echo "$file contiene $(wc -l $file) linee, di cui la più lunga di $long caratteri"
