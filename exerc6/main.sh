#!/bin/bash
set -e  # Para o script se qualquer comando falhar

# Compilador e flags
CC=gcc
CFLAGS="-std=c99 -Wall -Wextra -g"
TARGET="main"

# Compilar todos os .c em .o
for src in *.c; do
    obj="${src%.c}.o"
    $CC $CFLAGS -c "$src" -o "$obj"
done

# Linkar tudo em um executável
$CC $CFLAGS -o "$TARGET" *.o

# Executar o programa
if [ $# -gt 0 ]; then
    ./main "$@"
else
    ./main quicksort 8 1 5

    ./main heapsort 3 9 2 4
fi
