#!/bin/bash

# Проверяем, что передано два аргумента
if [ "$#" -ne 2 ]
then
    # "$#" - количество переданных аргументов
    # -ne расшифровывается как "not equal", эквивалентно !=
    echo "Usage: $0 directory1 directory2"
    exit 1
fi

# конструкция $() используется для выполнения команд в подоболочке и захвата вывода этой команды в переменную или его использования в другом контексте
echo "$(find "$1" -type f | wc -l) files were found in directory "$1""
echo "$(find "$2" -type f | wc -l) files were found in directory "$2""

# попарно сравниваем все файлы из двух переданных каталогов
for file1 in "$1"/*
do
    for file2 in "$2"/*
    do
        out=$(diff "$file1" "$file2")
        if [ -z "$out" ]
        then
            # -z используется для проверки, является ли строка пустой (имеет нулевую длину)
            echo "files "$file1" and "$file2" are the same"
        fi
    done
done