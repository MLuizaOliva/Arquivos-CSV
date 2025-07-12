#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Utils/utils.h"
#include "../Material/material.h"
#include "produto.h"

/* Cria um novo produto com nome, código e margem de lucro */
Produto *criarProduto(const char *nome, int codigo, float margem)
{
  Produto *novo = (Produto *)malloc(sizeof(Produto));
  if (!novo)
    return NULL;

  novo->nome = strdup(nome);
  novo->codigo = codigo;
  novo->margemLucro = margem;
  novo->prox = NULL;
  novo->ant = NULL;
  novo->ini_mat = NULL;

  return novo;
}

/* Realiza cadastro de um novo produto com dados do usuário */
void cadastrarProduto(Produto **lista, MatPrima *arvoreMaterias)
{
  char nome[100];
  int codigo, qtdeMat, codMat, qtde;
  float margem;

  printf("Nome do produto: ");
  limparBuffer();
  fgets(nome, sizeof(nome), stdin);
  nome[strcspn(nome, "\n")] = '\0';

  printf("Código do produto: ");
  scanf("%d", &codigo);

  printf("Margem de lucro (ex: 0.20 = 20%%): ");
  scanf("%f", &margem);

  Produto *novo = criarProduto(nome, codigo, margem);

  printf("Quantas matérias-primas o produto possui? ");
  scanf("%d", &qtdeMat);

  for (int i = 0; i < qtdeMat; i++)
  {
    printf("Código da matéria-prima #%d: ", i + 1);
    scanf("%d", &codMat);
    printf("Quantidade necessária: ");
    scanf("%d", &qtde);

    MatProduto *mp = criarMateriaProduto(codMat, qtde);
    inserirMateriaProduto(&(novo->ini_mat), mp);
  }

  inserirProduto(lista, novo);

  printf("\nProduto cadastrado com sucesso!\n");
}

/* Altera nome e margem de lucro de um produto existente */
void alterarProduto(Produto *lista, MatPrima *arvoreMaterias)
{
  int codigo;
  printf("Digite o código do produto a alterar: ");
  scanf("%d", &codigo);

  Produto *p = buscarProdutoPorCodigo(lista, codigo);
  if (!p)
  {
    printf("Produto não encontrado.\n");
    return;
  }

  printf("Novo nome do produto: ");
  limparBuffer();
  char novoNome[100];
  fgets(novoNome, sizeof(novoNome), stdin);
  novoNome[strcspn(novoNome, "\n")] = '\0';

  printf("Nova margem de lucro: ");
  scanf("%f", &p->margemLucro);

  free(p->nome);
  p->nome = strdup(novoNome);

  printf("Produto alterado com sucesso!\n");
}

/* Insere um produto no final da lista duplamente encadeada */
void inserirProduto(Produto **lista, Produto *novo)
{
  if (*lista == NULL)
  {
    *lista = novo;
  }
  else
  {
    Produto *atual = *lista;
    while (atual->prox != NULL)
      atual = atual->prox;
    atual->prox = novo;
    novo->ant = atual;
  }
}

/* Remove um produto da lista pelo código */
void excluirProduto(Produto **lista, int codigo)
{
  Produto *atual = *lista;

  while (atual && atual->codigo != codigo)
    atual = atual->prox;

  if (!atual)
    return;

  if (atual->ant)
    atual->ant->prox = atual->prox;
  else
    *lista = atual->prox;

  if (atual->prox)
    atual->prox->ant = atual->ant;

  free(atual->nome);

  MatProduto *mp = atual->ini_mat;
  while (mp)
  {
    MatProduto *tmp = mp;
    mp = mp->prox;
    free(tmp);
  }

  free(atual);
}

/* Busca um produto na lista pelo código */
Produto *buscarProdutoPorCodigo(Produto *lista, int codigo)
{
  while (lista)
  {
    if (lista->codigo == codigo)
      return lista;
    lista = lista->prox;
  }
  return NULL;
}

/* Lista todos os produtos e suas matérias-primas associadas */
void listarProdutos(Produto *lista, MatPrima *arvoreMaterias)
{
  while (lista)
  {
    printf("Produto: %s (Código: %d)\n", lista->nome, lista->codigo);
    printf("Margem de Lucro: %.2f%%\n", lista->margemLucro * 100);
    listarMateriasDeProduto(lista->ini_mat, arvoreMaterias);
    printf("----------------------------------------\n");
    lista = lista->prox;
  }
}

/* Calcula e exibe o preço final de um produto considerando margem e matérias-primas */
void calcularPrecoProduto(Produto *lista, MatPrima *arvoreMaterias)
{
  int codigo;
  printf("Informe o código do produto: ");
  scanf("%d", &codigo);

  Produto *p = buscarProdutoPorCodigo(lista, codigo);
  if (!p)
  {
    printf("Produto não encontrado.\n");
    return;
  }

  float custo = 0.0;
  MatProduto *mp = p->ini_mat;
  while (mp)
  {
    MatPrima *m = buscarMateriaPorCodigo(arvoreMaterias, mp->codigo_mat);
    if (m)
      custo += m->preco * mp->qtde;
    mp = mp->prox;
  }

  float precoFinal = custo * (1 + p->margemLucro);

  printf("Custo do Produto: R$ %.2f\n", custo);
  printf("Preço Final (com lucro): R$ %.2f\n", precoFinal);
}

/* Cria uma nova matéria-prima associada a um produto */
MatProduto *criarMateriaProduto(int codigo_mat, int qtde)
{
  MatProduto *nova = (MatProduto *)malloc(sizeof(MatProduto));
  if (!nova)
    return NULL;

  nova->codigo_mat = codigo_mat;
  nova->qtde = qtde;
  nova->prox = NULL;
  nova->ant = NULL;

  return nova;
}

/* Insere uma matéria-prima na lista encadeada do produto */
void inserirMateriaProduto(MatProduto **lista, MatProduto *nova)
{
  if (*lista == NULL)
  {
    *lista = nova;
  }
  else
  {
    MatProduto *atual = *lista;
    while (atual->prox != NULL)
      atual = atual->prox;
    atual->prox = nova;
    nova->ant = atual;
  }
}

/* Remove uma matéria-prima da lista do produto pelo código */
void removerMateriaProduto(MatProduto **lista, int codigo_mat)
{
  MatProduto *atual = *lista;

  while (atual && atual->codigo_mat != codigo_mat)
    atual = atual->prox;

  if (!atual)
    return;

  if (atual->ant)
    atual->ant->prox = atual->prox;
  else
    *lista = atual->prox;

  if (atual->prox)
    atual->prox->ant = atual->ant;

  free(atual);
}

/* Lista as matérias-primas associadas a um produto, exibindo detalhes */
void listarMateriasDeProduto(MatProduto *lista, MatPrima *arvoreMaterias)
{
  if (lista == NULL)
  {
    printf("Nenhuma matéria-prima vinculada a este produto.\n");
    return;
  }

  printf("Matérias-primas:\n");
  while (lista)
  {
    MatPrima *m = buscarMateriaPorCodigo(arvoreMaterias, lista->codigo_mat);
    if (m)
    {
      printf("- %s (Código %d), Quantidade: %d, Preço unitário: R$ %.2f\n",
             m->nome, m->codigo, lista->qtde, m->preco);
    }
    else
    {
      printf("- Código %d não encontrado na árvore de matérias-primas\n", lista->codigo_mat);
    }
    lista = lista->prox;
  }
}
