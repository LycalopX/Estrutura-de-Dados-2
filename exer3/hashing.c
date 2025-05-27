#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned int hashing(int nUSP)
{

    unsigned int altered = nUSP, digito, resultado = 0;

    int primos[8] = {2, 3, 5, 7, 11, 13, 17, 19};

    // Somando 1 a cada valor, e multiplicando pelo valor primo correspondente.
    for (int i = 0; i < 8; i++)
    {
        digito = altered % 10;
        altered /= 10;

        digito = (digito + 1) % 10;

        // Resultado da primeira operação
        resultado += digito * primos[7 - i];
    }

    // Usando unsigned int, precisamos inverter as ordens do bit.

    // Sabemos que trocando de ordem a primeira metade com a segunda, por exemplo, bit 1 -> bit 17.
    // Logo, só precisamos pegar os bits individualmente e avançar 16 bits.

    unsigned int esquerda = (resultado >> 16) & 0xFFFF;
    unsigned int direita = resultado & 0xFFFF;

    unsigned int invertido = (direita << 16) | esquerda;

    // Operação de XOR

    // Etapa 3: XOR final entre bits

    unsigned int xor, impar, par;

    impar = (invertido % 10 >> 3) & 1;
    invertido /= 10;

    par = (invertido % 10) & 1;
    invertido /= 10;

    xor = (impar ^ par);

    unsigned int hashed = xor;

    // Pegando cada dígito, e aplicando XOR
    for (int i = 1; invertido != 0; i++)
    {
        digito = (invertido % 10) >> ((i % 2) * 3) & 1;
        invertido /= 10;

        xor = xor ^ digito;

        // Resultado da primeira operação
        hashed = (hashed << 1) | xor;
    }

    return hashed;
};