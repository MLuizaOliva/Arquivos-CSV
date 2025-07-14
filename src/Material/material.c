#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "material.h"
#include "../Utils/utils.h"
#include "../Produto/produto.h"
#include "../Arquivos/arquivo.h"

// ==================== Funções auxiliares internas ====================
//             (Declarações internas não expostas no header)
static MatPrima* criarNoMateria(int codigo, const char *nome, float preco);
static MatPrima* minimoSubarvore(MatPrima *n);
static MatPrima* removerNo(MatPrima *raiz, int codigo, int *ok);

// ==================== CRUD da Árvore ====================

/* Insere uma nova matéria-prima na árvore. */
MatPrima* inserirMateriaArvore(MatPrima *raiz, MatPrima *nova) {
    if (!raiz) return nova;

    if (nova->codigo < raiz->codigo) {
        raiz->esq = inserirMateriaArvore(raiz->esq, nova);
    } else if (nova->codigo > raiz->codigo) {
        raiz->dir = inserirMateriaArvore(raiz->dir, nova);
    }

    return raiz;
}

/* Busca uma matéria-prima pelo código. */
MatPrima* buscarMateriaPorCodigo(MatPrima *raiz, int codigo) {
    while (raiz) {
        if (codigo == raiz->codigo) return raiz;
        raiz = (codigo < raiz->codigo) ? raiz->esq : raiz->dir;
    }

    return NULL;
}

/* Remove uma matéria-prima pelo código. */
MatPrima* removerMateriaArvore(MatPrima *raiz, int codigo, int *ok) {
    return removerNo(raiz, codigo, ok);
}

// ==================== Operações de alto nível (menu) ====================

/* Lê dados do usuário e cadastra uma nova matéria-prima na memória. */
void cadastrarMaterias(MatPrima **raiz) {
    int codigo;
    char nome[100];
    float preco;

    printf("=== Cadastrar Matéria-Prima ===\n");
    printf("Código: ");       scanf("%d", &codigo);
    limparBuffer();
    printf("Nome:   ");       fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    printf("Preço:  ");       scanf("%f", &preco);

    if (buscarMateriaPorCodigo(*raiz, codigo)) {
        printf("Erro: código %d já existe.\n", codigo);
        return;
    }

    MatPrima *nova = criarNoMateria(codigo, nome, preco);
    *raiz = inserirMateriaArvore(*raiz, nova);

    printf("Matéria-prima cadastrada (memória)!\n");
}

/* Lê código, novo nome e preço, e altera a matéria-prima em memória. */
void alterarMaterias(MatPrima *raiz) {
    int codigo;
    printf("=== Alterar Matéria-Prima ===\nCódigo: ");
    scanf("%d", &codigo);

    MatPrima *m = buscarMateriaPorCodigo(raiz, codigo);
    if (!m) {
        printf("Erro: código não encontrado.\n");
        return;
    }
    limparBuffer();

    char novoNome[100];
    printf("Novo nome (atual: %s): ", m->nome);
    fgets(novoNome, sizeof(novoNome), stdin);
    novoNome[strcspn(novoNome, "\n")] = '\0';

    float novoPreco;
    printf("Novo preço (atual: %.2f): ", m->preco);
    scanf("%f", &novoPreco);

    free(m->nome);
    m->nome  = malloc(strlen(novoNome) + 1);
    if (m->nome) strcpy(m->nome, novoNome);
    m->preco = novoPreco;

    printf("Matéria-prima alterada (memória)!\n");
}

/* Exclui matéria-prima da memória se não estiver vinculada a produtos. */
void excluirMaterias(MatPrima **raiz, Produto **listaProdutos) {
    int codigo;
    printf("=== Excluir Matéria-Prima ===\nCódigo: ");
    scanf("%d", &codigo);

    for (Produto *p = *listaProdutos; p; p = p->prox) {
        for (MatProduto *mp = p->ini_mat; mp; mp = mp->prox) {
            if (mp->codigo_mat == codigo) {
                printf("Erro: matéria-prima usada pelo produto %d (%s).\n", p->codigo, p->nome);
                return;
            }
        }
    }

    int ok = 0;
    *raiz = removerMateriaArvore(*raiz, codigo, &ok);
    if (!ok) {
        printf("Erro: código não encontrado.\n");
        return;
    }

    printf("Matéria-prima removida (memória)!\n");
}

/* Imprime todas as matérias-primas em ordem crescente de código. */
void imprimirMaterias(MatPrima *raiz) {
    if (!raiz) {
        printf("Nenhuma matéria-prima cadastrada.\n");
        return;
    }

    imprimirMaterias(raiz->esq);
    printf("Cód:%3d | %-20s | R$ %6.2f\n",
           raiz->codigo, raiz->nome, raiz->preco);
    imprimirMaterias(raiz->dir);
}

// ==================== Funções auxiliares internas ====================

/* Cria e inicializa um novo nó de matéria-prima. */
static MatPrima* criarNoMateria(int codigo, const char *nome, float preco) {
    MatPrima *m = malloc(sizeof(MatPrima));
    if (!m) return NULL;

    m->codigo = codigo;
    m->nome   = malloc(strlen(nome) + 1);

    if (m->nome) strcpy(m->nome, nome);
    m->preco  = preco;
    m->esq = NULL;
    m->dir = NULL;

    return m;
}

/* Retorna o nó de menor chave na subárvore. */
static MatPrima* minimoSubarvore(MatPrima *n) {
    while (n && n->esq) {
        n = n->esq;
    }

    return n;
}

/* Remove o nó com código dado da árvore (implementação interna). */
static MatPrima* removerNo(MatPrima *raiz, int codigo, int *ok) {
    if (!raiz) return NULL;
    if (codigo < raiz->codigo) {
        raiz->esq = removerNo(raiz->esq, codigo, ok);
    } else if (codigo > raiz->codigo) {
        raiz->dir = removerNo(raiz->dir, codigo, ok);
    } else {
        *ok = 1;

        if (!raiz->esq || !raiz->dir) {
            MatPrima *filho = raiz->esq ? raiz->esq : raiz->dir;
            free(raiz->nome);
            free(raiz);
            return filho;
        }

        MatPrima *suc = minimoSubarvore(raiz->dir);
        free(raiz->nome);
        raiz->codigo = suc->codigo;
        raiz->nome   = malloc(strlen(suc->nome) + 1);
        if (raiz->nome) strcpy(raiz->nome, suc->nome);
        raiz->preco  = suc->preco;
        raiz->dir    = removerNo(raiz->dir, suc->codigo, ok);
    }

    return raiz;
}
