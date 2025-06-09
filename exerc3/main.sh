#!/bin/bash
set -e

# Garante que o executável antigo seja removido antes de compilar
rm -f main

# Compila todos os arquivos .c
echo "Compilando o código..."
gcc -std=c99 -Wall -o main *.c

# Se não houver argumentos, executa os casos de teste
if [ $# -eq 0 ]; then
    echo "Teste: Criando tabela hash com 11 posições"
    ./main criar 11 hash

    echo "Teste: Inserindo dados de vários alunos"
    ./main inserir hash 15489730,Thales Vasconcelos Aguiar de Oliveira,Computação,41923202,Rosa Oliveira Pinto da Silva,Civil,23193023,Rosemar da Silva,Materiais,12345678,Pudim de Passas,Petróleo,23456789,Olimar,Gastronomia,

    echo "Teste: Removendo dois alunos"
    ./main remover hash 41923202,23193023

    echo "Teste: Consultando dados de três alunos"
    ./main buscar hash 41923202,12345678,23456789

else
    ./main "$@"
fi