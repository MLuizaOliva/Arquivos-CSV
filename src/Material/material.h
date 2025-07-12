#ifndef MATERIAL_H
#define MATERIAL_H

typedef struct Produto Produto;

typedef struct MateriaPrima
{
  char *nome;
  float preco;
  int codigo;
  struct MateriaPrima *esq, *dir;
} MatPrima;

void cadastrarMaterias(MatPrima **arvoreMaterias);
void excluirMaterias(MatPrima **arvoreMaterias, Produto **listaProdutos);
void alterarMaterias(MatPrima *arvoreMaterias);
void imprimirMaterias(MatPrima *arvoreMaterias);
MatPrima *buscarMateriaPorCodigo(MatPrima *arvoreMaterias, int codigo);

#endif