#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "../Utils/utils.h"
#include "../Arquivos/arquivo.h"
#include "../Produto/produto.h"
#include "../Material/material.h"

void exibirTitle()
{
  printf("\n========================================\n");
  printf("||                                    ||\n");
  printf("||      GERENCIAMENTO DE PRODUTOS     ||\n");
  printf("||                                    ||\n");
  printf("========================================\n\n");
}

void exibirMenu(Produto **listaProdutos, MatPrima **arvoreMaterias)
{
  int opcao;

  do
  {
    exibirTitle();

    printf("1. Inserir Produto\n");
    printf("2. Excluir Produto\n");
    printf("3. Alterar Produto\n");
    printf("4. Inserir Materia-Prima\n");
    printf("5. Excluir Materia-Prima\n");
    printf("6. Alterar Materia-Prima\n");
    printf("7. Listar Produtos\n");
    printf("8. Listar Materias-Primas\n");
    printf("9. Calcular Preco de Produto\n");
    printf("10. Salvar Alteracoes\n");
    printf("0. Sair\n");
    printf("========================================\n");
    printf("Escolha uma opcao: ");

    while (scanf("%d", &opcao) != 1)
    {
      printf("Entrada invalida! Digite um numero correspondente à opcao: ");
      limparBuffer();
    }

    limparTela();

    switch (opcao)
    {
    case 1:
      if (*arvoreMaterias == NULL)
      {
        printf("\nNenhuma materia-prima cadastrada! Cadastre ao menos uma antes de criar um produto.\n");
      }
      else
      {
        cadastrarProduto(listaProdutos);
      }
      break;

    case 2:
      if (*listaProdutos == NULL)
      {
        printf("\nNenhum produto cadastrado para excluir.\n");
      }
      else
      {
        int codigo;
        printf("Informe o codigo do produto a excluir: ");
        scanf("%d", &codigo);
        excluirProduto(listaProdutos, codigo);
      }
      break;

    case 3:
      if (*listaProdutos == NULL)
      {
        printf("\nNenhum produto cadastrado para alterar.\n");
      }
      else
      {
        alterarProduto(*listaProdutos);
      }
      break;

    case 4:
      cadastrarMaterias(arvoreMaterias);
      break;

    case 5:
      if (*arvoreMaterias == NULL)
      {
        printf("\nNenhuma materia-prima cadastrada para excluir.\n");
      }
      else
      {
        excluirMaterias(arvoreMaterias, listaProdutos);
      }
      break;

    case 6:
      if (*arvoreMaterias == NULL)
      {
        printf("\nNenhuma materia-prima cadastrada para alterar.\n");
      }
      else
      {
        alterarMaterias(*arvoreMaterias);
      }
      break;

    case 7:
      if (*listaProdutos == NULL)
      {
        printf("\nNenhum produto cadastrado para listar.\n");
      }
      else
      {
        listarProdutos(*listaProdutos, *arvoreMaterias);
      }
      break;

    case 8:
      if (*arvoreMaterias == NULL)
      {
        printf("\nNenhuma materia-prima cadastrada para listar.\n");
      }
      else
      {
        imprimirMaterias(*arvoreMaterias);
      }
      break;

    case 9:
      if (*listaProdutos == NULL)
      {
        printf("\nNenhum produto cadastrado para calcular preco.\n");
      }
      else
      {
        calcularPrecoProduto(*listaProdutos, *arvoreMaterias);
      }
      break;

    case 10:
      salvar_produtos(*listaProdutos);
      salvar_materias_primas(*arvoreMaterias);
      salvar_produtos_materias(*listaProdutos);
      printf("\nDados salvos com sucesso!\n");
      break;

    case 0:
      printf("\nEncerrando o programa...\n");
      break;

    default:
      printf("\nOpcao invalida. Tente novamente.\n");
    }
  } while (opcao != 0);
}
