#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../headers/espaconave.h"
#include "../headers/passageiros.h"

void inicializarEspaconave(Espaconave *nave) {
    nave->prioridade = rand() % 100;
    nave->passageiros = criarListaPassageiros();
    nave->recursos.quantidade_oxigenio = rand() % 100;
    nave->recursos.quantidade_comida = rand() % 100;
    nave->ultima_expansao = time(NULL);  // Inicializa o momento da última expansão
}

void inserirPassageiro(Espaconave *nave, Passageiro passageiro) {
    adicionarPassageiro(nave->passageiros, passageiro.nome, passageiro.idade, passageiro.identificador, passageiro.planeta_origem, passageiro.quantidade_oxigenio, passageiro.quantidade_comida);
    calcularPrioridade(nave);
}

void removerPassageiro(Espaconave *nave, int identificador) {
    removerPassageiroPorIdentificador(nave->passageiros, identificador);
    calcularPrioridade(nave);
}

void calcularPrioridade(Espaconave *nave) {
    nave->prioridade = rand() % 100;

    if (rand() % 10 == 0) {
        printf("Espaçonave contém clandestinos! Prioridade aumentada.\n");
        nave->prioridade += 20; // Aumenta a prioridade em 20 pontos
    }

    if (rand() % 20 == 0) {
        printf("Doenças a bordo! Prioridade aumentada.\n");
        nave->prioridade += 10; // Aumenta a prioridade em 10 pontos
    }

    if (rand() % 3 == 0) {
        printf("Recursos escassos! Prioridade aumentada.\n");
        nave->prioridade += 5; // Aumenta a prioridade em 5 pontos
    }

    if (nave->prioridade > 100) {
        nave->prioridade = 100;
    } else if (nave->prioridade < 0) {
        nave->prioridade = 0;
    }
}

// Altere o protótipo da função next_permutation para aceitar um ponteiro e o tamanho do array
int next_permutation(int *array, int size) {
    for (int i = size - 2; i >= 0; i--) {
        if (array[i] < array[i + 1]) {
            for (int j = size - 1; j > i; j--) {
                if (array[j] > array[i]) {
                    // Swap array[i] and array[j]
                    int temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                    
                    // Reverse the suffix
                    for (int l = i + 1, r = size - 1; l < r; l++, r--) {
                        int temp = array[l];
                        array[l] = array[r];
                        array[r] = temp;
                    }
                    return 1; // Permutation generated successfully
                }
            }
        }
    }
    return 0; // No more permutations
}

bool verificarPermutacoes(int *recursos, int tamanho) {
    int *contador = (int *)malloc(tamanho * sizeof(int));
    memset(contador, 0, tamanho * sizeof(int));

    for (int i = 0; i < tamanho; i++) {
        if (contador[recursos[i]] > 0) {
            free(contador);
            return false;
        }
        contador[recursos[i]]++;
    }

    free(contador);
    return true;
}

bool verificarExpansao(Espaconave *nave) {
    if (nave->passageiros->tamanho < 2) {
        printf("Não há nave suficiente para verificar a expansão.\n");
        return false;
    }

    int recursos[2] = {
        nave->passageiros->passageiros[nave->passageiros->tamanho - 1].quantidade_oxigenio,
        nave->passageiros->passageiros[nave->passageiros->tamanho - 1].quantidade_comida};

    for (int i = 0; i < nave->passageiros->tamanho - 1; i++) {
        int perm[2] = {recursos[0], recursos[1]};
        do {
            if (verificarPermutacoes(perm, 2)) {
                printf("Expansão da abertura ocorreu!\n");
                nave->ultima_expansao = time(NULL);
                return true;
            }
        } while (next_permutation(perm, 2));  // Corrigido o argumento para 2, indicando o tamanho do array.

        int oxigenio_comparado = nave->passageiros->passageiros[i].quantidade_oxigenio;
        int comida_comparada = nave->passageiros->passageiros[i].quantidade_comida;

        recursos[0] = oxigenio_comparado;
        recursos[1] = comida_comparada;
    }

    printf("A expansão da abertura não ocorreu.\n");
    return false;
}

void adicionarNaves(Espaconave *nave) {
    int quantidade_naves = rand() % 10; // Adiciona até 10 novas naves à fila (quantidade aleatória)
    for (int i = 0; i < quantidade_naves; ++i) {
        Espaconave nova_nave;
        inicializarEspaconave(&nova_nave);
        // Adicione a nova nave à fila ou faça o que for necessário com ela
        // Por exemplo, você pode usar uma lista encadeada para manter as naves em espera.
    }
}

void atualizarPrioridades(Espaconave *nave) {
    nave->prioridade = rand() % 100;

    if (rand() % 10 == 0) {
        printf("Espaçonave contém clandestinos! Prioridade aumentada.\n");
        nave->prioridade += 20;
    }

    if (rand() % 20 == 0) {
        printf("Doenças a bordo! Prioridade aumentada.\n");
        nave->prioridade += 10;
    }

    if (rand() % 3 == 0) {
        printf("Recursos escassos! Prioridade aumentada.\n");
        nave->prioridade += 5;
    }

    if (nave->prioridade > 100) {
        nave->prioridade = 100;
    } else if (nave->prioridade < 0) {
        nave->prioridade = 0;
    }
}

void liberarEspaconave(Espaconave *nave) {
    destruirListaPassageiros(nave->passageiros);
}

void salvarDadosParaArquivo(Espaconave *nave, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escrever dados da espaçonave no arquivo
    fprintf(arquivo, "Prioridade: %d\n", nave->prioridade);
    fprintf(arquivo, "Quantidade de oxigênio: %d\n", nave->recursos.quantidade_oxigenio);
    fprintf(arquivo, "Quantidade de comida: %d\n", nave->recursos.quantidade_comida);

    // Escrever dados dos passageiros no arquivo
    ListaPassageiros *lista = nave->passageiros;
    for (int i = 0; i < lista->tamanho; i++) {
        fprintf(arquivo, "Nome: %s, Idade: %d, Identificador: %d, Planeta de Origem: %s, Oxigênio: %d, Comida: %d\n",
               lista->passageiros[i].nome, lista->passageiros[i].idade,
               lista->passageiros[i].identificador, lista->passageiros[i].planeta_origem,
               lista->passageiros[i].quantidade_oxigenio, lista->passageiros[i].quantidade_comida);
    }

    fclose(arquivo);
}

void carregarDadosDoArquivo(Espaconave *nave, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    // Ler dados da espaçonave do arquivo
    fscanf(arquivo, "Prioridade: %d", &nave->prioridade);
    fscanf(arquivo, "Quantidade de oxigênio: %d", &nave->recursos.quantidade_oxigenio);
    fscanf(arquivo, "Quantidade de comida: %d", &nave->recursos.quantidade_comida);

    // Ler dados dos passageiros do arquivo e adicioná-los à lista de passageiros
    Passageiro passageiro;
    while (fscanf(arquivo, "Nome: %s, Idade: %d, Identificador: %d, Planeta de Origem: %s, Oxigênio: %d, Comida: %d\n",
                  passageiro.nome, &passageiro.idade, &passageiro.identificador, passageiro.planeta_origem,
                  &passageiro.quantidade_oxigenio, &passageiro.quantidade_comida) != EOF) {
        adicionarPassageiro(nave->passageiros, passageiro.nome, passageiro.idade, passageiro.identificador, passageiro.planeta_origem, passageiro.quantidade_oxigenio, passageiro.quantidade_comida);
    }

    fclose(arquivo);
}
