#ifndef ATIVIDADE_H
#define ATIVIDADE_H


typedef struct Atividade{
    int codigo;
    char titulo[100];
    int capacidade;
    int qtdInscritos;
    int qtdEspera; 

    /* É necessário implementar a lista de inscritos e a fila de espera */
} Atividade;

Atividade *criarAtividade(const int codigo, const char* titulo, int capacidade);
void destruirAtividade(Atividade *atividade);

#endif