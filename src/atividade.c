#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atividade.h"

Atividade *criarAtividade(const int codigo, const char* titulo, int capacidade){
    Atividade *novaAtividade = malloc(sizeof(Atividade));
    if(novaAtividade == NULL){
        return NULL;
    }
    novaAtividade->codigo = codigo;
    novaAtividade->capacidade = capacidade;
    novaAtividade->qtdInscritos = 0;
    novaAtividade->qtdEspera = 0;
    
    strncpy(novaAtividade->titulo, titulo, sizeof(novaAtividade->titulo) - 1);
    novaAtividade->titulo[sizeof(novaAtividade->titulo) - 1] = '\0';

    return novaAtividade;
}

void destruirAtividade(Atividade *atividade){
    if(atividade == NULL){
        return;
    }
    free(atividade);
}