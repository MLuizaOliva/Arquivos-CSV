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

int main()
{
  Produto *listaProdutos = NULL;
  MatPrima *arvoreMaterias = NULL;

  exibirMenu(&listaProdutos, &arvoreMaterias);
  return 0;
}