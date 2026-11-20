#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stdio.h>
#include "atividade.h"

typedef struct abb ABB;

/* Métodos básicos de criação de Nó e Árvore */
ABB *criarAbb(void);

/* Métodos de criação e destruição da ávore binária de busca */
bool inserirAbb(ABB *arvore, Atividade *atividade);
void destruirAbb(ABB *arvore);

/* Métodos de operações da árvore binária de busca */
Atividade *buscarAtividade(ABB *arvore, int codigo);
void calcularPercurso(ABB *arvore, bool comando);
int calcularAltura(ABB *arvore);
int contarNo(ABB *arvore);

#endif