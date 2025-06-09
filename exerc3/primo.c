#include "primo.h"

int encontrarPrimo(int n)
{
    n = 2 * n + 1;
    while (1)
    {
        int is_prime = 1;
        if (n % 2 == 0 && n != 2)
        {
            is_prime = 0;
        }
        else
        {
            for (int i = 3; i * i <= n; i += 2)
            {
                if (n % i == 0)
                {
                    is_prime = 0;
                    break;
                }
            }
        }
        if (is_prime)
            return n;
        n += 2;
    }
}