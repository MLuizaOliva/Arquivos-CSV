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

void exibirMenuPrincipal()
{
  printf("1. Produtos\n");
  printf("2. Materias-Primas\n");
  printf("3. Visualizar Preco de Produto\n");
  printf("4. Salvar Alteracoes\n");
  printf("0. Sair\n");
  printf("========================================\n");
  printf("Escolha uma opcao: ");
}

void exibirSubmenuProdutos()
{
  printf("\n--- PRODUTOS ---\n");
  printf("1. Inserir Produto\n");
  printf("2. Excluir Produto\n");
  printf("3. Alterar Produto\n");
  printf("4. Listar Produtos\n");
  printf("0. Voltar ao Menu Principal\n");
  printf("========================================\n");
  printf("Escolha uma opcao: ");
}

void exibirSubmenuMaterias()
{
  printf("\n--- MATERIAS-PRIMAS ---\n");
  printf("1. Inserir Materia-Prima\n");
  printf("2. Excluir Materia-Prima\n");
  printf("3. Alterar Materia-Prima\n");
  printf("4. Listar Materias-Primas\n");
  printf("0. Voltar ao Menu Principal\n");
  printf("========================================\n");
  printf("Escolha uma opcao: ");
}

void menuProdutos(Produto **listaProdutos, MatPrima **arvoreMaterias)
{
  int opcao;
  
  do
  {
    exibirTitle();
    exibirSubmenuProdutos();
    
    while (scanf("%d", &opcao) != 1)
    {
      printf("Entrada invalida! Digite um numero correspondente a opcao: ");
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
      if (*listaProdutos == NULL)
      {
        printf("\nNenhum produto cadastrado para listar.\n");
      }
      else
      {
        listarProdutos(*listaProdutos, *arvoreMaterias);
      }
      break;
      
    case 0:
      printf("\nVoltando ao menu principal...\n");
      break;
      
    default:
      printf("\nOpcao invalida. Tente novamente.\n");
    }
  } while (opcao != 0);
}

void menuMaterias(Produto **listaProdutos, MatPrima **arvoreMaterias)
{
  int opcao;
  
  do
  {
    exibirTitle();
    exibirSubmenuMaterias();
    
    while (scanf("%d", &opcao) != 1)
    {
      printf("Entrada invalida! Digite um numero correspondente a opcao: ");
      limparBuffer();
    }
    
    limparTela();
    
    switch (opcao)
    {
    case 1:
      cadastrarMaterias(arvoreMaterias);
      break;
      
    case 2:
      if (*arvoreMaterias == NULL)
      {
        printf("\nNenhuma materia-prima cadastrada para excluir.\n");
      }
      else
      {
        excluirMaterias(arvoreMaterias, listaProdutos);
      }
      break;
      
    case 3:
      if (*arvoreMaterias == NULL)
      {
        printf("\nNenhuma materia-prima cadastrada para alterar.\n");
      }
      else
      {
        alterarMaterias(*arvoreMaterias);
      }
      break;
      
    case 4:
      if (*arvoreMaterias == NULL)
      {
        printf("\nNenhuma materia-prima cadastrada para listar.\n");
      }
      else
      {
        imprimirMaterias(*arvoreMaterias);
      }
      break;
      
    case 0:
      printf("\nVoltando ao menu principal...\n");
      break;
      
    default:
      printf("\nOpcao invalida. Tente novamente.\n");
    }
  } while (opcao != 0);
}

void exibirMenu(Produto **listaProdutos, MatPrima **arvoreMaterias)
{
  int opcao;

  do
  {
    exibirTitle();
    exibirMenuPrincipal();

    while (scanf("%d", &opcao) != 1)
    {
      printf("Entrada invalida! Digite um numero correspondente a opcao: ");
      limparBuffer();
    }

    limparTela();

    switch (opcao)
    {
    case 1:
      menuProdutos(listaProdutos, arvoreMaterias);
      break;

    case 2:
      menuMaterias(listaProdutos, arvoreMaterias);
      break;

    case 3:
      if (*listaProdutos == NULL)
      {
        printf("\nNenhum produto cadastrado para calcular preco.\n");
      }
      else
      {
        calcularPrecoProduto(*listaProdutos, *arvoreMaterias);
      }
      break;

    case 4:
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