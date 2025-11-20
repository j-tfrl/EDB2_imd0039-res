
#include "jogo.h"

#define MAX 100

// --------------------------------------
// Leitura do tabuleiro
// --------------------------------------

// NOTE: O tabuleiro é alocado dinamicamente.
// Lembrar de liberar depois no main() para evitar memory leak:
char **lerTabuleiro(int *n)
{
    //FILE *arq = fopen("tabuleiro.txt", "r");

    FILE *arq = fopen("caca-pal__mus.txt", "r");

    if (!arq)
    {
        printf("Erro ao abrir tabuleiro.txt\n");
        return NULL;
    }

    // O arquivo contém algo como: "10 10":
    fscanf(arq, "%d %d", n, n);

    char **tab = malloc((*n) * sizeof(char *));

    for (int i = 0; i < *n; i++)
    {
        tab[i] = malloc((*n) * sizeof(char));

        // Ler cada caractere da matriz do tabuleiro:
        for (int j = 0; j < *n; j++)
            fscanf(arq, " %c", &tab[i][j]);
    }

    fclose(arq);
    return tab;
}

// --------------------------------------
// Carrega palavras para a Trie
// --------------------------------------

// OBSERVAÇÃO: Cada linha do arquivo representa uma palavra permitida:
void carregarPalavras(TrieNode *raiz)
{
    FILE *arq = fopen("p__mus.txt", "r");
    if (!arq)
    {
        printf("Erro ao abrir palavras.txt\n");
        return;
    }

    char palavra[MAX];

    while (fscanf(arq, "%s", palavra) != EOF)
    {
        // A Trie aceita apenas letras válidas (a-z):
        inserirTrie(raiz, palavra);
    }

    fclose(arq);
}

// --------------------------------------
// Definição das 8 direções possíveis.
// --------------------------------------

// (-1,0) para cima, (1,0) para baixo, etc.
// OBS: A busca depende totalmente dessa matriz:
int direcoes[8][2] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

// ---------------------------------------------
// Busca palavras a partir de uma posição (x,y)
// ---------------------------------------------

// IMPORTANTE RESSALTAR: As palavras podem crescer em qualquer direção até fim de tabuleiro:
void buscarAPartirDe(int x, int y, char **tab, int n,
                     TrieNode *trie, No **raizAVL)
{

    char palavra[MAX];

    for (int d = 0; d < 8; d++)
    {

        int dx = direcoes[d][0];
        int dy = direcoes[d][1];

        int i = x, j = y, k = 0;

        while (i >= 0 && i < n && j >= 0 && j < n)
        {

            // Constrói palavra letra por letra:
            palavra[k++] = tolower(tab[i][j]);
            palavra[k] = '\0';

            // prefixoTrie() evita buscas desnecessárias:
            if (!prefixoTrie(trie, palavra))
                break;

            // Se é palavra válida, inserir na AVL:
            if (buscarTrie(trie, palavra))
            {

                // ATENÇÃO IMPORTANTE: Jefferson, a AVL que você implementou armazena apenas um char* SEM duplicar. Se passarmos "palavra" diretamente, ela será sobrescrita.

                // strdup() cria uma cópia própria, evitando ponteiros soltos (dangling pointers):
                char *copia = strdup(palavra);

                *raizAVL = inserir_p(*raizAVL, copia);
            }

            i += dx;
            j += dy;
        }
    }
}

// --------------------------------------
// Busca geral no tabuleiro inteiro
// --------------------------------------

// OBS.: Para cada posição inicial (i,j), iremos invocar uma busca em 8 direções:
void buscarPalavras(char **tab, int n,
                    TrieNode *trie, No **raizAVL)
{

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            buscarAPartirDe(i, j, tab, n, trie, raizAVL);
}

// --------------------------------------
// Exibe palavras encontradas (via AVL)
// --------------------------------------

// VÊ ISSO AQUI: imprimir_em_ordem() imprime ordenado alfabeticamente.
void imprimirResultados(No *raizAVL)
{
    printf("\nPalavras encontradas:\n");
    imprimir_em_ordem(raizAVL);
}