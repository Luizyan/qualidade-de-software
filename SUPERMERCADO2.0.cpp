#include <stdio.h>

typedef struct {
    char nome[30];
    int id;
    float preco;
} Produto;

typedef struct {
    int quant;
    Produto produto[50];
    Produto carrinho[50];
} Carrinho;

// Função para remover um pedido
void remoPedido(Carrinho *carrinho, int id) {
    for (int i = 0; i < carrinho->quant; i++) {
        if (carrinho->carrinho[i].id == id) {
            // Remover produto do carrinho
            for (int j = i; j < carrinho->quant - 1; j++) {
                carrinho->carrinho[j] = carrinho->carrinho[j + 1];
            }
            carrinho->quant--;
            printf("Produto removido com sucesso\n");
            return;
        }
    }
    printf("Produto não encontrado\n");
}

// Função para atualizar um pedido
void atualizarPedido(Carrinho *carrinho, int id, float preco) {
    for (int i = 0; i < carrinho->quant; i++) {
        if (carrinho->carrinho[i].id == id) {
            // Atualizar preço do pedido
            carrinho->carrinho[i].preco = preco;
            printf("Preço atualizado com sucesso\n");
            return;
        }
    }
    printf("Produto não encontrado no carrinho\n");
}

// Variável global para a contagem correta dos IDs
int cont = 0;

// Função para calcular o valor total
void valorTotal(Carrinho *carrinho) {
    float total = 0;
    printf("Pedido fechado\n");
    printf("Produtos no pedido:\n");
    for (int i = 0; i < carrinho->quant; i++) {
        printf("ID: %d | Nome: %s | Preço: %.2f\n", carrinho->carrinho[i].id, carrinho->carrinho[i].nome, carrinho->carrinho[i].preco);
        total += carrinho->carrinho[i].preco;
    }
    printf("Valor total: R$%.2f\n", total);
}

// Função para listar todos os produtos cadastrados
void cadasProduto(Carrinho *carrinho) {
    if (cont == 0) {
        printf("Nenhum produto cadastrado.\n");
    } else {
        printf("Seus produtos listados:\n");
        for (int i = 0; i < cont; i++) {
            printf("ID: %d | Nome: %s | Preço: %.2f\n", carrinho->produto[i].id, carrinho->produto[i].nome, carrinho->produto[i].preco);
        }
    }
}

// Função para exibir o carrinho
void exibirCar(Carrinho *carrinho) {
    printf("Produtos no carrinho:\n");
    if (carrinho->quant == 0) {
        printf("Carrinho vazio.\n");
    } else {
        for (int i = 0; i < carrinho->quant; i++) {
            printf("ID: %d | Nome: %s | Preço: %.2f\n", carrinho->carrinho[i].id, carrinho->carrinho[i].nome, carrinho->carrinho[i].preco);
        }
    }
}

// Função para adicionar ao carrinho
void adcarrinho(Carrinho *carrinho, int id) {
    // Verifica se o produto existe
    for (int i = 0; i < cont; i++) {
        if (carrinho->produto[i].id == id) {
            if (carrinho->quant < 50) {
                carrinho->carrinho[carrinho->quant++] = carrinho->produto[i];
                printf("Produto adicionado com sucesso.\n");
            } else {
                printf("Carrinho cheio.\n");
            }
            return;
        }
    }
    printf("Produto não encontrado.\n");
}

// Função que exibe o menu e executa a ação correspondente
void menu(int opcao, Carrinho *carrinho) {
    int continuar;
    switch (opcao) {
        case 1:  // Cadastrar produto
            do {
                printf("Digite o nome do produto:\n");
                scanf("%29s", carrinho->produto[cont].nome);
                printf("Digite o preço do produto:\n");
                scanf("%f", &carrinho->produto[cont].preco);
                carrinho->produto[cont].id = ++cont;
                printf("Produto cadastrado com ID: %d\n", carrinho->produto[cont - 1].id);
                
                printf("Digite 0 para sair ou 1 para continuar cadastrando\n");
                scanf("%d", &continuar);
                while (continuar != 0 && continuar != 1) {
                    printf("Número não reconhecido, tente novamente:\n");
                    scanf("%d", &continuar);
                }
            } while (continuar == 1);
            break;
        case 2:  // Exibir produtos cadastrados
            printf("Exibindo produtos\n");
            cadasProduto(carrinho);
            break;
        case 3:  // Adicionar ao carrinho
            printf("Digite o ID do produto que você deseja colocar no carrinho:\n");
            int id;
            scanf("%d", &id);
            adcarrinho(carrinho, id);
            break;
        case 4:  // Finalizar compras
            printf("Obrigado e volte sempre!\n");
            valorTotal(carrinho);
            break;
        case 5:  // Exibir o carrinho
            exibirCar(carrinho);
            break;
        case 6:  // Atualizar preço de produto
            printf("Digite o ID do produto que você deseja atualizar o preço:\n");
            scanf("%d", &id);
            float preco;
            printf("Digite o novo preço do produto:\n");
            scanf("%f", &preco);
            atualizarPedido(carrinho, id, preco);
            break;
        case 7:  // Remover produto
            printf("Digite o ID do produto que você deseja remover:\n");
            scanf("%d", &id);
            remoPedido(carrinho, id);
            break;
        default:
            printf("Opção inválida!\n");
            break;
    }
}

int main() {
    int opcao;
    Carrinho carrinho;  // Inicialização
    carrinho.quant = 0; // Inicializar a quantidade do carrinho

    do {
        printf("\nOlá, seja bem-vindo ao Mercantil Bem-Barato!!!!\n");
        printf("Escolha uma das seguintes opções:\n");
        printf("Digite 1 para cadastrar um produto\n");
        printf("Digite 2 para ver produtos cadastrados\n");
        printf("Digite 3 para adicionar os produtos ao carrinho\n");
        printf("Digite 4 para finalizar compras\n");
        printf("Digite 5 para exibir o carrinho\n");
        printf("Digite 6 para atualizar o preço do produto\n");
        printf("Digite 7 para remover o produto\n");
        printf("Digite 0 para sair do sistema\n");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida, por favor, digite um número.\n");
            // Limpa o buffer de entrada em caso de erro
            while (getchar() != '\n');  // Limpa caracteres até encontrar nova linha
            opcao = -1;  // Define um valor inválido para repetir o loop
        }

        if (opcao < 0 || opcao > 7) {
            printf("Opção inválida! Tente novamente.\n");
        } else if (opcao != 0) {
            menu(opcao, &carrinho);  // Passando carrinho corretamente por referência
        }

    } while (opcao != 0);

    printf("Sistema encerrado.\n");  

    return 0;
}

