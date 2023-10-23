#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/passageiros.h"

ListaPassageiros* criarListaPassageiros() {
    ListaPassageiros *lista = (ListaPassageiros *)malloc(sizeof(ListaPassageiros));
    lista->passageiros = NULL;
    lista->tamanho = 0;
    return lista;
}

void destruirListaPassageiros(ListaPassageiros *lista) {
    free(lista->passageiros);
    free(lista);
}

void adicionarPassageiro(ListaPassageiros *lista, char nome[], int idade, int identificador, char planeta_origem[], int quantidade_oxigenio, int quantidade_comida) {
    lista->tamanho++;
    lista->passageiros = (Passageiro *)realloc(lista->passageiros, lista->tamanho * sizeof(Passageiro));
    strcpy(lista->passageiros[lista->tamanho - 1].nome, nome);
    lista->passageiros[lista->tamanho - 1].idade = idade;
    lista->passageiros[lista->tamanho - 1].identificador = identificador;
    strcpy(lista->passageiros[lista->tamanho - 1].planeta_origem, planeta_origem);
    lista->passageiros[lista->tamanho - 1].quantidade_oxigenio = quantidade_oxigenio;
    lista->passageiros[lista->tamanho - 1].quantidade_comida = quantidade_comida;
}

void removerPassageiroPorIdentificador(ListaPassageiros *lista, int identificador) {
    int i, j = 0;
    for (i = 0; i < lista->tamanho; i++) {
        if (lista->passageiros[i].identificador == identificador) {
            for (j = i; j < lista->tamanho - 1; j++) {
                lista->passageiros[j] = lista->passageiros[j + 1];
            }
            break;
        }
    }
    if (i != lista->tamanho) {
        lista->tamanho--;
        lista->passageiros = (Passageiro *)realloc(lista->passageiros, lista->tamanho * sizeof(Passageiro));
    }
}

void imprimirPassageiros(ListaPassageiros *lista) {
    for (int i = 0; i < lista->tamanho; i++) {
        printf("Nome: %s, Idade: %d, Identificador: %d, Planeta de Origem: %s, Oxigênio: %d, Comida: %d\n",
               lista->passageiros[i].nome, lista->passageiros[i].idade,
               lista->passageiros[i].identificador, lista->passageiros[i].planeta_origem,
               lista->passageiros[i].quantidade_oxigenio, lista->passageiros[i].quantidade_comida);
    }
}
