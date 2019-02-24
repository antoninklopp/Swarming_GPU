#!/bin/bash
for i in $(seq 10 10 200)
    do 
        echo $i; 
        ../bin/01_cpp_threading/main_cpp $i >> measures.txt; 
    done