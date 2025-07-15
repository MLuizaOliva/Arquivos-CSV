#ifndef ARQUIVO_H
#define ARQUIVO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Produto/produto.h"
#include "../Material/material.h"
#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256
#define ARQUIVO_PRODUTOS "db/produtos.csv"
#define ARQUIVO_MATERIAS_PRIMAS "db/matPrima.csv"
#define ARQUIVO_PRODUTOS_MATERIAS "db/produtos_matPrima.csv"
#define SUCESSO 0
#define ERRO_ARQUIVO -1
#define ERRO_MEMORIA -2
#define ERRO_FORMATO -3

typedef struct
{
    char **campos;
    int num_campos;
} LinhaCSV;

FILE *abrir_arquivo_leitura(const char *caminho_arquivo);

FILE *abrir_arquivo_escrita(const char *caminho_arquivo);

void fechar_arquivo(FILE *arquivo);

int ler_linha_csv(FILE *arquivo, LinhaCSV *linha);

void liberar_linha_csv(LinhaCSV *linha);

int escrever_linha_csv(FILE *arquivo, char **campos, int num_campos);

// Funções para matérias-primas
int carregar_materias_primas(MatPrima **raiz);
int salvar_materias_primas(MatPrima *raiz);
int adicionar_materia_prima_arquivo(MatPrima *materia);
int atualizar_materia_prima_arquivo();

// Funções para produtos
int carregar_produtos(Produto **lista_produtos);
int salvar_produtos(Produto *lista_produtos);
int adicionar_produto_arquivo(Produto *produto);

// Funções para relacionamento produto-matéria-prima
int carregar_produtos_materias(Produto *lista_produtos);
int salvar_produtos_materias(Produto *lista_produtos);
int adicionar_produto_materia_arquivo(int codigo_produto, int codigo_materia, int quantidade);

// Funções auxiliares
int inicializar_sistema_arquivos();

int string_para_int(const char *str, int *valor);

int string_para_float(const char *str, float *valor);

char *trim_string(char *str);

#endif 