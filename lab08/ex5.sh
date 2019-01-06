#!/bin/bash

proc="$1"
time="$2"

cnt=0

while :; do
    status=$(ps -el | grep "$proc" | cut -f 9)
    if [ $status = "Z" ] ; then
        ((cnt++))
        
        if [ cnt -eq 5 ] ; then
            killall $proc
            exit 0
        fi
    else
        ((cnt=0))
    fi

    sleep "$time"
done
