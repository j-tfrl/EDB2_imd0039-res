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

No* remover_p(No* raiz, char* p){
    if(raiz==NULL) return raiz;

    if(p<raiz->p) raiz->esquerdo=remover_p(raiz->esquerdo, p);
    else if(p>raiz->p) raiz->direito=remover_p(raiz->direito, p);
    else{
        /*No com apenas um filho*/
        if((raiz->esquerdo==NULL) || raiz->direito==NULL){
            No* temp; // Nó temporário que vai receber as modificações

            if(raiz->esquerdo!=NULL) temp=raiz->esquerdo;
            else
                temp=raiz->direito;

           /*Caso onde há nenhum filho*/
           if(temp==NULL){
            temp=raiz;
            raiz=NULL;
           }else{
            *raiz=*temp;
           }

           free(temp);
        }else{ 
            No* temp=menor_valorNo(raiz->direito);
            raiz->p=temp->p;
            raiz->direito=remover_p(raiz->direito,temp->p);
        }
    }
        //   Se a árvore tinha apenas um nó. 
        if(raiz == NULL)
            return raiz;

        if(obter_altura(raiz->esquerdo) > obter_altura(raiz->direito))
            raiz->altura = 1 + obter_altura(raiz->esquerdo);
        else
            raiz->altura = 1 + obter_altura(raiz->direito);

        int b = balanco(raiz);

        //   Caso 1: Desbalanceamento à esquerda. 
        if(b > 1 && balanco(raiz->esquerdo) >= 0)
            return rotacao_direita(raiz);

        //Caso 2: Desbalanceamento esquerda-direita. 
        if(b > 1 && balanco(raiz->esquerdo) < 0){
            raiz->esquerdo = rotacao_esquerda(raiz->esquerdo);
            return rotacao_direita(raiz);
        }

        // Caso 3: Desbalanceamento à direita. 
        if(b < -1 && balanco(raiz->direito) <= 0) return rotacao_esquerda(raiz);

        //* Caso 4: Desbalanceamento direita-esquerda. 
        if(b < -1 && balanco(raiz->direito) > 0){
            raiz->direito = rotacao_direita(raiz->direito);
            return rotacao_esquerda(raiz);
        }

        return raiz;
            
            
}

No* inserir_p(No* no, char* p){
    if(no==NULL) return criar_no(p);

    if(p<no->p) no->esquerdo=inserir_p(no->esquerdo, p);
    else if (p>no->p) no->direito=inserir_p(no->esquerdo, p);
    else
        return no;

    if(obter_altura(no->esquerdo)>obter_altura(no->direito)){
        no->altura=1+obter_altura(no->esquerdo);
    }else{
        no->altura=1+obter_altura(no->direito);
    }

    int b=balanco(no);


    if(b > 1 && p < no->esquerdo->p)
    return rotacao_direita(no);

  // Caso 2: Desbalanceamento à direita (Rotação à esquerda). 
    if(b < -1 && p > no->direito->p)
        return rotacao_esquerda(no);

  // Caso 3: Desbalanceamento esquerda-direita (Rotação dupla esquerda-direita). 
    if(b > 1 && p > no->esquerdo->p){
        no->esquerdo = rotacao_esquerda(no->esquerdo);
        return rotacao_direita(no);
    }

  // Caso 4: Desbalanceamento direita-esquerda (Rotação dupla direita-esquerda). 
    if(b < -1 && p > no->direito->p){
        no->direito = rotacao_direita(no->direito);
        return rotacao_esquerda(no);
    }

    return no;

}


No* menor_valorNo(No* no){
    No* at=no;
    while(at->esquerdo!=NULL) at=at->esquerdo;
    return at;
}

void imprimir_em_ordem(No* raiz){
    if(raiz!=NULL){
        imprimir_em_ordem(raiz->esquerdo);
        printf("%s \n", raiz->p);
        imprimir_em_ordem(raiz->direito);
    }
}