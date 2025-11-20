#ifndef JOGO_h
#define JOGO_h

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "trie.h"
#include "avl.h"

char **lerTabuleiro(int *n);
void carregarPalavras(TrieNode *raiz);
void buscarAPartirDe(int x, int y, char **tab, int n, TrieNode *trie, No **raizAVL);
void buscarPalavras(char **tab, int n,TrieNode *trie, No **raizAVL);
void imprimirResultados(No *raizAVL);

#endif //JOGO_h