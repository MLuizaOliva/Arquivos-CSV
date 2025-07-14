#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Produto/produto.h"
#include "../Material/material.h"

// Definições de constantes
#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

// Definições de caminhos dos arquivos CSV
#define ARQUIVO_PRODUTOS "db/produtos.csv"
#define ARQUIVO_MATERIAS_PRIMAS "db/matPrima.csv"
#define ARQUIVO_PRODUTOS_MATERIAS "db/produtos_matPrima.csv"

// Códigos de retorno
#define SUCESSO 0
#define ERRO_ARQUIVO -1
#define ERRO_MEMORIA -2
#define ERRO_FORMATO -3

// Estrutura para armazenar dados temporários durante a leitura
typedef struct
{
    char **campos;
    int num_campos;
} LinhaCSV;

// FUNÇÕES PARA MANIPULAÇÃO DE ARQUIVOS CSV GENÉRICAS
//----------------------------------------------------

/**
 * Abre um arquivo CSV para leitura
 * @param caminho_arquivo: Caminho para o arquivo CSV
 * @return Ponteiro para FILE ou NULL em caso de erro
 */
FILE *abrir_arquivo_leitura(const char *caminho_arquivo);

/**
 * Abre um arquivo CSV para escrita
 * @param caminho_arquivo: Caminho para o arquivo CSV
 * @return Ponteiro para FILE ou NULL em caso de erro
 */
FILE *abrir_arquivo_escrita(const char *caminho_arquivo);

/**
 * Fecha um arquivo CSV
 * @param arquivo: Ponteiro para o arquivo a ser fechado
 */
void fechar_arquivo(FILE *arquivo);

/**
 * Lê uma linha do arquivo CSV e separa os campos
 * @param arquivo: Ponteiro para o arquivo CSV
 * @param linha: Estrutura para armazenar os campos da linha
 * @return SUCESSO se leu com sucesso, ERRO_ARQUIVO se chegou ao fim do arquivo
 */
int ler_linha_csv(FILE *arquivo, LinhaCSV *linha);

/**
 * Libera a memória alocada para uma linha CSV
 * @param linha: Ponteiro para a estrutura LinhaCSV
 */
void liberar_linha_csv(LinhaCSV *linha);

/**
 * Escreve uma linha no arquivo CSV
 * @param arquivo: Ponteiro para o arquivo CSV
 * @param campos: Array de strings com os campos
 * @param num_campos: Número de campos
 * @return SUCESSO em caso de sucesso, ERRO_ARQUIVO em caso de erro
 */
int escrever_linha_csv(FILE *arquivo, char **campos, int num_campos);

//------------------------------------------------------//
// FUNÇÕES ESPECÍFICAS PARA MATÉRIAS-PRIMAS             //
//------------------------------------------------------//

/**
 * Carrega todas as matérias-primas do arquivo CSV para uma árvore binária
 * @param raiz: Ponteiro para a raiz da árvore binária
 * @return SUCESSO em caso de sucesso, código de erro caso contrário
 */
int carregar_materias_primas(MatPrima **raiz);

/**
 * Salva todas as matérias-primas da árvore binária no arquivo CSV
 * @param raiz: Ponteiro para a raiz da árvore binária
 * @return SUCESSO em caso de sucesso, código de erro caso contrário
 */
int salvar_materias_primas(MatPrima *raiz);

/**
 * Adiciona uma matéria-prima ao arquivo CSV
 * @param materia: Ponteiro para a matéria-prima a ser adicionada
 * @return SUCESSO em caso de sucesso, código de erro caso contrário
 */
int adicionar_materia_prima_arquivo(MatPrima *materia);

/**
 * Atualiza uma matéria-prima no arquivo CSV
 * @param codigo: Código da matéria-prima a ser atualizada
 * @param nova_materia: Ponteiro para os novos dados da matéria-prima
 * @return SUCESSO em caso de sucesso, código de erro caso contrário
 */
int atualizar_materia_prima_arquivo();

//------------------------------------------------------//
//           FUNÇÕES ESPECÍFICAS PARA PRODUTOS          //
//------------------------------------------------------//

/**
 * Carrega todos os produtos do arquivo CSV para uma lista duplamente encadeada
 * @param lista_produtos: Ponteiro para o início da lista de produtos
 * @return SUCESSO em caso de sucesso, código de erro caso contrário
 */
int carregar_produtos(Produto **lista_produtos);

/**
 * Salva todos os produtos da lista no arquivo CSV
 * @param lista_produtos: Ponteiro para o início da lista de produtos
 * @return SUCESSO em caso de sucesso, código de erro caso contrário
 */
int salvar_produtos(Produto *lista_produtos);

/**
 * Adiciona um produto ao arquivo CSV
 * @param produto: Ponteiro para o produto a ser adicionado
 * @return SUCESSO em caso de sucesso, código de erro caso contrário
 */
int adicionar_produto_arquivo(Produto *produto);

// =====================================================
// FUNÇÕES PARA RELACIONAMENTO PRODUTO-MATÉRIA-PRIMA
// =====================================================

/**
 * Carrega os relacionamentos produto-matéria-prima do arquivo CSV
 * @param lista_produtos: Ponteiro para a lista de produtos
 * @return SUCESSO em caso de sucesso, código de erro caso contrário
 */
int carregar_produtos_materias(Produto *lista_produtos);

/**
 * Salva os relacionamentos produto-matéria-prima no arquivo CSV
 * @param lista_produtos: Ponteiro para a lista de produtos
 * @return SUCESSO em caso de sucesso, código de erro caso contrário
 */
int salvar_produtos_materias(Produto *lista_produtos);

/**
 * Adiciona um relacionamento produto-matéria-prima ao arquivo CSV
 * @param codigo_produto: Código do produto
 * @param codigo_materia: Código da matéria-prima
 * @param quantidade: Quantidade da matéria-prima utilizada
 * @return SUCESSO em caso de sucesso, código de erro caso contrário
 */
int adicionar_produto_materia_arquivo(int codigo_produto, int codigo_materia, int quantidade);

// =====================================================
// FUNÇÕES AUXILIARES
// =====================================================

/**
 * Inicializa o sistema de arquivos (cria arquivos se não existirem)
 * @return SUCESSO em caso de sucesso, código de erro caso contrário
 */
int inicializar_sistema_arquivos();

/**
 * Converte uma string para inteiro com validação
 * @param str: String a ser convertida
 * @param valor: Ponteiro para armazenar o valor convertido
 * @return SUCESSO em caso de sucesso, ERRO_FORMATO em caso de erro
 */
int string_para_int(const char *str, int *valor);

/**
 * Converte uma string para float com validação
 * @param str: String a ser convertida
 * @param valor: Ponteiro para armazenar o valor convertido
 * @return SUCESSO em caso de sucesso, ERRO_FORMATO em caso de erro
 */
int string_para_float(const char *str, float *valor);

/**
 * Remove espaços em branco do início e fim de uma string
 * @param str: String a ser processada
 * @return Ponteiro para a string processada
 */
char *trim_string(char *str);

#endif // ARQUIVO_H