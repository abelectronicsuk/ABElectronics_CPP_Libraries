#!/bin/bash
if [ "$#" -eq  "0" ]
    then
        for file in testfiles/*.cpp; do 
            echo "Building" "$file"    
            outputname="$(basename "$file" .cpp)"
            g++ "$file" ../ABE_ExpanderPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o bin/"$outputname" -L/usr/local/lib
        done
        exit 1
else
    file="testfiles/"$1".cpp"
    echo "Building" "$file"    
    outputname="$(basename "$file" .cpp)"
    g++ "$file" ../ABE_ExpanderPi.cpp -Wall -Wextra -Wpedantic -Woverflow -o bin/"$outputname" -L/usr/local/lib
fi



























