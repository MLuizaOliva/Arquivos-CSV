#include <string.h>
#include "arquivo.h"

// =====================================================
// FUNCOES PARA MANIPULACAO DE ARQUIVOS CSV GENERICAS
// =====================================================

FILE *abrir_arquivo_leitura(const char *caminho_arquivo)
{
    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (!arquivo)
    {
        printf("Erro: Nao foi possivel abrir o arquivo %s para leitura.\n", caminho_arquivo);
        return NULL;
    }
    return arquivo;
}

FILE *abrir_arquivo_escrita(const char *caminho_arquivo)
{
    FILE *arquivo = fopen(caminho_arquivo, "w");
    if (!arquivo)
    {
        printf("Erro: Nao foi possivel abrir o arquivo %s para escrita.\n", caminho_arquivo);
        return NULL;
    }
    return arquivo;
}

void fechar_arquivo(FILE *arquivo)
{
    if (arquivo)
    {
        fclose(arquivo);
    }
}

int ler_linha_csv(FILE *arquivo, LinhaCSV *linha)
{
    if (!arquivo || !linha)
    {
        return ERRO_ARQUIVO;
    }

    char buffer[MAX_LINE_LENGTH];
    if (!fgets(buffer, MAX_LINE_LENGTH, arquivo))
    {
        return ERRO_ARQUIVO;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    int num_campos = 1;
    for (int i = 0; buffer[i]; i++)
    {
        if (buffer[i] == ',')
        {
            num_campos++;
        }
    }

    linha->campos = (char **)malloc(num_campos * sizeof(char *));
    if (!linha->campos)
    {
        return ERRO_MEMORIA;
    }

    linha->num_campos = num_campos;

    char *token = strtok(buffer, ",");
    int i = 0;
    while (token && i < num_campos)
    {
        linha->campos[i] = (char *)malloc((strlen(token) + 1) * sizeof(char));
        if (!linha->campos[i])
        {
            for (int j = 0; j < i; j++)
            {
                free(linha->campos[j]);
            }
            free(linha->campos);
            return ERRO_MEMORIA;
        }
        strcpy(linha->campos[i], trim_string(token));
        token = strtok(NULL, ",");
        i++;
    }

    return SUCESSO;
}

void liberar_linha_csv(LinhaCSV *linha)
{
    if (!linha || !linha->campos)
    {
        return;
    }

    for (int i = 0; i < linha->num_campos; i++)
    {
        if (linha->campos[i])
        {
            free(linha->campos[i]);
        }
    }
    free(linha->campos);
    linha->campos = NULL;
    linha->num_campos = 0;
}

int escrever_linha_csv(FILE *arquivo, char **campos, int num_campos)
{
    if (!arquivo || !campos || num_campos <= 0)
    {
        return ERRO_ARQUIVO;
    }

    for (int i = 0; i < num_campos; i++)
    {
        if (i > 0)
        {
            fprintf(arquivo, ",");
        }
        fprintf(arquivo, "%s", campos[i] ? campos[i] : "");
    }
    fprintf(arquivo, "\n");

    return SUCESSO;
}

// =====================================================
// FUNCOES ESPECIFICAS PARA MATERIAS-PRIMAS
// =====================================================

MatPrima *inserir_materia_arvore(MatPrima *raiz, MatPrima *nova_materia)
{
    if (!raiz)
    {
        return nova_materia;
    }

    if (nova_materia->codigo < raiz->codigo)
    {
        raiz->esq = inserir_materia_arvore(raiz->esq, nova_materia);
    }
    else if (nova_materia->codigo > raiz->codigo)
    {
        raiz->dir = inserir_materia_arvore(raiz->dir, nova_materia);
    }

    return raiz;
}

int carregar_materias_primas(MatPrima **raiz)
{
    FILE *arquivo = abrir_arquivo_leitura(ARQUIVO_MATERIAS_PRIMAS);
    if (!arquivo)
    {
        return ERRO_ARQUIVO;
    }

    LinhaCSV linha;
    int resultado = SUCESSO;

    while (ler_linha_csv(arquivo, &linha) == SUCESSO)
    {
        if (linha.num_campos >= 3)
        {
            MatPrima *nova_materia = (MatPrima *)malloc(sizeof(MatPrima));
            if (!nova_materia)
            {
                resultado = ERRO_MEMORIA;
                liberar_linha_csv(&linha);
                break;
            }

            nova_materia->esq = NULL;
            nova_materia->dir = NULL;

            if (string_para_int(linha.campos[0], &nova_materia->codigo) != SUCESSO ||
                string_para_float(linha.campos[2], &nova_materia->preco) != SUCESSO)
            {
                free(nova_materia);
                resultado = ERRO_FORMATO;
                liberar_linha_csv(&linha);
                break;
            }

            nova_materia->nome = (char *)malloc((strlen(linha.campos[1]) + 1) * sizeof(char));
            if (!nova_materia->nome)
            {
                free(nova_materia);
                resultado = ERRO_MEMORIA;
                liberar_linha_csv(&linha);
                break;
            }
            strcpy(nova_materia->nome, linha.campos[1]);

            *raiz = inserir_materia_arvore(*raiz, nova_materia);
        }

        liberar_linha_csv(&linha);
    }

    fechar_arquivo(arquivo);
    return resultado;
}

void salvar_materias_em_ordem(FILE *arquivo, MatPrima *raiz)
{
    if (!raiz)
    {
        return;
    }

    salvar_materias_em_ordem(arquivo, raiz->esq);

    char codigo_str[20], preco_str[20];
    sprintf(codigo_str, "%d", raiz->codigo);
    sprintf(preco_str, "%.2f", raiz->preco);

    char *campos[] = {codigo_str, raiz->nome, preco_str};
    escrever_linha_csv(arquivo, campos, 3);

    salvar_materias_em_ordem(arquivo, raiz->dir);
}

int salvar_materias_primas(MatPrima *raiz)
{
    FILE *arquivo = abrir_arquivo_escrita(ARQUIVO_MATERIAS_PRIMAS);
    if (!arquivo)
    {
        return ERRO_ARQUIVO;
    }

    salvar_materias_em_ordem(arquivo, raiz);

    fechar_arquivo(arquivo);
    return SUCESSO;
}

int adicionar_materia_prima_arquivo(MatPrima *materia)
{
    if (!materia)
    {
        return ERRO_ARQUIVO;
    }

    FILE *arquivo = fopen(ARQUIVO_MATERIAS_PRIMAS, "a");
    if (!arquivo)
    {
        return ERRO_ARQUIVO;
    }

    char codigo_str[20], preco_str[20];
    sprintf(codigo_str, "%d", materia->codigo);
    sprintf(preco_str, "%.2f", materia->preco);

    char *campos[] = {codigo_str, materia->nome, preco_str};
    int resultado = escrever_linha_csv(arquivo, campos, 3);

    fechar_arquivo(arquivo);
    return resultado;
}

int atualizar_materia_prima_arquivo()
{
    MatPrima *raiz = NULL;
    int resultado = carregar_materias_primas(&raiz);
    if (resultado != SUCESSO)
    {
        return resultado;
    }

    resultado = salvar_materias_primas(raiz);

    return resultado;
}

// =====================================================
// FUNCOES ESPECIFICAS PARA PRODUTOS
// =====================================================

int carregar_produtos(Produto **lista_produtos)
{
    FILE *arquivo = abrir_arquivo_leitura(ARQUIVO_PRODUTOS);
    if (!arquivo)
    {
        return ERRO_ARQUIVO;
    }

    LinhaCSV linha;
    int resultado = SUCESSO;
    Produto *ultimo = NULL;

    while (ler_linha_csv(arquivo, &linha) == SUCESSO)
    {
        if (linha.num_campos >= 3)
        {
            Produto *novo_produto = (Produto *)malloc(sizeof(Produto));
            if (!novo_produto)
            {
                resultado = ERRO_MEMORIA;
                liberar_linha_csv(&linha);
                break;
            }

            novo_produto->prox = NULL;
            novo_produto->ant = NULL;
            novo_produto->ini_mat = NULL;

            if (string_para_int(linha.campos[0], &novo_produto->codigo) != SUCESSO ||
                string_para_float(linha.campos[2], &novo_produto->margemLucro) != SUCESSO)
            {
                free(novo_produto);
                resultado = ERRO_FORMATO;
                liberar_linha_csv(&linha);
                break;
            }

            novo_produto->nome = (char *)malloc((strlen(linha.campos[1]) + 1) * sizeof(char));
            if (!novo_produto->nome)
            {
                free(novo_produto);
                resultado = ERRO_MEMORIA;
                liberar_linha_csv(&linha);
                break;
            }
            strcpy(novo_produto->nome, linha.campos[1]);

            if (!*lista_produtos)
            {
                *lista_produtos = novo_produto;
            }
            else
            {
                ultimo->prox = novo_produto;
                novo_produto->ant = ultimo;
            }
            ultimo = novo_produto;
        }

        liberar_linha_csv(&linha);
    }

    fechar_arquivo(arquivo);
    return resultado;
}

int salvar_produtos(Produto *lista_produtos)
{
    FILE *arquivo = abrir_arquivo_escrita(ARQUIVO_PRODUTOS);
    if (!arquivo)
    {
        return ERRO_ARQUIVO;
    }

    Produto *atual = lista_produtos;
    while (atual)
    {
        char codigo_str[20], margem_str[20];
        sprintf(codigo_str, "%d", atual->codigo);
        sprintf(margem_str, "%.2f", atual->margemLucro);

        char *campos[] = {codigo_str, atual->nome, margem_str};
        escrever_linha_csv(arquivo, campos, 3);

        atual = atual->prox;
    }

    fechar_arquivo(arquivo);
    return SUCESSO;
}

int adicionar_produto_arquivo(Produto *produto)
{
    if (!produto)
    {
        return ERRO_ARQUIVO;
    }

    FILE *arquivo = fopen(ARQUIVO_PRODUTOS, "a");
    if (!arquivo)
    {
        return ERRO_ARQUIVO;
    }

    char codigo_str[20], margem_str[20];
    sprintf(codigo_str, "%d", produto->codigo);
    sprintf(margem_str, "%.2f", produto->margemLucro);

    char *campos[] = {codigo_str, produto->nome, margem_str};
    int resultado = escrever_linha_csv(arquivo, campos, 3);

    fechar_arquivo(arquivo);
    return resultado;
}

// =====================================================
// FUNCOES PARA RELACIONAMENTO PRODUTO-MATERIA-PRIMA
// =====================================================

int carregar_produtos_materias(Produto *lista_produtos)
{
    FILE *arquivo = abrir_arquivo_leitura(ARQUIVO_PRODUTOS_MATERIAS);
    if (!arquivo)
    {
        return ERRO_ARQUIVO;
    }

    LinhaCSV linha;
    int resultado = SUCESSO;

    while (ler_linha_csv(arquivo, &linha) == SUCESSO)
    {
        if (linha.num_campos >= 3)
        {
            int codigo_produto, codigo_materia, quantidade;

            if (string_para_int(linha.campos[0], &codigo_produto) != SUCESSO ||
                string_para_int(linha.campos[1], &codigo_materia) != SUCESSO ||
                string_para_int(linha.campos[2], &quantidade) != SUCESSO)
            {
                resultado = ERRO_FORMATO;
                liberar_linha_csv(&linha);
                break;
            }

            Produto *produto_atual = lista_produtos;
            while (produto_atual && produto_atual->codigo != codigo_produto)
            {
                produto_atual = produto_atual->prox;
            }

            if (produto_atual)
            {
                MatProduto *nova_mat = (MatProduto *)malloc(sizeof(MatProduto));
                if (!nova_mat)
                {
                    resultado = ERRO_MEMORIA;
                    liberar_linha_csv(&linha);
                    break;
                }

                nova_mat->codigo_mat = codigo_materia;
                nova_mat->qtde = quantidade;
                nova_mat->prox = NULL;
                nova_mat->ant = NULL;

                if (!produto_atual->ini_mat)
                {
                    produto_atual->ini_mat = nova_mat;
                }
                else
                {
                    MatProduto *ultimo = produto_atual->ini_mat;
                    while (ultimo->prox)
                    {
                        ultimo = ultimo->prox;
                    }
                    ultimo->prox = nova_mat;
                    nova_mat->ant = ultimo;
                }
            }
        }

        liberar_linha_csv(&linha);
    }

    fechar_arquivo(arquivo);
    return resultado;
}

int salvar_produtos_materias(Produto *lista_produtos)
{
    FILE *arquivo = abrir_arquivo_escrita(ARQUIVO_PRODUTOS_MATERIAS);
    if (!arquivo)
    {
        return ERRO_ARQUIVO;
    }

    Produto *produto_atual = lista_produtos;
    while (produto_atual)
    {
        MatProduto *mat_atual = produto_atual->ini_mat;
        while (mat_atual)
        {
            char codigo_produto_str[20], codigo_materia_str[20], quantidade_str[20];
            sprintf(codigo_produto_str, "%d", produto_atual->codigo);
            sprintf(codigo_materia_str, "%d", mat_atual->codigo_mat);
            sprintf(quantidade_str, "%d", mat_atual->qtde);

            char *campos[] = {codigo_produto_str, codigo_materia_str, quantidade_str};
            escrever_linha_csv(arquivo, campos, 3);

            mat_atual = mat_atual->prox;
        }
        produto_atual = produto_atual->prox;
    }

    fechar_arquivo(arquivo);
    return SUCESSO;
}

int adicionar_produto_materia_arquivo(int codigo_produto, int codigo_materia, int quantidade)
{
    FILE *arquivo = fopen(ARQUIVO_PRODUTOS_MATERIAS, "a");
    if (!arquivo)
    {
        return ERRO_ARQUIVO;
    }

    char codigo_produto_str[20], codigo_materia_str[20], quantidade_str[20];
    sprintf(codigo_produto_str, "%d", codigo_produto);
    sprintf(codigo_materia_str, "%d", codigo_materia);
    sprintf(quantidade_str, "%d", quantidade);

    char *campos[] = {codigo_produto_str, codigo_materia_str, quantidade_str};
    int resultado = escrever_linha_csv(arquivo, campos, 3);

    fechar_arquivo(arquivo);
    return resultado;
}

// =====================================================
// FUNCOES AUXILIARES
// =====================================================

int inicializar_sistema_arquivos()
{
    FILE *arquivo;

    arquivo = fopen(ARQUIVO_PRODUTOS, "a");
    if (arquivo)
    {
        fclose(arquivo);
    }

    arquivo = fopen(ARQUIVO_MATERIAS_PRIMAS, "a");
    if (arquivo)
    {
        fclose(arquivo);
    }

    arquivo = fopen(ARQUIVO_PRODUTOS_MATERIAS, "a");
    if (arquivo)
    {
        fclose(arquivo);
    }

    return SUCESSO;
}

int string_para_int(const char *str, int *valor)
{
    if (!str || !valor)
    {
        return ERRO_FORMATO;
    }

    char *endptr;
    long resultado = strtol(str, &endptr, 10);

    if (*endptr != '\0' || endptr == str)
    {
        return ERRO_FORMATO;
    }

    *valor = (int)resultado;
    return SUCESSO;
}

int string_para_float(const char *str, float *valor)
{
    if (!str || !valor)
    {
        return ERRO_FORMATO;
    }

    char *endptr;
    double resultado = strtod(str, &endptr);

    if (*endptr != '\0' || endptr == str)
    {
        return ERRO_FORMATO;
    }

    *valor = (float)resultado;
    return SUCESSO;
}

char *trim_string(char *str)
{
    if (!str)
    {
        return NULL;
    }

    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r')
    {
        str++;
    }

    char *end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r'))
    {
        end--;
    }

    *(end + 1) = '\0';
    return str;
}
