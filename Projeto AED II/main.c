#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers/espaconave.h"

int main() {
    srand(time(NULL));

    Espaconave nave;
    inicializarEspaconave(&nave);

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Verificar dados e ajustar prioridade\n");
        printf("2. Inserir novo passageiro\n");
        printf("3. Remover passageiro\n");
        printf("4. Listar passageiros da espaçonave\n");
        printf("5. Salvar dados para arquivo\n");
        printf("6. Carregar dados do arquivo\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        // Limpar o buffer de entrada para evitar problemas com entradas inválidas
        while (getchar() != '\n');

        switch (opcao) {
            case 1:
                verificarDados(&nave);
                printf("Dados verificados e prioridade ajustada.\n");
                break;
            case 2: {
                Passageiro novoPassageiro;
                printf("Nome: ");
                scanf("%s", novoPassageiro.nome);
                printf("Idade: ");
                scanf("%d", &novoPassageiro.idade);
                printf("Identificador: ");
                scanf("%d", &novoPassageiro.identificador);
                printf("Planeta de Origem: ");
                scanf("%s", novoPassageiro.planeta_origem);
                printf("Quantidade de oxigênio: ");
                scanf("%d", &novoPassageiro.quantidade_oxigenio);
                printf("Quantidade de comida: ");
                scanf("%d", &novoPassageiro.quantidade_comida);

                // Validar entrada (por exemplo, garantir que o identificador seja positivo)
                if (novoPassageiro.identificador <= 0) {
                    printf("Erro: Identificador inválido. Deve ser um número inteiro positivo.\n");
                } else {
                    inserirPassageiro(&nave, novoPassageiro);
                    printf("Passageiro inserido na espaçonave.\n");
                }
                break;
            }
            case 3: {
                int identificador;
                printf("Digite o identificador do passageiro a ser removido: ");
                scanf("%d", &identificador);

                // Validar entrada
                if (identificador <= 0) {
                    printf("Erro: Identificador inválido. Deve ser um número inteiro positivo.\n");
                } else {
                    removerPassageiro(&nave, identificador);
                    printf("Passageiro removido da espaçonave.\n");
                }
                break;
            }
            case 4:
                // Lista os passageiros da espaçonave
                printf("Passageiros da espaçonave:\n");
                imprimirPassageiros(nave.passageiros);
                break;
            case 5: {
                char nomeArquivo[100];
                printf("Digite o nome do arquivo para salvar os dados: ");
                scanf("%s", nomeArquivo);
                salvarDadosParaArquivo(&nave, nomeArquivo);
                printf("Dados salvos no arquivo com sucesso.\n");
                break;
            }
            case 6: {
                char nomeArquivo[100];
                printf("Digite o nome do arquivo para carregar os dados: ");
                scanf("%s", nomeArquivo);
                carregarDadosDoArquivo(&nave, nomeArquivo);
                printf("Dados carregados do arquivo com sucesso.\n");
                break;
            }
            case 7:
                // Liberar memória e sair do programa
                liberarEspaconave(&nave);
                exit(0);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 7);

    return 0;
}
