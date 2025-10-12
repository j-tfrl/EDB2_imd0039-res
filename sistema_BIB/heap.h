#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileLoad.h"

#define MAX_TITULO 100
#define MAX_AUTOR 100

typedef struct {
    int isbn;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int ano;
    float preco;
    int estoque;
    int vendas;
} Livro;

typedef struct {
    Livro *livros;
    int tamanho;
    int capacidade;
} HeapMax;

// Criação e liberação:
HeapMax* criarHeap(int capacidade);
void liberarHeap(HeapMax *heap);

// Inserção e remoção:
void inserirHeap(HeapMax *heap, Livro* livro);
Livro extrairMax(HeapMax *heap);

// Reconstrução e utilidades:
void heapify(HeapMax *heap, int i);
void reconstruirHeap(HeapMax *heap);
void imprimirTopN(HeapMax *heap, int n);
void mostraPrimeiroMaisVendido(HeapMax* heap);

// Acesso ao topo (sem remover):
Livro topoHeap(HeapMax *heap);

// Processa os dados em .csv referentes a uma dada categoria
// onde se encontram os livros de interesse: 
HeapMax* processaLivro(const char *arqCSV, int indexCol_Vendas);

// Venda de livro (registro): 
Livro* buscaISBN(HeapMax* vLivro, int ISBN);
void updateHeap(HeapMax* heap, int isbn, int qtd); 

#endif
