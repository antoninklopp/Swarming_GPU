#!/bin/bash
for i in $(seq 10 10 200)
    do 
        echo $i; 
        ../bin/03_cuda/main_cuda $i >> measures.txt; 
    done