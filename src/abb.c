#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "abb.h"

typedef struct no{
    Atividade *atividade;
    struct no *esq;
    struct no *dir;
} No;

struct abb{
    No *raiz;
    int countNos;
};

/* Cria uma estrutura do tipo árvore binária de busca*/
ABB *criarAbb(void){
    ABB *arvore = malloc(sizeof(ABB));
    if (arvore == NULL){
        return NULL;
    };

    arvore->raiz = NULL;
    arvore->countNos = 0;
    return arvore;
}

/* Destroi uma árvore recursivamente a partir da raiz em pós-ordem */
static void destruir(No *raiz){
    if(raiz != NULL){
        destruir(raiz->esq);
        destruir(raiz->dir);
        destruirAtividade(raiz->atividade);
        free(raiz);
    }
}

/* Destroi uma árvore binária de busca */
void destruirAbb(ABB *arvore){
    if(arvore != NULL){
        destruir(arvore->raiz);
        free(arvore);
    }
}

/* Cria uma estrutura do tipo Nó*/
static No *criarNo(void){
    No *novoNo = malloc(sizeof(No));
    if(novoNo == NULL){
        return NULL;
    }

    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->atividade = NULL;
    return novoNo;
}

/* Tenta inserir uma atividade em uma árvore não vazia */
static bool inserir(No *raiz, Atividade *atividade){

    if(raiz != NULL && raiz->atividade->codigo != atividade->codigo){

        /* Tenta inserir à esquerda */
        if(raiz->atividade->codigo > atividade->codigo){
            if(raiz->esq != NULL){
                return inserir(raiz->esq, atividade);
            }else{
                No *novoFilho = criarNo();
                if(novoFilho != NULL){
                    novoFilho->atividade = atividade;
                    raiz->esq = novoFilho;
                    return true;
                }else{
                    return false;
                }
            }
        }else{

            /* Tenta inserir à direita */
            if(raiz->dir != NULL){
                return inserir(raiz->dir, atividade);
            }else{
                No *novoFilho = criarNo();
                if(novoFilho != NULL){
                    novoFilho->atividade = atividade;
                    raiz->dir = novoFilho;
                    return true;
                }else{
                    return false;
                }
            }
        }
    }else{
        /* Se não houver raiz ou a atividade ser duplicada, a inserção falha. */
        return false;
    }
}

/* Tenta inserir uma atividade em uma árvore */
bool inserirAbb(ABB *arvore, Atividade *atividade){
    if (arvore == NULL || atividade == NULL){
        return false;
    }

    /* Se a árvore está vazia, um novo nó vira a raiz e a atividade é anexada ao novo nó */
    if (arvore->raiz == NULL){
        No *novoNo = criarNo();
        if(novoNo == NULL){
            return false;
        }
        novoNo->atividade = atividade;
        arvore->raiz = novoNo;
        arvore->countNos++;
        return true;   
    }

    /* Se a árvore não está vazia, tenta executar uma inserção na árvore */
    if(inserir(arvore->raiz, atividade) == true){
        arvore->countNos++;
        return true;
    }else{
        return false;
    }
}

/* Retorna a contagem dos nós de uma árvore aproveitando o descritor existente */
int contarNo(ABB *arvore){
    if(arvore == NULL){
        return 0;
    }
    return arvore->countNos;
}

/* Busca uma atividade para uma raiz especificada */
static Atividade *buscar(No *raiz, int codigo){
    if(raiz != NULL){
        if(raiz->atividade->codigo == codigo){
            return raiz->atividade;
        }else if(raiz->atividade->codigo > codigo){
                return buscar(raiz->esq, codigo);
        }else{
            return buscar(raiz->dir, codigo);
        }
    }else{
        return NULL;
    }
}

/* Faz uma busca por uma atividade em uma árvore com base no código da atividade */
Atividade *buscarAtividade(ABB *arvore, int codigo){
    if(arvore == NULL || arvore->raiz == NULL){
        return NULL;
    }
    return buscar(arvore->raiz, codigo);
}

/* Calcula a altura da árvore a partir de uma raiz */
static int calcAltura(No *raiz, int contagem){ 
    if(raiz != NULL){
        contagem = contagem + 1;
        int altEsqueda = calcAltura(raiz->esq, contagem);
        int altDireita = calcAltura(raiz->dir, contagem);
        if( altEsqueda > altDireita){
            contagem = altEsqueda;
        }else{
            contagem = altDireita;
        }
        return contagem;
    }else{
        return contagem;
    }
}

/* Calcula a altura, isto é, a maior distância da raiz até uma folha de uma árvore */
int calcularAltura(ABB *arvore){
    if(arvore == NULL){
        return -1;
    }
    int contagem = -1;
    return calcAltura(arvore->raiz, contagem);
}

/* Imprime os dados da atividade Em-Ordem */
/* Se o comando for true imprime a atividade, se for false imprime o resumo*/
static void emOrdem(No *raiz, bool comando){
    if(raiz != NULL){
        emOrdem(raiz->esq, comando);
        if(comando == true){
            printf("ATIVIDADE ");
            printf("%d %s %d %d %d\n", 
            raiz->atividade->codigo,
            raiz->atividade->titulo, raiz->atividade->capacidade,
            raiz->atividade->qtdInscritos, raiz->atividade->qtdEspera);
        }else{
            printf("RESUMO ");
            printf("%d %d %d %d\n", 
            raiz->atividade->codigo, raiz->atividade->capacidade,
            raiz->atividade->qtdInscritos, raiz->atividade->qtdEspera);
        }
        emOrdem(raiz->dir, comando);
    }
}

/* Calcular percurso de uma árvore */
/* Se o comando for true ele lista, se for false ele imprime o relatório*/
void calcularPercurso(ABB *arvore, bool comando){
    if(comando == true){
        printf("LISTAR %d\n", contarNo(arvore));
        if(arvore != NULL){
            emOrdem(arvore->raiz, comando);
        }
    }else{
        printf("RELATORIO %d\n", contarNo(arvore));
        if(arvore != NULL){
            emOrdem(arvore->raiz, comando);
        }
    }
}