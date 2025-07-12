/* ================================================================
 *                      GERENCIAMENTO DE PRODUTOS
 * ================================================================
 *
 *  Projeto:     Sistema de cadastro, composição e cálculo de
 *               preço de produtos baseando-se em matérias-primas.
 *
 *  Disciplina:  Estrutura de Dados
 *  Curso:       Ciência da Computação – UESC
 *  Professor:   Edgar Alexander
 *  Ano:         2025
 *
 *  Autores:
 *   - Ariel Pina Ribeiro
 *   - Bruno Gabriel Leite de Matos
 *   - Camilla Matos Araujo
 *   - Henrique Sousa Brito
 *   - Maria Luiza Oliva Santos
 *
 * ================================================================*/

#include <stdio.h>
#include "Menu/menu.h"
#include "Produto/produto.h"
#include "Material/material.h"
#include "Arquivos/arquivo.h"

int main()
{
  Produto *listaProdutos = NULL;
  MatPrima *arvoreMaterias = NULL;

  // Inicializa arquivos (cria se não existir)
  inicializar_sistema_arquivos();

  // Carrega dados dos arquivos
  carregar_materias_primas(&arvoreMaterias);
  carregar_produtos(&listaProdutos);
  carregar_produtos_materias(listaProdutos);

  // Chama o menu principal
  exibirMenu(&listaProdutos, &arvoreMaterias);

  // Salva dados atualizados nos arquivos
  salvar_materias_primas(arvoreMaterias);
  salvar_produtos(listaProdutos);
  salvar_produtos_materias(listaProdutos);

  return 0;
}
