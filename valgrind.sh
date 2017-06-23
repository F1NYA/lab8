#!/usr/bin/env bash

if [ $1 = "C" ]
then
    /usr/bin/clang -ggdb main.c -std=c99 -Wall -Werror -o program && /usr/local/bin/valgrind ./program
elif [ $1 = "Cpp" ]
then
    g++ -stdlib=libc++ main.cpp ReqProcessor.cpp JsonFormer.cpp json.hpp -levent -Wall -Werror -g program && /usr/local/bin/valgrind ./program
fi