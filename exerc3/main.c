#include "criar.h"
#include "inserir.h"
#include "hashing.h"
#include "buscar.h"
#include "remover.h"

// Recebe argumentos do terminal, dependendo do comando realiza função diferente
int main(int argc, char *argv[])
{
  char *command = argv[1], args[2048];

  args[0] = '\0';

  // Assegurar que todos os argumentos sejam lidos dentro de uma única string
  if (argc > 4)
  {
    for (int i = 3; i < argc; i++)
    {
      strcat(args, argv[i]);
      strcat(args, " ");
    }
  }
  else
  {
    strcpy(args, argv[3]);
  }
  

  if (strcmp(command, "criar") == 0)
  {
    int size = atoi(argv[2]);
    char *path = argv[3];

    criar(size, path);
  }
  else if (strcmp(command, "inserir") == 0)
  {
    char *path = argv[2];

    inserir(path, args);
  }
  else if (strcmp(command, "buscar") == 0)
  {
    buscar(argc, argv);
  }
  else if (strcmp(command, "remover") == 0)
  {
    remover(argc, argv);
  }
  else
  {
    printf("Comando inválido. Use 'criar', 'inserir', 'buscar' ou 'remover'.\n");
    return 0;
  }
}
