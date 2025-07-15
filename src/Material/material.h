#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produto Produto;

typedef struct MateriaPrima
{
  char *nome;
  float preco;
  int codigo;
  struct MateriaPrima *esq, *dir;
} MatPrima;

// ==================== CRUD da arvore ====================
MatPrima* buscarMateriaPorCodigo(MatPrima *raiz, int codigo);
MatPrima* inserirMateriaArvore(MatPrima *raiz, MatPrima *nova);
MatPrima* removerMateriaArvore(MatPrima *raiz, int codigo, int *ok);

// ==================== Operacões de alto nível (menu) ====================
void cadastrarMaterias(MatPrima **raiz);
void alterarMaterias(MatPrima *raiz);
void excluirMaterias(MatPrima **raiz, Produto **listaProdutos);
void imprimirMaterias(MatPrima *raiz);

#endif // MATERIAL_H