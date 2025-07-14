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

// Cria um novo produto com nome, codigo e margem
Produto *criarProduto(const char *nome, int codigo, float margem);

// Funcao para cadastrar um produto
void cadastrarProduto(Produto **lista);

// Insere produto na lista duplamente encadeada
void inserirProduto(Produto **lista, Produto *novo);

// Exclui um produto da lista por codigo
void excluirProduto(Produto **lista, int codigo);

// Altera os dados de um produto (nome, margem e materias-primas)
void alterarProduto(Produto *produto);

// Busca um produto por codigo
Produto *buscarProdutoPorCodigo(Produto *lista, int codigo);

// Lista todos os produtos com suas materias-primas
void listarProdutos(Produto *lista, MatPrima *arvoreMaterias);

// Calcula e exibe o preco de um produto (custo + lucro)
void calcularPrecoProduto(Produto *lista, MatPrima *arvoreMaterias);

// ==================== CRUD da lista de materias de um produto ====================

// Cria uma nova ligacao entre um produto e uma materia-prima
MatProduto *criarMateriaProduto(int codigo_mat, int qtde);

// Insere uma materia-prima na lista de um produto
void inserirMateriaProduto(MatProduto **lista, MatProduto *nova);

// Remove uma materia-prima da composicao do produto
void removerMateriaProduto(MatProduto **lista, int codigo_mat);

// Lista as materias-primas de um produto (com nome e quantidade)
void listarMateriasDeProduto(MatProduto *lista, MatPrima *arvoreMaterias);

#endif
