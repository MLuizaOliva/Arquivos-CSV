#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "material.h"
#include "../Utils/utils.h"
#include "../Produto/produto.h"
#include "../Arquivos/arquivo.h"

// ==================== Funcões auxiliares internas ====================
//             (Declaracões internas nao expostas no header)
static MatPrima *criarNoMateria(int codigo, const char *nome, float preco);
static MatPrima *minimoSubarvore(MatPrima *n);
static MatPrima *removerNo(MatPrima *raiz, int codigo, int *ok);

// ==================== CRUD da arvore ====================

/* Insere uma nova materia-prima na arvore. */
MatPrima *inserirMateriaArvore(MatPrima *raiz, MatPrima *nova)
{
    if (!raiz)
        return nova;

    if (nova->codigo < raiz->codigo)
    {
        raiz->esq = inserirMateriaArvore(raiz->esq, nova);
    }
    else if (nova->codigo > raiz->codigo)
    {
        raiz->dir = inserirMateriaArvore(raiz->dir, nova);
    }

    return raiz;
}

/* Busca uma materia-prima pelo codigo. */
MatPrima *buscarMateriaPorCodigo(MatPrima *raiz, int codigo)
{
    while (raiz)
    {
        if (codigo == raiz->codigo)
            return raiz;
        raiz = (codigo < raiz->codigo) ? raiz->esq : raiz->dir;
    }

    return NULL;
}

/* Remove uma materia-prima pelo codigo. */
MatPrima *removerMateriaArvore(MatPrima *raiz, int codigo, int *ok)
{
    return removerNo(raiz, codigo, ok);
}

// ==================== Operacões de alto nível (menu) ====================

/* Lê dados do usuario e cadastra uma nova materia-prima na memoria. */
void cadastrarMaterias(MatPrima **raiz)
{
    int codigo;
    char nome[100];
    float preco;

    printf("=== Cadastrar Materia-Prima ===\n");
    printf("Codigo: ");
    scanf("%d", &codigo);
    limparBuffer();
    printf("Nome:   ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    printf("Preco:  ");
    scanf("%f", &preco);

    if (buscarMateriaPorCodigo(*raiz, codigo))
    {
        printf("Erro: codigo %d ja existe.\n", codigo);
        return;
    }

    MatPrima *nova = criarNoMateria(codigo, nome, preco);
    *raiz = inserirMateriaArvore(*raiz, nova);

    printf("Materia-prima cadastrada (memoria)!\n");
}

/* Lê codigo, novo nome e preco, e altera a materia-prima em memoria. */
void alterarMaterias(MatPrima *raiz)
{
    int codigo;
    printf("=== Alterar Materia-Prima ===\nCodigo: ");
    scanf("%d", &codigo);

    MatPrima *m = buscarMateriaPorCodigo(raiz, codigo);
    if (!m)
    {
        printf("Erro: codigo nao encontrado.\n");
        return;
    }
    limparBuffer();

    char novoNome[100];
    printf("Novo nome (atual: %s): ", m->nome);
    fgets(novoNome, sizeof(novoNome), stdin);
    novoNome[strcspn(novoNome, "\n")] = '\0';

    float novoPreco;
    printf("Novo preco (atual: %.2f): ", m->preco);
    scanf("%f", &novoPreco);

    free(m->nome);
    m->nome = malloc(strlen(novoNome) + 1);
    if (m->nome)
        strcpy(m->nome, novoNome);
    m->preco = novoPreco;

    printf("Materia-prima alterada (memoria)!\n");
}

/* Exclui materia-prima da memoria se nao estiver vinculada a produtos. */
void excluirMaterias(MatPrima **raiz, Produto **listaProdutos)
{
    int codigo;
    printf("=== Excluir Materia-Prima ===\nCodigo: ");
    scanf("%d", &codigo);

    for (Produto *p = *listaProdutos; p; p = p->prox)
    {
        for (MatProduto *mp = p->ini_mat; mp; mp = mp->prox)
        {
            if (mp->codigo_mat == codigo)
            {
                printf("Erro: materia-prima usada pelo produto %d (%s).\n", p->codigo, p->nome);
                return;
            }
        }
    }

    int ok = 0;
    *raiz = removerMateriaArvore(*raiz, codigo, &ok);
    if (!ok)
    {
        printf("Erro: codigo nao encontrado.\n");
        return;
    }

    printf("Materia-prima removida (memoria)!\n");
}

/* Imprime todas as materias-primas em ordem crescente de codigo. */
void imprimirMaterias(MatPrima *raiz)
{
    if (!raiz)
    {
        return;
    }

    imprimirMaterias(raiz->esq);
    printf("Cod:%3d | %-20s | R$ %6.2f\n",
           raiz->codigo, raiz->nome, raiz->preco);
    imprimirMaterias(raiz->dir);
}

void imprimirTodasMaterias(MatPrima *raiz)
{
    if (!raiz)
    {
        printf("Nenhuma materia-prima cadastrada.\n");
        return;
    }
    imprimirMaterias(raiz);
}

// ==================== Funcões auxiliares internas ====================

/* Cria e inicializa um novo no de materia-prima. */
static MatPrima *criarNoMateria(int codigo, const char *nome, float preco)
{
    MatPrima *m = malloc(sizeof(MatPrima));
    if (!m)
        return NULL;

    m->codigo = codigo;
    m->nome = malloc(strlen(nome) + 1);

    if (m->nome)
        strcpy(m->nome, nome);
    m->preco = preco;
    m->esq = NULL;
    m->dir = NULL;

    return m;
}

/* Retorna o no de menor chave na subarvore. */
static MatPrima *minimoSubarvore(MatPrima *n)
{
    while (n && n->esq)
    {
        n = n->esq;
    }

    return n;
}

/* Remove o no com codigo dado da arvore (implementacao interna). */
static MatPrima *removerNo(MatPrima *raiz, int codigo, int *ok)
{
    if (!raiz)
        return NULL;
    if (codigo < raiz->codigo)
    {
        raiz->esq = removerNo(raiz->esq, codigo, ok);
    }
    else if (codigo > raiz->codigo)
    {
        raiz->dir = removerNo(raiz->dir, codigo, ok);
    }
    else
    {
        *ok = 1;

        if (!raiz->esq || !raiz->dir)
        {
            MatPrima *filho = raiz->esq ? raiz->esq : raiz->dir;
            free(raiz->nome);
            free(raiz);
            return filho;
        }

        MatPrima *suc = minimoSubarvore(raiz->dir);
        free(raiz->nome);
        raiz->codigo = suc->codigo;
        raiz->nome = malloc(strlen(suc->nome) + 1);
        if (raiz->nome)
            strcpy(raiz->nome, suc->nome);
        raiz->preco = suc->preco;
        raiz->dir = removerNo(raiz->dir, suc->codigo, ok);
    }

    return raiz;
}
