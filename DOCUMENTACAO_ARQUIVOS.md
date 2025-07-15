# DOCUMENTAÇÃO TÉCNICA - SISTEMA DE ARQUIVOS CSV

## VISÃO GERAL

Este módulo implementa um sistema completo de gerenciamento de arquivos CSV para persistência de dados de produtos e matérias-primas. O sistema foi projetado para trabalhar com estruturas de dados específicas (árvores binárias para matérias-primas e listas duplamente encadeadas para produtos) e garantir a sincronização entre memória principal e memória secundária.

## DIAGRAMA HIERÁRQUICO DE FUNÇÕES

```
Sistema
 ├── main()
 │   └── exibir_menu_principal()                    → Menu principal do sistema
 │       ├── menu_materias()                        → Menu para gerenciar matérias-primas
 │       │   ├── cadastrarMaterias()                → Lê dados e insere nova matéria-prima
 │       │   │   └── inserirMateriaArvore()         → Insere na árvore binária
 │       │   │       └── criarNoMateria()           → Cria novo nó de matéria
 │       │   ├── alterarMaterias()                  → Altera nome ou preço de matéria
 │       │   ├── excluirMaterias()                  → Remove matéria-prima da árvore
 │       │   │   └── removerMateriaArvore()         → Inicia remoção na árvore
 │       │   │       └── removerNo()                → Remove nó e reorganiza árvore
 │       │   │           └── minimoSubarvore()      → Busca menor valor da subárvore
 │       │   └── imprimirTodasMaterias()            → Lista todas as matérias ordenadas
 │       │       └── imprimirMaterias()             → Impressão em ordem
 │       │
 │       ├── menu_produtos()                        → Menu para gerenciar produtos
 │       │   ├── cadastrarProduto()                 → Cria produto com nome/código/margem
 │       │   │   ├── criarProduto()                 → Aloca struct de produto
 │       │   │   └── inserirProduto()               → Insere na lista duplamente encadeada
 │       │   ├── alterarProduto()                   → Altera nome/margem e matérias-primas
 │       │   ├── excluirProduto()                   → Remove produto da lista
 │       │   ├── listarProdutos()                   → Lista produtos e suas matérias
 │       │   │   └── listarMateriasDeProduto()      → Lista matérias de um produto
 │       │   └── calcularPrecoProduto()             → Calcula custo + margem de lucro
 │       │       └── buscarProdutoPorCodigo()       → Busca produto na lista
 │       │
 │       └── menu_relacionamentos()                 → Menu de vínculos produto ↔ matéria
 │           ├── inserirMateriaProduto()            → Insere nova matéria ao produto
 │           │   └── criarMateriaProduto()          → Cria struct de ligação com quantidade
 │           ├── removerMateriaProduto()            → Remove matéria de um produto
 │           └── listarMateriasDeProduto()          → Exibe as matérias vinculadas
 │
 ├── inicializar_sistema_arquivos()                 → Carrega dados dos arquivos CSV
 │   ├── carregar_materias_primas()                 → Lê matérias do CSV
 │   │   └── inserirMateriaArvore()
 │   ├── carregar_produtos()                        → Lê produtos do CSV
 │   │   └── inserirProduto()
 │   ├── carregar_produtos_materias()               → Lê vínculos produto ↔ matéria
 │   │   └── inserirMateriaProduto()
 │   └── abrir_arquivo_leitura()                    → Abre arquivo CSV em modo leitura
 │       └── ler_linha_csv()                        → Lê e separa valores da linha CSV
 │           └── liberar_linha_csv()                → Libera memória da linha CSV
 │
 ├── salvar_materias_primas()                       → Grava todas as matérias no CSV
 ├── salvar_produtos()                              → Grava todos os produtos no CSV
 ├── salvar_produtos_materias()                     → Grava vínculos produto ↔ matéria no CSV
 ├── adicionar_materia_prima_arquivo()              → Adiciona nova matéria no arquivo
 ├── atualizar_materia_prima_arquivo()              → Atualiza preço ou nome de uma matéria
 ├── adicionar_produto_arquivo()                    → Adiciona novo produto ao arquivo
 ├── adicionar_produto_materia_arquivo()            → Adiciona nova ligação no CSV
 │
 ├── abrir_arquivo_escrita()                        → Abre arquivo para escrita
 ├── fechar_arquivo()                               → Fecha arquivo aberto
 ├── escrever_linha_csv()                           → Escreve linha formatada no CSV
 │
 ├── string_para_int()                              → Converte string para inteiro
 ├── string_para_float()                            → Converte string para float
 └── trim_string()                                  → Remove espaços extras da string
```
