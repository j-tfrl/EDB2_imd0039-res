#include "arvSBin.h"

int main(void) {
    int valores[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    int n = (int)(sizeof(valores) / sizeof(valores[0]));
    
    int val_a[]={50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65, 75, 85};
    int n_a=(int)(sizeof(val_a)/sizeof(val_a[0]));

    int val_b[]={10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120};
    int n_b=(int)(sizeof(val_b)/sizeof(val_b[0]));

    int val_c[]={50, 40, 99, 30, 45, 34, 32, 35, 70, 65, 85, 100, 95, 110};
    int n_c=(int)(sizeof(val_c)/sizeof(val_b[0]));

    No* raiz = NULL;
    for (int i = 0; i < n; ++i) raiz = inserir(raiz, valores[i]);

    No* raiz_a = NULL;
    for (int j = 0; j < n_a; ++j) raiz_a = inserir(raiz_a, val_a[j]); //caso fosse o limite com n
    //... o unico valor divisivel por 10 incluído seria 25

    No* raiz_b= NULL;
    for (int k=0; k<n_b; ++k) raiz_b=inserir(raiz_b, val_b[k]);

    No* raiz_c=NULL;
    for(int m=0; m<n_c; ++m) raiz_c=inserir(raiz_c, val_c[m]);
 
    printf("Em-ordem (ordenado): ");
    emOrdem(raiz);
    printf("\n");

   
    int x = 7;
    printf("Buscando %d... %s\n", x, buscar(raiz, x) ? "encontrado" : "nao encontrado");


    //_________ item a) __________
    int x2 = 55;
    printf("\nITEM A | Buscando %d... %s\n\n", x2, buscar(raiz_a, x2) ? "encontrado" : "nao encontrado");
    //__________


    //_________ item b) __________
    int x3=30;
    printf("\n ITEM B | Buscando %d... %s\n\n", x3, buscar(raiz_b, x3) ? "encontrado": "nao encontrado");


    //_________ item c) __________
    int x4=99;
    printf("\n ITEM C | Buscando %d... %s\n\n", x4, buscar(raiz_c, x4) ? "encontrado": "nao encontrado");


     //__________
    //item a)
    printf("\nITEM A | Em-ordem (ordenado): \n");
    emOrdem(raiz_a);
    printf("\n\n");
    //__________


    //__________
    //item b)
    printf("\nITEM B | Em-ordem (ordenado): \n");
    emOrdem(raiz_b);
    printf("\n\n");

    //__________
    //item c)
    printf("\nITEM C | Em-ordem (ordenado): \n");
    emOrdem(raiz_c); 
    printf("\n\n");
    
    raiz = remover(raiz, 1);
    raiz = remover(raiz, 14);
    raiz = remover(raiz, 3);

    //_________
    //item a)
   
    raiz_a = remover(raiz_a, 10);
    raiz_a = remover(raiz_a, 25);
    raiz_a = remover(raiz_a, 50);
     //_________
     
    //_________
    //item b)
    raiz_b=remover(raiz_b, 120);
    raiz_b=remover(raiz_b, 100);
    raiz_b=remover(raiz_b, 60);


    //___________
    //item c)
    raiz_c=remover(raiz_c,95);
    raiz_c=remover(raiz_c,100);
    raiz_c=remover(raiz_c, 99);

    printf("\nEm-ordem após remoções: ");
    emOrdem(raiz);
    printf("\n\n");

    //_________
    printf("\nITEM A  | Em-ordem após remoções: ");
    emOrdem(raiz_a);
    printf("\n\n");
    //_________

    //_________
    printf("\nITEM B | Em-ordem após remoções: ");
    emOrdem(raiz_b);
    printf("\n\n");
    //_________

    //_________
    printf("\nITEM C | Em-ordem após remoções: ");
    emOrdem(raiz_b);
    printf("\n\n");
    //_________

    liberarArvore(raiz);
    liberarArvore(raiz_a);
    liberarArvore(raiz_b);
    liberarArvore(raiz_c);

    return 0;
}
