#ifndef ABBSYS
#define ABBSYS
#include "fileLoad.h"
#include "heap.h"

typedef struct No{
    char* catExt; //categoria extraída
    struct No *esq, *dir;
}No;

// Inserção e criação de nós:
No* inserir(No* r, CatVector* vetorComCat);
No* novoNo(char* catExt);

// Funções requisitadas:
No* buildABB(CatVector* vCats);
void emOrdem(No* raiz);
No* buscaCat(No* raiz, const char* cat){

// Processamento e liberação:
void liberarABB(No* raiz);
bool checkFinalPartFile(char *file);
void processarCat(const char* arqCSV, int indexColCat);

// Contagem de estoque de livros
int contaEstoque(char* busca);

// Processamento para a base de dados de livros 
// de uma categoria de interesse
Livro* readCatCSV_provideHeap(char* busca);

#endif //ABBSYS


