#include "avl.h"


int obter_altura(No* no){
    if(no==NULL) return -1;
    else return no->altura;
}

No* criar_no(char* p){
    No* no=(No*)malloc(sizeof(No));
    no->p=p;
    no->esquerdo=NULL;
    no->direito=NULL;
    no->altura=0;

    return no;
}

int balanco(No* no){
    if(no==NULL) return 0;
    else return obter_altura(no-> esquerdo) - obter_altura(no->direito);
}


// Rotações
No* rotacao_direita(No* y){
    No* x=y->esquerdo;
    No* z=x->direito;

    x->direito=y;
    y->esquerdo=z;

    if(obter_altura(y->esquerdo)>obter_altura(y->direito))
        y->altura=1+obter_altura(y->esquerdo);
    else
        y->altura=1+obter_altura(y->direito);

    if(obter_altura(x->esquerdo)>obter_altura(x->direito))
        x->altura=1+obter_altura(x->esquerdo);
    else
        x->altura=1+obter_altura(x->direito);


    return x;

}

No* rot_dir_esq(No* y){
    No* x=y->direito;
    No* z=x->esquerdo;
    
    y=rotacao_direita(y);

    if(obter_altura(x->esquerdo)>obter_altura(x->direito))
        x->altura=1+obter_altura(x->esquerdo);
    else
        x->altura=1+obter_altura(y->direito);

    if(obter_altura(y->esquerdo)>obter_altura(y->direito))
        y->altura=1+obter_altura(y->esquerdo);
    else
        y->altura=1+obter_altura(y->direito);

    return y;
}


No* rotacao_esquerda(No* x){
    No* y=x->direito;
    No* z=y->esquerdo;

    y->esquerdo=x;
    x->direito=z;

    if(obter_altura(x->esquerdo)>obter_altura(x->direito))
        x->altura=1+obter_altura(x->esquerdo);
    else
        x->altura=1+obter_altura(x->direito);
    if(obter_altura(y->esquerdo)>obter_altura(y->direito))
        y->altura=1+obter_altura(y->esquerdo);
    else
        y->altura=1+obter_altura(y->direito);

    return y;
}


No* rot_esq_dir(No* y){
     No* x=y->direito;
    No* z=x->esquerdo;

    y=rotacao_esquerda(y);

    if(obter_altura(y->esquerdo)>obter_altura(y->direito))
        y->altura=1+obter_altura(y->esquerdo);
    else
        y->altura=1+obter_altura(y->direito);

    if(obter_altura(x->esquerdo)>obter_altura(x->direito))
        x->altura=1+obter_altura(x->esquerdo);
    else
        x->altura=1+obter_altura(x->direito);
    
    return y;
}