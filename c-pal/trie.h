#ifndef TRIE_H
#define TRIE_H

// Cada nó representa um caractere da palavra.
// A Trie permite validar rápido prefixos e palavras inteiras:
typedef struct TrieNode
{
    struct TrieNode *filhos[26]; // um ponteiro para cada letra 'a' a 'z'.
    int fimDePalavra;            // marca se este caminho forma uma palavra completa.
} TrieNode;

// Cria um nó com todos os ponteiros nulos.
// OBS: cuidar para sempre inicializar filhos[] com NULL:
TrieNode *criarNoTrie();

// Insere uma palavra na Trie.
// NOTE: insere letra por letra e marca fimDePalavra ao final:
void inserirTrie(TrieNode *raiz, const char *palavra);

// Busca por uma palavra inteira.
// Retorna 1 se existir e 0 caso contrário:
int buscarTrie(TrieNode *raiz, const char *palavra);

// Verifica apenas prefixos.
// IMPORTANTE para interromper buscas no tabuleiro cedo:
int prefixoTrie(TrieNode *raiz, const char *palavra);

void liberarTrie(TrieNode *r);

#endif