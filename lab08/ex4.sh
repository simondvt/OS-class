#!/bin/bash

declare -A parole

for word in $(<"$1")
do
    if [ ${parole["$word"]+_} ] ; then
        ((parole["$word"]++))
    else
        parole["$word"]=1
    fi
done

for k in "${!parole[@]}" ; do
    echo $k ${parole[$k]}
done
