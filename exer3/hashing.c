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

    unsigned int xor, impar, par, hashed = 2;
    unsigned int temp = invertido;

    int odd;

    for (int j = 0; j < 4; j++)
    {
        temp = invertido;

        impar = ((temp % 10) >> (j)) & 1;
        temp /= 10;

        par = ((temp % 10) >> (3 - j)) & 1;
        temp /= 10;

        xor = (impar ^ par);

        // Pegando cada dígito, e aplicando XOR
        for (int i = 1; temp != 0; i++)
        {
            odd = (i % 2);

            if (odd)
            {
                digito = ((temp % 10) >> (3 - j)) & 1;
            }
            else
            {
                digito = ((temp % 10) >> (j)) & 1;
            }

            temp /= 10;

            xor = xor ^ digito;
        }

        if (hashed == 2)
        {
            hashed = xor;
        }
        else
        {
            hashed = (hashed << 1) | xor;
        }
    }

    return hashed;
};