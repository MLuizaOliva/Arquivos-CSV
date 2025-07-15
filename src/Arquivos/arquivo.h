#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Produto/produto.h"
#include "../Material/material.h"

// Definicões de constantes
#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

// Definicões de caminhos dos arquivos CSV
#define ARQUIVO_PRODUTOS "db/produtos.csv"
#define ARQUIVO_MATERIAS_PRIMAS "db/matPrima.csv"
#define ARQUIVO_PRODUTOS_MATERIAS "db/produtos_matPrima.csv"

// Codigos de retorno
#define SUCESSO 0
#define ERRO_ARQUIVO -1
#define ERRO_MEMORIA -2
#define ERRO_FORMATO -3

// Estrutura para armazenar dados temporarios durante a leitura
typedef struct
{
    char **campos;
    int num_campos;
} LinhaCSV;

// FUNcÕES PARA MANIPULAcaO DE ARQUIVOS CSV GENeRICAS
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
 * Libera a memoria alocada para uma linha CSV
 * @param linha: Ponteiro para a estrutura LinhaCSV
 */
void liberar_linha_csv(LinhaCSV *linha);

/**
 * Escreve uma linha no arquivo CSV
 * @param arquivo: Ponteiro para o arquivo CSV
 * @param campos: Array de strings com os campos
 * @param num_campos: Numero de campos
 * @return SUCESSO em caso de sucesso, ERRO_ARQUIVO em caso de erro
 */
int escrever_linha_csv(FILE *arquivo, char **campos, int num_campos);

//------------------------------------------------------//
// FUNcÕES ESPECÍFICAS PARA MATeRIAS-PRIMAS             //
//------------------------------------------------------//

/**
 * Carrega todas as materias-primas do arquivo CSV para uma arvore binaria
 * @param raiz: Ponteiro para a raiz da arvore binaria
 * @return SUCESSO em caso de sucesso, codigo de erro caso contrario
 */
int carregar_materias_primas(MatPrima **raiz);

/**
 * Salva todas as materias-primas da arvore binaria no arquivo CSV
 * @param raiz: Ponteiro para a raiz da arvore binaria
 * @return SUCESSO em caso de sucesso, codigo de erro caso contrario
 */
int salvar_materias_primas(MatPrima *raiz);

/**
 * Adiciona uma materia-prima ao arquivo CSV
 * @param materia: Ponteiro para a materia-prima a ser adicionada
 * @return SUCESSO em caso de sucesso, codigo de erro caso contrario
 */
int adicionar_materia_prima_arquivo(MatPrima *materia);

/**
 * Atualiza uma materia-prima no arquivo CSV
 * @param codigo: ID da materia-prima a ser atualizada
 * @param nova_materia: Ponteiro para os novos dados da materia-prima
 * @return SUCESSO em caso de sucesso, codigo de erro caso contrario
 */
int atualizar_materia_prima_arquivo();

//------------------------------------------------------//
//           FUNcÕES ESPECÍFICAS PARA PRODUTOS          //
//------------------------------------------------------//

/**
 * Carrega todos os produtos do arquivo CSV para uma lista duplamente encadeada
 * @param lista_produtos: Ponteiro para o início da lista de produtos
 * @return SUCESSO em caso de sucesso, codigo de erro caso contrario
 */
int carregar_produtos(Produto **lista_produtos);

/**
 * Salva todos os produtos da lista no arquivo CSV
 * @param lista_produtos: Ponteiro para o início da lista de produtos
 * @return SUCESSO em caso de sucesso, codigo de erro caso contrario
 */
int salvar_produtos(Produto *lista_produtos);

/**
 * Adiciona um produto ao arquivo CSV
 * @param produto: Ponteiro para o produto a ser adicionado
 * @return SUCESSO em caso de sucesso, codigo de erro caso contrario
 */
int adicionar_produto_arquivo(Produto *produto);

// =====================================================
// FUNcÕES PARA RELACIONAMENTO PRODUTO-MATeRIA-PRIMA
// =====================================================

/**
 * Carrega os relacionamentos produto-materia-prima do arquivo CSV
 * @param lista_produtos: Ponteiro para a lista de produtos
 * @return SUCESSO em caso de sucesso, codigo de erro caso contrario
 */
int carregar_produtos_materias(Produto *lista_produtos);

/**
 * Salva os relacionamentos produto-materia-prima no arquivo CSV
 * @param lista_produtos: Ponteiro para a lista de produtos
 * @return SUCESSO em caso de sucesso, codigo de erro caso contrario
 */
int salvar_produtos_materias(Produto *lista_produtos);

/**
 * Adiciona um relacionamento produto-materia-prima ao arquivo CSV
 * @param codigo_produto: ID do produto
 * @param codigo_materia: ID da materia-prima
 * @param quantidade: Quantidade da materia-prima utilizada
 * @return SUCESSO em caso de sucesso, codigo de erro caso contrario
 */
int adicionar_produto_materia_arquivo(int codigo_produto, int codigo_materia, int quantidade);

// =====================================================
// FUNcÕES AUXILIARES
// =====================================================

/**
 * Inicializa o sistema de arquivos (cria arquivos se nao existirem)
 * @return SUCESSO em caso de sucesso, codigo de erro caso contrario
 */
int inicializar_sistema_arquivos();

/**
 * Converte uma string para inteiro com validacao
 * @param str: String a ser convertida
 * @param valor: Ponteiro para armazenar o valor convertido
 * @return SUCESSO em caso de sucesso, ERRO_FORMATO em caso de erro
 */
int string_para_int(const char *str, int *valor);

/**
 * Converte uma string para float com validacao
 * @param str: String a ser convertida
 * @param valor: Ponteiro para armazenar o valor convertido
 * @return SUCESSO em caso de sucesso, ERRO_FORMATO em caso de erro
 */
int string_para_float(const char *str, float *valor);

/**
 * Remove espacos em branco do início e fim de uma string
 * @param str: String a ser processada
 * @return Ponteiro para a string processada
 */
char *trim_string(char *str);

#endif // ARQUIVO_H