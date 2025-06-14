#!/bin/bash

# Este script compila e executa o programa de hash.

# 1. Compila o programa
# O comando gcc é o mesmo, mas a convenção no Linux é não usar a extensão .exe
gcc main.c operacoes.c hash.c -o programa

# Verifica se a compilação foi bem-sucedida
if [ $? -ne 0 ]; then
    echo "Erro na compilacao. Verifique os erros acima."
    exit 1
fi

# 2. Executa o programa
# O "$@" é o equivalente do %* no shell script. Ele passa todos os
# argumentos da linha de comando para o programa.
./programa "$@"
