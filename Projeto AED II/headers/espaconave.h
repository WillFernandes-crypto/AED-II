#ifndef ESPACONAVE_H
#define ESPACONAVE_H

#include <stdbool.h>
#include "passageiros.h"

typedef struct {
    int quantidade_oxigenio;
    int quantidade_comida;
} Recursos;

typedef struct {
    int prioridade;
    ListaPassageiros *passageiros;
    Recursos recursos;  // Recursos associados à espaçonave
    time_t ultima_expansao;
} Espaconave;


int next_permutation(int *array, int size);
void inicializarEspaconave(Espaconave *nave);
bool verificarExpansao(Espaconave *nave);
void adicionarNaves(Espaconave *nave);
void atualizarPrioridades(Espaconave *nave);
void liberarEspaconave(Espaconave *nave);
void inserirPassageiro(Espaconave *nave, Passageiro passageiro);
void removerPassageiro(Espaconave *nave, int identificador);
void calcularPrioridade(Espaconave *nave);
void salvarDadosParaArquivo(Espaconave *nave, const char *nomeArquivo);
void carregarDadosDoArquivo(Espaconave *nave, const char *nomeArquivo);

#endif /* ESPACONAVE_H */
