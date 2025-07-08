#ifndef LIB_H
#define LIB_H


typedef struct MateriaPrima{
  char *nome;
  float preco;
  int codigo;
  struct MateriaPrima *esq, *dir;
} MatPrima;

typedef MateriaProduto{
  int codigo_mat;
  int qtde;
  struct MateriaProduto *prox, *ant;
} MatProduto;

typedef struct TProduto{
  char *nome;
  int codigo;
  float margemLucro;
  struct TProduto *prox, ant*;
  struct MatProduto *ini_mat;
} Produto;

// protótipos

// leitura e escrita de arquivos
// abrir para leitura, ler sem escrever, escrever em aqr (a partir de uma DLL ou arvore), fechar 

// implementação e manipulação de lista duplamente encadeada
// criar no, inserir no inicio/fim, percorrer, excluir...

// implementação e manipulação de arvore AVL
// inserções, rotações, percurso, excluir...

// funçoes para a lista de produtos, incluem produtos.csv e dll.c
// inserir, excluir e alterar, salvar modificações no arquivo, listar todos, consultar por nome/codigo   

// funções para a lista de matéria prima, incluem matPrima.csv e tree.c
// inserir, excluir e alterar, salvar modificações no arquivo, listar todos, consultar por nome/codigo   

// utilitários
// menu, limpar tela, obter opcao, handler da opcao, etc

#endif
