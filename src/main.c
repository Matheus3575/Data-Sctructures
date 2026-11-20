#include <stdio.h>
#include <stdlib.h>
#include "abb.h"
#include "atividade.h"

int main(void) {
    ABB *arvore = criarAbb();
    if (arvore == NULL) {
        printf("Erro ao inicializar a Árvore.\n");
        return 1;
    }

    printf("=== ESTADO INICIAL ===\n");
    printf("Nos: %d | Altura: %d\n\n", contarNo(arvore), calcularAltura(arvore));

    printf("=== CADASTRO DE ATIVIDADES ===\n");
    inserirAbb(arvore, criarAtividade(50, "Minicurso Entendendo Algoritmos", 40));
    inserirAbb(arvore, criarAtividade(30, "Minicurso de docker", 25));
    inserirAbb(arvore, criarAtividade(70, "Palestra com Jensen Huang", 35));
    inserirAbb(arvore, criarAtividade(20, "Minicurso: Git e Controle de Versao", 50));
    inserirAbb(arvore, criarAtividade(40, "Palestra com WALL-E", 30));
    inserirAbb(arvore, criarAtividade(60, "Minicurso: Como sair do sedentarismo", 20));
    inserirAbb(arvore, criarAtividade(80, "Palestra: Como fui perseguido por um ornitorrinco", 45));

    printf("Nos apos insercoes: %d | Altura: %d\n\n", contarNo(arvore), calcularAltura(arvore));

    printf("=== TESTE DE DUPLICIDADE ===\n");
    Atividade *duplicada = criarAtividade(30, "Atividade Repetida", 10);
    if (!inserirAbb(arvore, duplicada)) {
        printf("Codigo 30 bloqueado corretamente.\n");
        destruirAtividade(duplicada);
    }
    printf("Nos apos tentativa duplicada: %d\n\n", contarNo(arvore));

    printf("=== BUSCA POR CODIGO ===\n");
    Atividade *buscada = buscarAtividade(arvore, 40);
    if (buscada != NULL) {
        printf("Encontrada: [%d] %s (Capacidade: %d)\n",
               buscada->codigo, buscada->titulo, buscada->capacidade);
    } else {
        printf("A atividade 40 nao foi encontrada.\n");
    }

    if (buscarAtividade(arvore, 99) == NULL) {
        printf("Codigo 99 nao encontrado (correto).\n\n");
    }

    printf("=== PERCURSO EM ORDEM (LISTAR) ===\n");
    calcularPercurso(arvore, true);

    printf("\n=== PERCURSO EM ORDEM (RELATORIO) ===\n");
    calcularPercurso(arvore, false);

    return 0;
}