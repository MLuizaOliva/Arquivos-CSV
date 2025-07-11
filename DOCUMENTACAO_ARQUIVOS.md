# DOCUMENTAÇÃO TÉCNICA - SISTEMA DE ARQUIVOS CSV

## VISÃO GERAL

Este módulo implementa um sistema completo de gerenciamento de arquivos CSV para persistência de dados de produtos e matérias-primas. O sistema foi projetado para trabalhar com estruturas de dados específicas (árvores binárias para matérias-primas e listas duplamente encadeadas para produtos) e garantir a sincronização entre memória principal e memória secundária.

## ESTRUTURA DOS ARQUIVOS

### 1. `arquivo.h` - Arquivo de Cabeçalho
Contém todas as definições de funções, constantes e estruturas necessárias para o funcionamento do sistema.

### 2. `arquivo.c` - Implementação
Contém a implementação de todas as funções declaradas no cabeçalho.

### 3. Arquivos CSV de Dados
- `db/matPrima.csv` - Armazena dados das matérias-primas
- `db/produtos.csv` - Armazena dados dos produtos
- `db/produtos_matPrima.csv` - Armazena relacionamentos produto-matéria-prima

## FORMATO DOS ARQUIVOS CSV

### matPrima.csv
```
codigo,nome,preco
1,Farinha de Trigo,2.50
2,Açúcar,3.20
```

### produtos.csv
```
codigo,nome,margemLucro
1,Bolo de Chocolate,0.30
2,Pão Francês,0.25
```

### produtos_matPrima.csv
```
codigo_produto,codigo_materia,quantidade
1,1,500
1,2,200
```

## FUNÇÕES PRINCIPAIS

### Funções Genéricas CSV
- `abrir_arquivo_leitura()` - Abre arquivo para leitura
- `abrir_arquivo_escrita()` - Abre arquivo para escrita
- `ler_linha_csv()` - Lê e parseia uma linha CSV
- `escrever_linha_csv()` - Escreve uma linha CSV
- `liberar_linha_csv()` - Libera memória de linha CSV

### Funções de Matérias-Primas
- `carregar_materias_primas()` - Carrega CSV para árvore binária
- `salvar_materias_primas()` - Salva árvore binária no CSV
- `adicionar_materia_prima_arquivo()` - Adiciona matéria-prima ao CSV
- `atualizar_materia_prima_arquivo()` - Atualiza matéria-prima no CSV
- `remover_materia_prima_arquivo()` - Remove matéria-prima do CSV

### Funções de Produtos
- `carregar_produtos()` - Carrega CSV para lista duplamente encadeada
- `salvar_produtos()` - Salva lista no CSV
- `adicionar_produto_arquivo()` - Adiciona produto ao CSV
- `atualizar_produto_arquivo()` - Atualiza produto no CSV
- `remover_produto_arquivo()` - Remove produto do CSV

### Funções de Relacionamentos
- `carregar_produtos_materias()` - Carrega relacionamentos para estruturas
- `salvar_produtos_materias()` - Salva relacionamentos no CSV
- `adicionar_produto_materia_arquivo()` - Adiciona relacionamento ao CSV
- `remover_produto_materia_arquivo()` - Remove relacionamento do CSV

### Funções Auxiliares
- `inicializar_sistema_arquivos()` - Inicializa sistema de arquivos
- `fazer_backup_arquivos()` - Faz backup dos arquivos
- `validar_integridade_arquivos()` - Valida integridade dos dados
- `string_para_int()` - Converte string para inteiro com validação
- `string_para_float()` - Converte string para float com validação
- `trim_string()` - Remove espaços em branco das strings

## CÓDIGOS DE RETORNO

- `SUCESSO` (0) - Operação realizada com sucesso
- `ERRO_ARQUIVO` (-1) - Erro relacionado ao arquivo (não encontrado, permissão, etc.)
- `ERRO_MEMORIA` (-2) - Erro de alocação de memória
- `ERRO_FORMATO` (-3) - Erro de formato dos dados

## FLUXO DE OPERAÇÕES

### Inicialização do Sistema
```c
1. inicializar_sistema_arquivos()
2. carregar_materias_primas(&raiz_arvore)
3. carregar_produtos(&lista_produtos)
4. carregar_produtos_materias(lista_produtos)
```

### Operações em Tempo Real
```c
// Adicionar nova matéria-prima
adicionar_materia_prima_arquivo(nova_materia);

// Adicionar novo produto
adicionar_produto_arquivo(novo_produto);

// Adicionar relacionamento
adicionar_produto_materia_arquivo(cod_produto, cod_materia, quantidade);
```

### Finalização/Salvamento Completo
```c
1. salvar_materias_primas(raiz_arvore)
2. salvar_produtos(lista_produtos)
3. salvar_produtos_materias(lista_produtos)
```

## CARACTERÍSTICAS TÉCNICAS

