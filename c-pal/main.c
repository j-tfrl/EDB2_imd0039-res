#include "avl.h"
#include "trie.h"

int main(){
    print("#..*#..*#..*#..* CAÇA PALAVRAS *..#*..#*..#*..#\n\n");

    //WHILE impl -- laco para controlar e informar o usuário para comecar o jogo
    TrieNode *trie = criarNoTrie();
    carregarPalavras(trie);

    
    int n; // dimensões l x l do quadro de palavras do tabuleiro
    char **tab = lerTabuleiro(&n);
    if (!tab){
        perror("Não foi possível abrir o tabuleiro");
        return 1; // Erro ao ler tabuleiro
    }

    // Buscar palavras no tabuleiro e armazenar em AVL:
    No *raizAVL = NULL;
    buscarPalavras(tab, n, trie, &raizAVL);

    printf("Palavras encontradas:\n");
    imprimirResultados(raizAVL);

    del_arv(raizAVL);
    for (int i = 0; i < n; i++)
        free(tab[i]);
    free(tab);


   // liberarTrie(trie); !! IMPL

    return 0;
}