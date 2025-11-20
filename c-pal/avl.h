#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct No{
  char* p;
  struct No* esquerdo;
  struct No* direito;
  int altura;
}No;

int obter_altura(No* no);
int balanco(No* no); // calcula o fator de balanceamento
No* criar_no(char* p);

 // um nó é tomado como eixo; maior vai a direita
 // equilibrando a árbore
No* rotacao_direita(No* y);
No* rot_dir_esq(No* y);

// função análoga
No* rotacao_esquerda(No* x);
No* rot_esq_dir(No* x);

// inserção e remoção de palavras  
No* inserir_p(No* no, char* p);
No* remover_p(No* raiz, char* p);

No* menor_valorNo(No* no);

void imprimir_em_ordem(No* raiz);


// liberação de memória em no e na estrutura geral
void liberar_no(No* no);
void del_arv(No* raiz); // impede vazamentos de memória na AVL

#endif //AVL_H