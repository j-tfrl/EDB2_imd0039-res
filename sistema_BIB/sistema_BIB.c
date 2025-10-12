#include "abbSys.h"
#include "heap.h"
#include "fileLoad.h"

int main(){
    printf("######### BIB - SISTEMA DE GESTÃO DE ESTOQUE #########");

     // Carregamento do arquivo .csv é automático, já que 
    // ele é o arquivo principal do programa
    FILE* csv_file=openFile("categorias.csv");
    readFile(csv_file); //executa a leitura
    bool rnn=true; //controla o laço do menu
    int op=0;

    if(checkOpenFile(csv_file)){ //controle por precaução

        CatVector* catCSVfile=leCSV_Cat("categorias.csv", 1);
        //liberaCat(catCSVfile);
        while(rnn){
            printf("\n\n Selecione uma opção do menu a seguir: \n");
            printf("[1] Listar categorias e selecionar;\n[2] Mostrar o livro mais vendido da categoria;\n",
              "[4] Mostrar os mais vendidos\n[5] Registrar venda \n[6] Sair");
            scanf("%d", &op);
            bool uOpt=false;


            if(op<1||op>6) perror("Selecione um número válido\n");
            uOpt=true;
            
            if(uOpt){

                switch(op){
                    case 1:{}
                    case 2:{}
                    case 3:{}
                    case 4:{}
                    case 5:{
                        int isbn_s=0;
                        printf("\nInsira ISBN do livro para a venda\n");
                        scanf("%d", isbn_s);

                        //buscaISBN(vetor de livro aq, isbn_s);
                    }
                    case 6:{}
                    default:{
                        rnn=false;
                        printf("Saindo do programa...\n");
                        break;
                    }


                }

            }
        liberaCat(catCSVfile);
        }
    }

    return 0;
}
