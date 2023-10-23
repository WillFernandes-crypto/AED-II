#ifndef PASSAGEIROS_H
#define PASSAGEIROS_H

typedef struct {
    char nome[100];
    int idade;
    int identificador;
    char planeta_origem[100];
    int quantidade_oxigenio;
    int quantidade_comida;
} Passageiro;

typedef struct {
    Passageiro *passageiros;
    int tamanho;
} ListaPassageiros;

ListaPassageiros* criarListaPassageiros();
void destruirListaPassageiros(ListaPassageiros *lista);
void adicionarPassageiro(ListaPassageiros *lista, char nome[], int idade, int identificador, char planeta_origem[], int quantidade_oxigenio, int quantidade_comida);
void removerPassageiroPorIdentificador(ListaPassageiros *lista, int identificador);
void imprimirPassageiros(ListaPassageiros *lista);

#endif /* PASSAGEIROS_H */
