#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100

struct Produto {
    char nome[50];
    int codigo;
    int quantidade;
    float preco;
};



struct ListaProdutos {
    struct Produto produtos[MAX_PRODUTOS];
    int tamanho;
}lista;


int buscarProduto(int codigo, struct ListaProdutos *lista){
    for (int i = 0; i < lista->tamanho; i++){
        if(lista->produtos[i].codigo == codigo) return 1;
    }
    return 0;
}




void adicionarProduto(struct ListaProdutos *lista, int tamanho, struct Produto produto){
    if(buscarProduto(produto.codigo, lista) == 1){
        printf("Produto já existe");
    }
    else{
        if(tamanho > 0) lista->produtos[tamanho] = produto;
        else{
            tamanho = 0;
            lista->produtos[tamanho] = produto;
        }
    }
}

void ordenarProduto(int tamanho){
    for (int i = 0; i < tamanho; i++)
    {
        
    }
    
}