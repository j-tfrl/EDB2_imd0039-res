//Carrega apenas a árvore e provê arquivos para heap.c

#include "fileLoad.h"
#include "abbSys.h"


No* inserir(No* r, CatVector* vetorComCat) {
    char* cat_ext=vetorComCat->cat;
    
    if (r == NULL) return novoNo(cat_ext);
    if (cat_ext < r->catExt) r->esq = inserir(r->esq, vetorComCat);
    else if (cat_ext > r->catExt) r->dir = inserir(r->dir, vetorComCat);
    return r;
}


No* novoNo(char* catExt){
 
    No* n=(No*)malloc(sizeof(No));
    if(!n){
        perror("Erro ao alocar no");
        return NULL;
    }

    n->catExt=(char*)malloc(strlen(catExt)+1);

    if(!n->catExt){
        perror("Erro ao alocar dado em string da categoria");
        free(n);
        return NULL;
    }

    strcpy(n->catExt, catExt); //copia a informação da categoria
    n->esq=n->dir=NULL;

    return n;

}

No* buildABB(CatVector* vCats){
    if(!vCats || vCats->count==0) return NULL;

    No* raiz=NULL;
    int lmt=vCats->count;

    // como temos um vetor de strings, podemos alimentar a ABB com 
    // o que vem da struct CatVector 
    for(int i=0; i<lmt;i++) raiz=inserir(raiz,vCats->cat[i]);

    return raiz;
}

void emOrdem(No* raiz){
    if (raiz==NULL) return;
    emOrdem(raiz->esq);
    printf("%s ", raiz->catExt);
    emOrdem(raiz->dir);
}

No* buscaCat(No* raiz, const char* cat){
    if(raiz==NULL || raiz->catExt == cat) return raiz;
    return(cat < raiz->catExt) ? buscaCat(raiz->esq, cat) : buscaCat(raiz->dir, cat);
}

void liberarABB(No* raiz){
    if(raiz==NULL) return;

    liberarABB(raiz->esq);
    liberarABB(raiz->dir);

    free(raiz->catExt);
    free(raiz);
}

// já mostra as categorias em ordem e permite a busca
void processarCat(const char* arqCSV, int indexColCat){
    CatVector* categoria=leCSV_Cat(arqCSV, indexColCat);

    if(!categoria || categoria->count==0){
        printf("Nenhuma categoria encontrada. Insira um novo arquivo e tente novamente\n");
        return;
    }

    printf("Carregadas %d categorias do .CSV", categoria->count);

    // construindo a arvore
    No* tree=buildABB(categoria);

    printf("\n Categorias em ordem: ");
    emOrdem(tree);

    char busca[MAX_CAT_NAME];
    print("Digite uma categoria para a busca\n");
    scanf("%s", busca);

    No* resultado=buscaCat(tree, busca);
    if(resultado) printf("Categoria '%s' encontrada: ", busca, "| processando arquivo .csv correspondente\n");
    else printf("Não encontrada: ", busca);

    libera(tree);
    libera(categoria);

}

// contagem de livros no estoque 
int contaEstoque(char* busca){
    LivroVet* liv=readCatCSV_provideHeap(busca);

    if(!liv || liv->count==0){
        printf("Não foram adicionados livros para a contagem\n");
        if(liv) liberaLvet(liv);
        return 0;
    }
    int cEstoque=0;
    int index=0;
    while(liv->count!=0){
        cEstoque+=liv->livros[index].estoque;
        liv->count--;
        index++;
    }

    printf("Categoria '%s': %d' é o estoque total", busca, cEstoque);

    liberaLvet(liv);

    return cEstoque;
}

void liberaLvet(LivroVet* arr){
    if(arr){
        free(arr->livros);
        free(arr);
    }

}


// arquivo em .csv que vai ser utilizado na heap
// aqui os dados do livro da categoria serão lidos
// para ajudar no processamento em heap.c
Livro* readCatCSV_provideHeap(char* busca){
    char* fileFormat=".csv";
    char* file_provHeap=strcat(busca, fileFormat);
    FILE* abrir=fopen(file_provHeap, "r");

    if(!checkOpenFile(abrir)) return NULL;

    // reserva de espaço para 1000 livros (livros_cat: onde há os livros na cat.)
    Livro* livros_cat=(Livro*)malloc(sizeof(Livro) * 1000);

    if(livros_cat==NULL){
        printf("Falha na alocação de memória\n");
        fclose(abrir);
        return NULL;
    }

    int index_livrosCat=0;
    char linha[1024]; // buffer para ler linhas

    while(fgets(linha, sizeof(linha), abrir)){
        if(sscanf(linha, "%d,%99[^,],%99[^,],%d,%f,%d,%d",
            &livros_cat[index_livrosCat].isbn,
            livros_cat[index_livrosCat].titulo,
            livros_cat[index_livrosCat].autor,
            &livros_cat[index_livrosCat].ano,
            &livros_cat[index_livrosCat].preco,
            &livros_cat[index_livrosCat].estoque,
            &livros_cat[index_livrosCat].vendas
        )==7) //sete atributos passam na controle
        {
            index_livrosCat++;
        }

        if(index_livrosCat>=1000) break;
    }

    fclose(abrir);

    if(index_livrosCat==0){
        free(livros_cat);
        return NULL;
    }

    contaEstoque(busca);

    return livros_cat;

}
