#!/bin/bash

if [ $# -eq 1 ] ; then
    dir="$1"
else
    read dir 
fi

for f in $(ls "$dir"); do
    mv -v "$dir/$f" "$(echo "$dir/$f" | tr '[A-Z]' '[a-z]')"
done

exit 0

find "$dir" -type f -exec sh -c 'mv "$1" "${$1,,}"' x {} \;
