# 🧠 Estrutura de Dados 2 – USP

Este projeto reúne 7 ferramentas desenvolvidas para a disciplina de **Algoritmos e Estruturas de Dados II (SCC0502)** na USP – ICMC, implementadas em **linguagem C** e com foco em **recursividade, estruturas de dados clássicas e técnicas de otimização**.

## 🔧 Ferramentas implementadas

- 📐 **ExprEval** – Avaliador recursivo de expressões aritméticas
- 🧭 **SmartBinarySearch** – Busca binária modificada para múltiplas ocorrências
- 📁 **HashUSP** – Tabela hash com chave baseada no número USP
- 🗃️ **HashNome** – Tabela hash com chave baseada no nome do aluno
- 🔁 **BinInsertionSort** – Verificador de anagramas com insertion sort otimizado
- 🏗️ **HanoiSort** – Torres de Hanói com ordenação e rastreamento de carga
- ♟️ **NQueensUnique** – Solução das N Rainhas com simetria eliminada

---

## 📘 Descrição das ferramentas

### 1. 📐 ExprEval – Avaliação de Expressões Recursiva
Dado um vetor com até 6 números inteiros e um valor alvo, tenta encontrar uma expressão (com `+`, `-`, `*`, `/`) que resulte exatamente no alvo.

- Implementado **100% com recursão**, sem laços.
- A divisão só é permitida se for exata.
- Exibe:
  - A primeira expressão válida encontrada.
  - Total de chamadas recursivas realizadas.

### 2. 🧭 SmartBinarySearch – Busca Binária Recursiva para Múltiplas Ocorrências
Realiza busca binária pura (sem loops) em vetores **ordenados ascendente ou descendentemente**, retornando o par `(índice_inicial, índice_final)` para cada valor buscado.

- Funciona com vetores contendo valores repetidos.
- Nenhuma busca linear é usada.

### 3. 📁 HashUSP – Tabela Hash com Número USP
Armazena alunos (USP, nome, curso) com uma **função hash bitwise personalizada** baseada no número USP:

- Reespalhamento quadrático como padrão.
- Reespalhamento duplo se a carga > 70%.
- Redimensionamento automático se carga > 90%.
- Persistência em arquivo `.txt`.

### 4. 🗃️ HashNome – Tabela Hash com Nome
Armazena alunos com o **nome como chave**, utilizando:

- Hash com deslocamentos e rotação à esquerda de bits.
- Colisões tratadas com **listas encadeadas**.
- Exportação/importação por arquivos texto com estrutura legível.

### 5. 🔁 BinInsertionSort – Anagram Checker com Insertion Sort Binário
Verifica se duas palavras são anagramas:

- Usa **Insertion Sort com busca binária** para ordenar caracteres.
- Não diferencia maiúsculas/minúsculas.
- Exibe: `Palavra 1: x – Palavra 2: y – Anagrama? sim/não`

### 6. 🏗️ HanoiSort – Torres de Hanói com Pesos
Versão estendida das Torres de Hanói:

- Ordena os discos por **quicksort** ou **heapsort** (recursivo).
- Rastreia o peso movimentado a cada passo.
- Exibe:
  - Algoritmo usado.
  - Todos os movimentos.
  - Total de movimentos.
  - Carga total movimentada.

### 7. ♟️ NQueensUnique – N Rainhas com Simetrias Eliminadas
Resolve o clássico problema das N rainhas:

- Utiliza **backtracking recursivo**.
- Filtra soluções simétricas (reflexão e rotação).
- Exibe:
  - Soluções únicas.
  - Total de chamadas recursivas.
  - Quantidade final de soluções distintas.

---

## 🛠️ Tecnologias usadas

- Linguagem: **C**
- Compilação: `gcc`
- Bibliotecas: `<stdio.h>`, `<stdlib.h>`, `<string.h>`

---

## ▶️ Execução

Cada ferramenta é executável via linha de comando.  
Se nenhum parâmetro for passado, ela executa testes automáticos para validação.

### Exemplos:

```bash
# ExprEval
./expr1 3,4,2 14

# SmartBinarySearch
./exerc2 8,8,6,5,5,5,3,2,1 desc 5,8,7

# HashUSP
./exerc3 inserir hash.txt 123456,Alex,Engenharia

# HashNome
./exerc4 buscar hash_nome.txt Alex

# Anagram Checker
./exerc5 Pedro poder

# HanoiSort
./exerc6 quick 8 1 5

# NQueensUnique
./exerc7 8
