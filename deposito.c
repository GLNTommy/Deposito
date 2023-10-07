/* Ryan Lucas Moreira - SC3033538
   Thomas Caio dos Santos - SC302086X*/


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

struct Produto estoque[MAX_PRODUTOS];
int numProdutos = 0;
const int estoqueMedio = 50;

void salvarEstoque() {
    FILE *arquivo = fopen("estoque.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de estoque.\n");
        return;
    }

    for (int i = 0; i < numProdutos; i++) {
        fprintf(arquivo, "%s,%d,%d,%.2f\n", estoque[i].nome, estoque[i].codigo, estoque[i].quantidade, estoque[i].preco);
    }

    fclose(arquivo);
    printf("Estoque salvo com sucesso!\n");
}

void carregarEstoque() {
    FILE *arquivo = fopen("estoque.csv", "r");
    if (arquivo == NULL) {
        printf("Arquivo de estoque nao encontrado. O estoque esta vazio.\n");
        return;
    }

    char linha[100];
    numProdutos = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%49[^,],%d,%d,%f", estoque[numProdutos].nome, &estoque[numProdutos].codigo,
               &estoque[numProdutos].quantidade, &estoque[numProdutos].preco);
        numProdutos++;
    }

    fclose(arquivo);
    printf("Estoque carregado com sucesso!\n");
}

void adicionarProduto() {
    if (numProdutos >= MAX_PRODUTOS) {
        printf("O estoque esta cheio. Não eh possivel adicionar mais produtos.\n");
        return;
    }

    struct Produto novoProduto;
    printf("Digite o nome do produto: ");
    scanf("%s", novoProduto.nome);
    printf("Digite o codigo do produto: ");
    scanf("%d", &novoProduto.codigo);

    for (int i = 0; i < numProdutos; i++) {
        if (estoque[i].codigo == novoProduto.codigo) {
            printf("Produto com o mesmo codigo ja existe no estoque. Não eh possivel adicionar.\n");
            return;
        }
    }

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &novoProduto.quantidade);
    printf("Digite o preço do produto: ");
    scanf("%f", &novoProduto.preco);

    estoque[numProdutos] = novoProduto;
    numProdutos++;
    printf("Produto adicionado com sucesso!\n");
}

void removerProduto() {
    int codigo;
    printf("Digite o codigo do produto a ser removido: ");
    scanf("%d", &codigo);

    int indice = -1;

    for (int i = 0; i < numProdutos; i++) {
        if (estoque[i].codigo == codigo) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Produto nao encontrado no estoque.\n");
        return;
    }

    for (int i = indice; i < numProdutos - 1; i++) {
        estoque[i] = estoque[i + 1];
    }

    numProdutos--;
    printf("Produto removido com sucesso!\n");
}

void atualizarProduto() {
    int codigo;
    printf("Digite o codigo do produto a ser atualizado: ");
    scanf("%d", &codigo);

    int indice = -1;

    for (int i = 0; i < numProdutos; i++) {
        if (estoque[i].codigo == codigo) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Produto nao encontrado no estoque.\n");
        return;
    }

    printf("Digite o novo nome do produto: ");
    scanf("%s", estoque[indice].nome);
    printf("Digite a nova quantidade em estoque: ");
    scanf("%d", &estoque[indice].quantidade);
    printf("Digite o novo preço do produto: ");
    scanf("%f", &estoque[indice].preco);

    printf("Produto atualizado com sucesso!\n");
}


int compararPorNome(const void *a, const void *b) {
    return strcmp(((struct Produto*)a)->nome, ((struct Produto*)b)->nome);
}

int compararPorCodigo(const void *a, const void *b) {
    return ((struct Produto*)a)->codigo - ((struct Produto*)b)->codigo;
}

int compararPorQuantidade(const void *a, const void *b) {
    return ((struct Produto*)a)->quantidade - ((struct Produto*)b)->quantidade;
}

int compararPorPreco(const void *a, const void *b) {
    if (((struct Produto*)a)->preco < ((struct Produto*)b)->preco) return -1;
    if (((struct Produto*)a)->preco > ((struct Produto*)b)->preco) return 1;
    return 0;
}

void listarProdutosOrdenados(int criterio) {
    if (numProdutos == 0) {
        printf("O estoque esta vazio.\n");
        return;
    }

    switch (criterio) {
        case 1: 
            qsort(estoque, numProdutos, sizeof(struct Produto), compararPorNome);
            break;
        case 2: 
            qsort(estoque, numProdutos, sizeof(struct Produto), compararPorCodigo);
            break;
        case 3: 
            qsort(estoque, numProdutos, sizeof(struct Produto), compararPorQuantidade);
            break;
        case 4: 
            qsort(estoque, numProdutos, sizeof(struct Produto), compararPorPreco);
            break;
        default:
            printf("Opcao de ordenacao invalida.\n");
            return;
    }

    printf("Produtos ordenados:\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("Nome: %s, Codigo: %d, Quantidade: %d, Preco: %.2f\n", 
               estoque[i].nome, estoque[i].codigo,
               estoque[i].quantidade, estoque[i].preco);
    }
}

void listarProdutosComEstoqueBaixo(int limite) {
    if (numProdutos == 0) {
        printf("O estoque esta vazio.\n");
        return;
    }

    printf("Produtos com estoque baixo (menos de %d unidades):\n", limite);
    for (int i = 0; i < numProdutos; i++) {
        if (estoque[i].quantidade < limite) {
            printf("Nome: %s, Codigo: %d, Quantidade: %d, Preco: %.2f\n", 
                   estoque[i].nome, estoque[i].codigo,
                   estoque[i].quantidade, estoque[i].preco);
        }
    }
}

void gerarRelatoriosEstoque() {
    int opcao;

    do {
        printf("\nRelatorios de Estoque:\n");
        printf("1. Listar todos os produtos ordenados por nome\n");
        printf("2. Listar todos os produtos ordenados por codigo\n");
        printf("3. Listar todos os produtos ordenados por quantidade\n");
        printf("4. Listar todos os produtos ordenados por preco\n");
        printf("5. Listar produtos com estoque baixo\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listarProdutosOrdenados(1);
                break;
            case 2:
                listarProdutosOrdenados(2);
                break;
            case 3:
                listarProdutosOrdenados(3);
                break;
            case 4:
                listarProdutosOrdenados(4);
                break;
            case 5:
                listarProdutosComEstoqueBaixo(estoqueMedio);
                break;
            case 0:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}

int main() {
    carregarEstoque();
    int opcao;

    do {
        printf("\nMENU:\n");
        printf("1. Adicionar Produto\n");
        printf("2. Remover Produto\n");
        printf("3. Atualizar Produto\n");
        printf("4. Relatorios de Estoque\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        fflush(stdin);
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarProduto();
                break;
            case 2:
                removerProduto();
                break;
            case 3:
                atualizarProduto();
                break;
            case 4:
                gerarRelatoriosEstoque();
                break;
            case 0:
                salvarEstoque();
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 1;
}


