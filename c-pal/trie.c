#include "trie.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Criação de um novo nó.
// OBSERVAÇÃO IMPORTANTE: sempre inicializar todos os ponteiros, senão acessos inválidos acontecerão:
TrieNode *criarNoTrie()
{
    TrieNode *no = (TrieNode *)malloc(sizeof(TrieNode));
    if (!no)
        return NULL;

    no->fimDePalavra = 0;

    // Inicializa todos os filhos como NULL:
    for (int i = 0; i < 26; i++)
        no->filhos[i] = NULL;

    return no;
}

// Insere palavra letra por letra.
// ATENÇÃO: A Trie não armazena a palavra inteira, apenas a estrutura de caminhos:
void inserirTrie(TrieNode *raiz, const char *palavra)
{
    TrieNode *atual = raiz;

    for (int i = 0; palavra[i] != '\0'; i++)
    {
        char c = tolower(palavra[i]);

        // Ignorar caracteres inválidos:
        if (c < 'a' || c > 'z')
            continue;

        int idx = c - 'a';

        // Se o caminho não existe, cria um novo nó:
        if (atual->filhos[idx] == NULL)
            atual->filhos[idx] = criarNoTrie();

        atual = atual->filhos[idx];
    }

    // Marca que a palavra termina aqui:
    atual->fimDePalavra = 1;
}

// Busca apenas palavras completas.
// NOTA: Não confundir com prefixoTrie():
int buscarTrie(TrieNode *raiz, const char *palavra)
{
    TrieNode *atual = raiz;

    for (int i = 0; palavra[i] != '\0'; i++)
    {
        char c = tolower(palavra[i]);
        if (c < 'a' || c > 'z')
            return 0;

        int idx = c - 'a';

        if (atual->filhos[idx] == NULL)
            return 0; // caminho inexistente.

        atual = atual->filhos[idx];
    }

    // Só é palavra válida se estiver marcada como fim:
    return atual->fimDePalavra;
}

// Verifica apenas prefixos, sem exigir que seja palavra final.
// FUNDAMENTAL para o algoritmo de busca no tabuleiro:
int prefixoTrie(TrieNode *raiz, const char *palavra)
{
    TrieNode *atual = raiz;

    for (int i = 0; palavra[i] != '\0'; i++)
    {
        char c = tolower(palavra[i]);
        if (c < 'a' || c > 'z')
            return 0;

        int idx = c - 'a';

        if (atual->filhos[idx] == NULL)
            return 0; // não há prefixo.

        atual = atual->filhos[idx];
    }

    return 1;
}

void liberarTrie(TrieNode *r){
    if(r==NULL) return;
    // Liberamos recursivamente para cada filho
    for(int i=0; i<26; i++) liberarTrie(r->filhos[i]);
    free(r); // logo após, a própria raiz da trie
}