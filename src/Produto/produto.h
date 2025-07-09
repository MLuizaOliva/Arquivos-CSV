#ifndef PRODUTO_H
#define PRODUTO_H

#include "../Material/material.h"

typedef struct MateriaProduto
{
  int codigo_mat;
  int qtde;
  struct MateriaProduto *prox, *ant;
} MatProduto;

typedef struct TProduto
{
  char *nome;
  int codigo;
  float margemLucro;
  struct TProduto *prox, *ant;
  struct MateriaProduto *ini_mat;
} Produto;

#endif
