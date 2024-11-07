#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 50
#define MAX_NOME 30

typedef struct {
    char nome[MAX_NOME];
    int id;
    float preco;
} Produto;

typedef struct {
    int quant;
    Produto produto[MAX_PRODUTOS];
    Produto carrinho[MAX_PRODUTOS];
} Carrinho;

int cont = 0;  // Vari�vel para controle de IDs

// Fun��o para limpar o buffer de entrada
void limparBuffer() {
    while (getchar() != '\n');
}

// Fun��o para verificar se o ID � v�lido
int idValido(int id, Produto *produtos, int qtd) {
    for (int i = 0; i < qtd; i++) {
        if (produtos[i].id == id) {
            return 1;
        }
    }
    return 0;
}

// Fun��o para cadastrar um produto
void cadastrarProduto(Carrinho *carrinho) {
    int continuar;
    do {
        printf("Digite o nome do produto (m�ximo de 29 caracteres):\n");
        fgets(carrinho->produto[cont].nome, MAX_NOME, stdin);
        carrinho->produto[cont].nome[strcspn(carrinho->produto[cont].nome, "\n")] = '\0';  // Remove o '\n' deixado pelo fgets

        printf("Digite o pre�o do produto:\n");
        while (scanf("%f", &carrinho->produto[cont].preco) != 1) {
            printf("Entrada inv�lida. Digite novamente o pre�o:\n");
            limparBuffer();
        }
        
        carrinho->produto[cont].id = ++cont;
        printf("Produto cadastrado com ID: %d\n", carrinho->produto[cont - 1].id);
        
        printf("Digite 0 para sair ou 1 para continuar cadastrando\n");
        while (scanf("%d", &continuar) != 1 || (continuar != 0 && continuar != 1)) {
            printf("N�mero n�o reconhecido, tente novamente:\n");
            limparBuffer();
        }
        
        limparBuffer();
    } while (continuar == 1);
}

// Fun��o para exibir todos os produtos cadastrados
void exibirProdutos(Carrinho *carrinho) {
    if (cont == 0) {
        printf("Nenhum produto cadastrado.\n");
    } else {
        printf("Produtos cadastrados:\n");
        for (int i = 0; i < cont; i++) {
            printf("ID: %d | Nome: %s | Pre�o: %.2f\n", carrinho->produto[i].id, carrinho->produto[i].nome, carrinho->produto[i].preco);
        }
    }
}

// Fun��o para adicionar produto ao carrinho
void adicionarCarrinho(Carrinho *carrinho, int id) {
    if (!idValido(id, carrinho->produto, cont)) {
        printf("Produto n�o encontrado.\n");
        return;
    }

    if (carrinho->quant < MAX_PRODUTOS) {
        for (int i = 0; i < cont; i++) {
            if (carrinho->produto[i].id == id) {
                carrinho->carrinho[carrinho->quant++] = carrinho->produto[i];
                printf("Produto adicionado com sucesso.\n");
                return;
            }
        }
    } else {
        printf("Carrinho cheio.\n");
    }
}

// Fun��o para exibir o carrinho
void exibirCarrinho(Carrinho *carrinho) {
    if (carrinho->quant == 0) {
        printf("Carrinho vazio.\n");
    } else {
        printf("Produtos no carrinho:\n");
        for (int i = 0; i < carrinho->quant; i++) {
            printf("ID: %d | Nome: %s | Pre�o: %.2f\n", carrinho->carrinho[i].id, carrinho->carrinho[i].nome, carrinho->carrinho[i].preco);
        }
    }
}

// Fun��o para calcular o valor total do carrinho
void valorTotal(Carrinho *carrinho) {
    float total = 0;
    printf("Pedido fechado. Produtos no pedido:\n");
    for (int i = 0; i < carrinho->quant; i++) {
        printf("ID: %d | Nome: %s | Pre�o: %.2f\n", carrinho->carrinho[i].id, carrinho->carrinho[i].nome, carrinho->carrinho[i].preco);
        total += carrinho->carrinho[i].preco;
    }
    printf("Valor total: R$%.2f\n", total);
}

// Fun��o para remover um produto do carrinho
void removerProduto(Carrinho *carrinho, int id) {
    int encontrado = 0;
    for (int i = 0; i < carrinho->quant; i++) {
        if (carrinho->carrinho[i].id == id) {
            encontrado = 1;
            for (int j = i; j < carrinho->quant - 1; j++) {
                carrinho->carrinho[j] = carrinho->carrinho[j + 1];
            }
            carrinho->quant--;
            printf("Produto removido com sucesso.\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Produto n�o encontrado no carrinho.\n");
    }
}

// Fun��o para atualizar o pre�o de um produto no carrinho
void atualizarPreco(Carrinho *carrinho, int id, float preco) {
    int encontrado = 0;
    for (int i = 0; i < carrinho->quant; i++) {
        if (carrinho->carrinho[i].id == id) {
            carrinho->carrinho[i].preco = preco;
            printf("Pre�o atualizado com sucesso.\n");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Produto n�o encontrado no carrinho.\n");
    }
}

// Fun��o para exibir o menu e gerenciar as op��es
void exibirMenu(Carrinho *carrinho) {
    int opcao;
    do {
        printf("\nOl�, seja bem-vindo ao Mercantil Bem-Barato!!!!\n");
        printf("Escolha uma das seguintes op��es:\n");
        printf("1. Cadastrar produto\n");
        printf("2. Exibir produtos cadastrados\n");
        printf("3. Adicionar produto ao carrinho\n");
        printf("4. Finalizar compras\n");
        printf("5. Exibir carrinho\n");
        printf("6. Atualizar pre�o de produto\n");
        printf("7. Remover produto do carrinho\n");
        printf("0. Sair\n");

        while (scanf("%d", &opcao) != 1) {
            printf("Entrada inv�lida. Tente novamente.\n");
            limparBuffer();
        }

        switch (opcao) {
            case 1:
                cadastrarProduto(carrinho);
                break;
            case 2:
                exibirProdutos(carrinho);
                break;
            case 3: {
                int id;
                printf("Digite o ID do produto a ser adicionado ao carrinho:\n");
                while (scanf("%d", &id) != 1 || !idValido(id, carrinho->produto, cont)) {
                    printf("ID inv�lido. Tente novamente.\n");
                    limparBuffer();
                }
                adicionarCarrinho(carrinho, id);
                break;
            }
            case 4:
                valorTotal(carrinho);
                break;
            case 5:
                exibirCarrinho(carrinho);
                break;
            case 6: {
                int id;
                float preco;
                printf("Digite o ID do produto a ser atualizado:\n");
                while (scanf("%d", &id) != 1 || !idValido(id, carrinho->carrinho, carrinho->quant)) {
                    printf("ID inv�lido. Tente novamente.\n");
                    limparBuffer();
                }
                printf("Digite o novo pre�o:\n");
                while (scanf("%f", &preco) != 1) {
                    printf("Pre�o inv�lido. Tente novamente.\n");
                    limparBuffer();
                }
                atualizarPreco(carrinho, id, preco);
                break;
            }
            case 7: {
                int id;
                printf("Digite o ID do produto a ser removido:\n");
                while (scanf("%d", &id) != 1 || !idValido(id, carrinho->carrinho, carrinho->quant)) {
                    printf("ID inv�lido. Tente novamente.\n");
                    limparBuffer();
                }
                removerProduto(carrinho, id);
                break;
            }
            case 0:
                printf("Sistema encerrado.\n");
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}

int main() {
    Carrinho carrinho = {0};  // Inicializa o carrinho
    exibirMenu(&carrinho);
    return 0;
}

