#include "avl.h"

int obter_altura(No* no){
    if(no==NULL) return -1;
    else return no->altura;
}

No* criar_no(char* p){
    No* no=(No*)malloc(sizeof(No));
    if(no==NULL) return NULL; 

    // aloca memoria para a string
    no->p=(char*)malloc(strlen(p)+1); // +1  para o caractere final

    if(no->p==NULL){
        free(no);
        perror("Não foi possível alocar a palavra no nó");
        return NULL;
    }

    // feito todos os controles, alocamos na memória
    strcpy(no->p, p);
    //no->p=p;
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

No* rot_dir_esq(No* x){
    x->esquerdo=rotacao_esquerda(x->esquerdo);
    return rotacao_direita(x);
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
    y->direito=rotacao_direita(y->direito);
    return rotacao_esquerda(y);
}

No* remover_p(No* raiz, char* p){
    if(raiz==NULL) return raiz;

    int cmp=strcmp(p, raiz->p);
    
    if(cmp<0) raiz->esquerdo=remover_p(raiz->esquerdo, p);
    else if(cmp>0) raiz->direito=remover_p(raiz->direito, p);
    else{
        /*No com apenas um filho ou nenhum*/
        if((raiz->esquerdo==NULL) || raiz->direito==NULL){
            No* temp = (raiz->esquerdo != NULL) ? raiz->esquerdo : raiz->direito;
            
            liberar_no(raiz); //libera a string e a struct
            
            return temp;
        }else{ 
            No* temp=menor_valorNo(raiz->direito);

            free(raiz->p);

            raiz->p=(char*)malloc(strlen(temp->p)+1);

            if(raiz->p==NULL) return NULL;
            strcpy(raiz->p, temp->p); //fazemos uma copia para tomar a palavra
            /*
            raiz->p=temp->p;
        */
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

    int cmp=strcmp(p, no->p);

    if(cmp<0) no->esquerdo=inserir_p(no->esquerdo, p);
    else if (cmp>0) no->direito=inserir_p(no->direito, p);
    else
        return no;

    //alturas para balanços
    int h_e=obter_altura(no->esquerdo);
    int h_d=obter_altura(no->direito);

    no->altura=1+((h_e>h_d)) ? h_e:h_d; // atualização da altura com base nas ramificações
    int b=balanco(no);

    /// BALANCEAMENTO ///
    // adiciona palavra que é anterior ao do no filho esq.
    if(b > 1 && strcmp(p, no->esquerdo->p)<0) return rotacao_direita(no);
    // análogo: 
    if (b < -1 && strcmp(p, no->direito->p) > 0) return rotacao_esquerda(no);
    
    if (b>1 && strcmp(p, no->esquerdo->p)>0) return rot_esq_dir(no);
    if (b<-1 && strcmp(p, no->direito->p)<0) return rot_dir_esq(no);

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

void liberar_no(No* no){
    if(no==NULL) return;
    free(no->p); // liberamos na palavra
    free(no); // liberamos no nó
}

void del_arv(No* raiz){
    if(raiz==NULL) return;
    del_arv(raiz->esquerdo);
    del_arv(raiz->direito);
    liberar_no(raiz);
}