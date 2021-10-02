#!/bin/bash

# build test

if [ "$#" -eq  "0" ]
    then
        for file in testfiles/*.cpp; do 
            echo "Building" "$file"    
            outputname="$(basename "$file" .cpp)"
            g++ "$file" ../ABE_IoPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o bin/"$outputname" -L/usr/local/lib
        done
else
    file="testfiles/"$1".cpp"
    echo "Building" "$file"    
    outputname="$(basename "$file" .cpp)"
    g++ "$file" ../ABE_IoPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o bin/"$outputname" -L/usr/local/lib
fi

# run test

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
























