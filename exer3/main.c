#include "criar.h"
#include "inserir.h"
#include "hashing.h"
#include "buscar.h"
#include "remover.h"

// Main function
int main(int argc, char *argv[])
{
  char *command = argv[1];

  if (strcmp(command, "criar") == 0)
  {
    int size = atoi(argv[2]);
    char *path = argv[3];

    criar(size, path);
  }
  else if (strcmp(command, "inserir") == 0)
  {
    char *path = argv[2];
    char *data = argv[3];

    inserir(path, data);
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

/*
Exercício 3: Implementação de Tabela Hash para Alunos

Implemente uma tabela hash para armazenar os dados de alunos, em que cada aluno é representado
por uma estrutura com os seguintes campos: número USP, nome e curso.
A chave utilizada pela função hash deve ser baseada no número USP, que é um identificador
numérico único (tipo unsigned int, dentro da struct).

Função Hash:
1. Para cada dígito do número USP:
   - Some 1 ao valor do dígito.
   - Multiplique pelo i-ésimo número primo (i inicia em 1). Ex: 1º dígito * 2, 2º * 3, 3º * 5...
2. Converta o número resultante para 32 bits.
   - Inverta a primeira metade (16 bits mais à esquerda) com a segunda metade (16 bits mais à direita).
3. Realize uma operação XOR entre bits alternados dos dígitos do número:
   - Ex: 1º bit do 1º dígito XOR último bit do 2º dígito XOR 1º bit do 3º dígito XOR ...
4. O valor final da função hash é o número resultante reduzido por `mod m`, onde `m` é o tamanho da tabela.

Requisitos:
- Operações com bits devem ser feitas diretamente com operadores bit a bit em unsigned int.
- O tamanho da tabela deve ser o primeiro número primo ≥ ao valor informado.

Operações suportadas:
- inserir(nusp, nome, curso): insere um aluno na tabela (nusp é a chave).
- buscar(nusp): retorna os dados do aluno com o número USP igual a nusp.

Tratamento de colisões:
1. Iniciar com reespalhamento quadrático.
2. Se taxa de ocupação > 70%:
   - Mudar para reespalhamento duplo:
     h2(x, i) = (h1(x) + i * h3(x)) mod m
     onde h3(x) = 1 + (x mod (m - 1))
   - Todos os elementos devem ser reespalhados na nova estratégia.
3. Se fator de carga > 0.9:
   - Redimensionar tabela para próximo primo > 2 * tamanho atual.
   - Usar reespalhamento quadrático se fator de carga < 0.7, senão, reespalhamento duplo.

Interface via linha de comando:
- main criar <tamanho> <path>
  → Cria a tabela hash e salva no arquivo <path>.txt. Primeira linha = tamanho da tabela.

- main inserir <path> <nusp0>,<nome0>,<curso0>,<nusp1>,<nome1>,<curso1>,...
  → Carrega a tabela do arquivo, insere alunos e salva atualizações.

- main buscar <path> <nusp0>,<nusp1>,...
  → Carrega tabela e imprime dados dos alunos com nUSP correspondente.

- main remover <path> <nusp0>,<nusp1>,...
  → Carrega tabela, remove alunos indicados, marca com lápide e salva a tabela.

Modo de teste automático (sem argumentos):
1. Criar tabela hash com tamanho 11.
2. Inserir 5 alunos.
3. Remover 2 alunos.
4. Salvar tabela em "hash.txt" (raiz do projeto).
5. Carregar "hash.txt" e buscar 2 alunos cadastrados e 1 não cadastrado.

Saída:
- Em criação, inserção e remoção: imprimir mensagem de sucesso ou fracasso.
- Em busca: imprimir dados do aluno correspondente.
*/

/*
 * Teste do algoritmo
 *
 * O algoritmo deve tratar chamadas com parâmetros nos seguintes formatos:
 *
 *  • main criar <tamanho> <path>
 *    - Cria uma tabela hash com o tamanho especificado (conforme descrito anteriormente)
 *      e a salva em um arquivo .txt no path informado.
 *    - A primeira linha desse arquivo informa o tamanho da tabela hash.
 *
 *  • main inserir <path> <nusp0>,<nome0>,<curso0>,<nusp1>,<nome1>,<curso1>,...
 *    - Considera que a tabela hash já existe no path especificado;
 *    - Carrega a tabela na memória;
 *    - Insere os dados dos alunos passados como parâmetro;
 *    - Salva a tabela hash atualizada no path. Cada aluno deve ser registrado em uma linha,
 *      com os campos separados por ponto e vírgula.
 *
 *  • main buscar <path> <nusp0>,<nusp1>,...
 *    - Considera que a tabela hash já existe no path especificado;
 *    - Carrega a tabela na memória;
 *    - Imprime os dados dos alunos cujos N° USP correspondam às chaves informadas como parâmetro.
 *
 *  • main remover <path> <nusp0>,<nusp1>,...
 *    - Considera que a tabela hash já existe no path especificado;
 *    - Carrega a tabela na memória;
 *    - Remove os dados de cada aluno passado como parâmetro que for encontrado na tabela.
 *    - Não se esqueça de criar uma lápide nos registros removidos;
 *    - Salva a tabela hash atualizada no path.
 */
