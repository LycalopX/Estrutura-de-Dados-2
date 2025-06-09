#include "heap.h"
#include "swap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

A Max heap is typically represented as an array.

The root element will be at Arr[0].
For any ith node Arr[i].
left child is stored at index 2i+1
Right child is stored at index 2i+2
Parent is stored at index floor((i-1)/2)

*/

void heapify(int arr[], int n, int i)
{
    int smallest = i; // Inicializar o menor como raiz

    // Para compreender seus "galhos"
    int left = 2 * i + 1;  // Esquerda = 2*i + 1
    int right = 2 * i + 2; // Direita = 2*i + 2

    // n é usado como limite para evitar acessar fora do array

    // Se o filho esquerdo for menor que a raiz
    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    // Se o filho direito for menor que o menor até agora
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    // Se o menor não for a raiz
    if (smallest != i)
    {
        swap(&arr[i], &arr[smallest]); // Trocar a raiz com o maior

        // Recursivamente heapify a subárvore afetada
        heapify(arr, n, smallest);
    }
}

void heapSort(int arr[], int n)
{

    // Construir o heap (rearranjar o array)
    // Assume-se que i é o índice da raiz mais baixa, por meio do valor de n
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    // Retirar elementos do heap
    for (int i = n - 1; i >= 0; i--)
    {
        swap(&arr[0], &arr[i]); // Mover a raiz para o final

        // Call heapify
        heapify(arr, i, 0);
    }
}
