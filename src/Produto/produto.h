#ifndef PRODUTO_H
#define PRODUTO_H

#include "../Material/material.h"

typedef struct MateriaProduto
{
  int codigo_mat;
  int qtde;
  struct MateriaProduto *prox, *ant;
} MatProduto;

typedef struct Produto
{
  char *nome;
  int codigo;
  float margemLucro;
  struct Produto *prox, *ant;
  struct MateriaProduto *ini_mat;
} Produto;

// ==================== CRUD de Produto ====================

// Cria um novo produto com nome, código e margem
Produto *criarProduto(const char *nome, int codigo, float margem);

// Função para cadastrar um produto
void cadastrarProduto(Produto **lista);

// Insere produto na lista duplamente encadeada
void inserirProduto(Produto **lista, Produto *novo);

// Exclui um produto da lista por código
void excluirProduto(Produto **lista, int codigo);

// Altera os dados de um produto (nome, margem e matérias-primas)
void alterarProduto(Produto *produto);

// Busca um produto por código
Produto *buscarProdutoPorCodigo(Produto *lista, int codigo);

// Lista todos os produtos com suas matérias-primas
void listarProdutos(Produto *lista, MatPrima *arvoreMaterias);

// Calcula e exibe o preço de um produto (custo + lucro)
void calcularPrecoProduto(Produto *lista, MatPrima *arvoreMaterias);

// ==================== CRUD da lista de matérias de um produto ====================

// Cria uma nova ligação entre um produto e uma matéria-prima
MatProduto *criarMateriaProduto(int codigo_mat, int qtde);

// Insere uma matéria-prima na lista de um produto
void inserirMateriaProduto(MatProduto **lista, MatProduto *nova);

// Remove uma matéria-prima da composição do produto
void removerMateriaProduto(MatProduto **lista, int codigo_mat);

// Lista as matérias-primas de um produto (com nome e quantidade)
void listarMateriasDeProduto(MatProduto *lista, MatPrima *arvoreMaterias);

#endif
