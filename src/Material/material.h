#ifndef MATERIAL_H
#define MATERIAL_H

typedef struct MateriaPrima
{
  char *nome;
  float preco;
  int codigo;
  struct MateriaPrima *esq, *dir;
} MatPrima;

#endif
