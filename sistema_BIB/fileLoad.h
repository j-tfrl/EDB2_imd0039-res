//Carrega os arquivos em csv
#ifndef FILE_LOAD
#define FILE_LOAD

#define MAX_CAT 1000
#define MAX_CAT_NAME 15

//cat.=="CATEGORIA"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool checkOpenFile(FILE* arqCsv){
    //bool isok=true;
    if(!arqCsv){
        perror("Abertura do arquivo falhou");
        return false;
    }

    return true;
}

FILE* openFile(const char *fileAdd){
    FILE* abrir=fopen(fileAdd, "r");
    if(!checkOpenFile(abrir)) return NULL; // checa o .csv
    return abrir;
}


void readFile(FILE* dataCsv){
    if(!dataCsv) return;
    int c;

    while((c=fgetc(dataCsv))!=EOF) putchar(c);

    if(ferror(dataCsv)){
        puts("ERRO DE LEITURA");
    }
    // caso n haja erro, significa que a leitura foi concluída
}


void closeFile(FILE* f){
    if(f){
        fclose(f);
    } 
}

/* #### DEFININDO CATEGORIAS DENTRO DO ARQ #### */

typedef struct{
    char **cat; // array de strings
    int count;
    int cap; // capacidade
}CatVector;


void initCatVector(CatVector* v, int cap_inicial){
    v->cat=(char**)malloc(sizeof(char*)*cap_inicial);
    v->count=0;
    v->cap=cap_inicial;

}

CatVector* criaVtCat(){
    // trata o bloco a seguir como se fosse CatVector, mesmo com retorno void
    // assim podemos usar ref. com '->'
    CatVector* vet=(CatVector*)malloc(sizeof(CatVector)); 

    if(!vet) return NULL;

    initCatVector(vet, 100);

    return vet;
}

// adicionando categorias
void addCat(CatVector* v, const char* nome_cat){
    if(v->count>=v->cap){
        v->cap*=2; // atualização de tamanho para utilizar alocação abaixo
        v->cat=(char**)realloc(v->cat, sizeof(char*)*v->cap);
    }
    // aloca espaço para os caracteres da string + 1 (\0)
    v->cat[v->count]=(char*)malloc(strlen(nome_cat)+1); 
    strcpy(v->cat[v->count], nome_cat);// cada categoria é colocada no vetor
    v->count++;
}

// liberar memoria
void liberaCat(CatVector* v){
    if(!v) return;

    for(int i=0; i<v->count; i++) free(v->cat[i]); // libera em cada posição
    free(v->cat);
    free(v);
}

// LEITURA DO .CSV
CatVector* leCSV_Cat(const char* file, int indexCol){
    FILE* f=openFile(file);
    if(!f) return NULL; // falha na leitura
    
    CatVector* cats=criaVtCat();

    if(!cats){
        closeFile(f);
        return NULL; // se não tem categorias, então NULL
    }

    char linha[1024];
    char *token; // cada parte das strings

    while(fgets(linha, sizeof(linha), f)){
        linha[strcspn(linha, "\0")]=0; // remove quebra

        int atualCol=0;
        char *linha_ptr=linha;
        // leitura com delimitador c/ strtok_r
        while((token=strtok_r(linha_ptr, ";", &linha_ptr))){
            if(atualCol==indexCol){
                addCat(cats, token); // há um 'match': logo a categoria é adiciona ao vetor
                break;
            }
            atualCol++;
        } 

    }
    closeFile(f);
    return cats;
}




#endif //FILE_LOAD