### Tratamento de Erros
- Todas as funções retornam códigos de erro padronizados
- Validação de parâmetros de entrada
- Tratamento de erros de memória e arquivo
- Limpeza automática de recursos em caso de erro

### Eficiência
- Leitura e escrita otimizadas para grandes volumes de dados
- Parsing eficiente de linhas CSV
- Gerenciamento inteligente de memória

### Robustez
- Validação de formato de dados
- Tratamento de arquivos corrompidos
- Funcionalidade de backup
- Verificação de integridade

### Compatibilidade
- Padrão CSV RFC 4180
- Compatível com diferentes sistemas operacionais
- Encoding UTF-8 suportado

## INTEGRAÇÃO COM OUTRAS PARTES DO SISTEMA

### Com o Módulo de Produtos
```c
#include "Arquivos/arquivo.h"

// Carregar dados na inicialização
carregar_produtos(&lista_produtos);
carregar_produtos_materias(lista_produtos);

// Salvar após modificações
salvar_produtos(lista_produtos);
salvar_produtos_materias(lista_produtos);
```

### Com o Módulo de Matérias-Primas
```c
#include "Arquivos/arquivo.h"

// Carregar dados na inicialização
carregar_materias_primas(&raiz_arvore);

// Salvar após modificações
salvar_materias_primas(raiz_arvore);
```

### Com o Módulo de Menu
```c
#include "Arquivos/arquivo.h"

// Inicializar sistema no início do programa
if (inicializar_sistema_arquivos() != SUCESSO) {
    printf("Erro ao inicializar sistema de arquivos\n");
    exit(1);
}
```

## EXEMPLO DE USO COMPLETO

```c
#include "Arquivos/arquivo.h"

int main() {
    // 1. Inicializar sistema
    if (inicializar_sistema_arquivos() != SUCESSO) {
        printf("Erro na inicialização\n");
        return -1;
    }
    
    // 2. Carregar dados existentes
    MatPrima* raiz_materias = NULL;
    Produto* lista_produtos = NULL;
    
    carregar_materias_primas(&raiz_materias);
    carregar_produtos(&lista_produtos);
    carregar_produtos_materias(lista_produtos);
    
    // 3. Realizar operações...
    
    // 4. Salvar dados atualizados
    salvar_materias_primas(raiz_materias);
    salvar_produtos(lista_produtos);
    salvar_produtos_materias(lista_produtos);
    
    return 0;
}
```

## CONSIDERAÇÕES DE PERFORMANCE

### Operações Frequentes
- Para operações frequentes de adição/remoção, considere usar as funções de salvamento completo apenas periodicamente
- Use as funções de adição direta ao arquivo para operações individuais

### Grandes Volumes de Dados
- O sistema foi projetado para trabalhar com volumes moderados de dados
- Para grandes volumes, considere implementar paginação ou indexação

### Backup e Recuperação
- Implemente rotinas de backup regulares
- Use a função de validação de integridade após operações críticas

## MANUTENÇÃO E EXTENSIBILIDADE

### Adicionar Novos Campos
1. Atualizar estruturas de dados em `produto.h` e `material.h`
2. Modificar funções de leitura/escrita no módulo de arquivos
3. Atualizar formato dos arquivos CSV
4. Implementar migração de dados

### Adicionar Novos Tipos de Arquivo
1. Definir constantes para novos arquivos
2. Implementar funções específicas seguindo o padrão existente
3. Adicionar ao sistema de inicialização

### Otimizações Futuras
- Implementar cache de dados frequentemente acessados
- Adicionar compressão de arquivos
- Implementar indexação para buscas rápidas
- Adicionar suporte a transações

## DIAGRAMA HIERÁRQUICO DE FUNÇÕES

```
Sistema de Arquivos CSV
├── Inicialização
│   ├── inicializar_sistema_arquivos()
│   ├── fazer_backup_arquivos()
│   └── validar_integridade_arquivos()
├── Operações Genéricas CSV
│   ├── abrir_arquivo_leitura()
│   ├── abrir_arquivo_escrita()
│   ├── fechar_arquivo()
│   ├── ler_linha_csv()
│   ├── liberar_linha_csv()
│   └── escrever_linha_csv()
├── Matérias-Primas
│   ├── carregar_materias_primas()
│   ├── salvar_materias_primas()
│   ├── adicionar_materia_prima_arquivo()
│   ├── atualizar_materia_prima_arquivo()
│   └── remover_materia_prima_arquivo()
├── Produtos
│   ├── carregar_produtos()
│   ├── salvar_produtos()
│   ├── adicionar_produto_arquivo()
│   ├── atualizar_produto_arquivo()
│   └── remover_produto_arquivo()
├── Relacionamentos
│   ├── carregar_produtos_materias()
│   ├── salvar_produtos_materias()
│   ├── adicionar_produto_materia_arquivo()
│   └── remover_produto_materia_arquivo()
└── Utilitários
    ├── string_para_int()
    ├── string_para_float()
    └── trim_string()
```
