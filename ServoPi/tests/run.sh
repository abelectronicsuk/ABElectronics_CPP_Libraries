#!/bin/bash
if [ "$#" -eq  "0" ]
    then
        for file in bin/*; do 
            ./"$file"
        done
        exit 1
else
    file="bin/"$1""
    ./"$file"
fi

