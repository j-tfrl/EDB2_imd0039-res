#include "arvSBin.h"

int main(void) {
    int valores[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    int n = (int)(sizeof(valores) / sizeof(valores[0]));
    
    int val_a[]={50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65, 75, 85};
    int n_a=(int)(sizeof(val_a)/sizeof(val_a[0]));

    No* raiz = NULL;
    for (int i = 0; i < n; ++i) raiz = inserir(raiz, valores[i]);

    No* raiz_a = NULL;
    for (int j = 0; j < n_a; ++j) raiz_a = inserir(raiz_a, val_a[j]); //caso fosse o limite com n
    //... o unico valor divisivel por 10 incluído seria 25

    printf("Em-ordem (ordenado): ");
    emOrdem(raiz);
    printf("\n");

    //__________
    //item a)
    printf("\nITEM A | Em-ordem (ordenado): \n");
    emOrdem(raiz_a); //não está incluindo 55 (???)
    printf("\n\n");
    //__________

    int x = 7;
    printf("Buscando %d... %s\n", x, buscar(raiz, x) ? "encontrado" : "nao encontrado");


    //__________
    //item a)
    int x2 = 55;
    printf("\nITEM A | Buscando %d... %s\n\n", x2, buscar(raiz_a, x2) ? "encontrado" : "nao encontrado");
    //__________

    raiz = remover(raiz, 1);
    raiz = remover(raiz, 14);
    raiz = remover(raiz, 3);

    //_________
    //item a)
   
    raiz_a = remover(raiz_a, 10);
    raiz_a = remover(raiz_a, 25);
    raiz_a = remover(raiz_a, 50);
     //_________

    
    printf("\nEm-ordem após remoções: ");
    emOrdem(raiz);
    printf("\n\n");

    //_________
    printf("\nITEM A  | Em-ordem após remoções: ");
    emOrdem(raiz_a);
    printf("\n\n");
    //_________

    liberarArvore(raiz);
    liberarArvore(raiz_a);
    return 0;
}
