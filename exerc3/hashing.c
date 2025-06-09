#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Gera valor de hash a partir do número USP
unsigned int hashing(int nUSP)
{
    unsigned int altered = nUSP, digito, resultado = 0;

    // Primos utilizados para ponderação dos dígitos
    int primos[8] = {2, 3, 5, 7, 11, 13, 17, 19};

    // Etapa 1: somar 1 a cada dígito e multiplicar por um primo específico
    for (int i = 0; i < 8; i++)
    {
        digito = altered % 10;
        altered /= 10;

        digito = (digito + 1) % 10;

        resultado += digito * primos[7 - i];
    }

    // Etapa 2: inverter os 16 bits mais à esquerda com os 16 bits mais à direita
    unsigned int esquerda = (resultado >> 16) & 0xFFFF;
    unsigned int direita = resultado & 0xFFFF;
    unsigned int invertido = (direita << 16) | esquerda;

    // Etapa 3: aplicar XOR entre bits alternados dos dígitos
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

        // Aplica XOR com bits alternados dos demais dígitos
        for (int i = 1; temp != 0; i++)
        {
            odd = (i % 2);

            if (odd)
                digito = ((temp % 10) >> (3 - j)) & 1;
            else
                digito = ((temp % 10) >> (j)) & 1;

            temp /= 10;
            xor ^= digito;
        }

        // Monta o valor final bit a bit
        if (hashed == 2)
            hashed = xor;
        else
            hashed = (hashed << 1) | xor;
    }

    return hashed;
};
