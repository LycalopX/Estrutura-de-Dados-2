#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "mainFunctions.h"

// ERROR
#define TOO_MANY_ARGUMENTS_MESSAGE "Too many arguments\n"
#define TOO_MANY_ARGUMENTS 1
#define TOO_FEW_ARGUMENTS_MESSAGE "Too few arguments\n"
#define TOO_FEW_ARGUMENTS 2
#define INVALID_INPUT_MESSAGE "Invalid input\n"
#define INVALID_INPUT 3

int main(int argc, char *argv[])
{
    // Validate arguments count
    if(argc > 3){
        fprintf(stderr, TOO_MANY_ARGUMENTS_MESSAGE);
        return TOO_MANY_ARGUMENTS;
    }
    if(argc < 3){
        fprintf(stderr, TOO_FEW_ARGUMENTS_MESSAGE);
        return TOO_FEW_ARGUMENTS;
    }

    // Get inputs and print them
    List *word1 = List_FromWord(argv[1]);
    List *word2 = List_FromWord(argv[2]);
    printf("Palavra 1: ");
    MyPrintList(word1);
    printf(" - Palavra 2: ");
    MyPrintList(word2);


    List_WordToUpperCase(word1);
    List_WordToUpperCase(word2);

    List *orderedWord1 = OrderMethod_InsertionUsingList(word1);
    List *orderedWord2 = OrderMethod_InsertionUsingList(word2);

    printf(" - Anagrama? ");
    int comparisonResult = List_Compare(orderedWord1, orderedWord2);
    if (comparisonResult == 1)
    {
        printf("sim\n");
    }
    else
    {
        printf("não\n");
    }

    List_Destroy(word1);
    List_DestroyWithoutElementsData(orderedWord1);
    List_Destroy(word2);
    List_DestroyWithoutElementsData(orderedWord2);
    return 0;
}