#include <stdlib.h>
#include "func5.h"

p_no criar_lista() {
/*
Cria uma lista ligada vazia

Return:

---- result (p_no): Ponteiro para struct no
*/
    p_no lista = malloc(sizeof(struct no));
    lista->prox = NULL;
    return lista;
}

p_pilha criar_pilha() {
/*
Cria uma pilha vazia

Return:

---- pilha (p_pilha): Ponteiro para struct pilha
*/
    p_pilha pilha = malloc(sizeof(struct pilha));
    pilha->topo=NULL;
    pilha->tam_pilha=0;
    return pilha;
}

void push(p_pilha pilha, int x) {
/*
Adiciona o elemento x no topo da pilha
--Parameters:

---- pilha (p_pilha): Ponteiro para struct pilha

---- x (int) : Inteiro
*/
    p_no novo = malloc(sizeof(struct no));
    novo->boneca.k = x;
    novo->boneca.soma = 0;
    novo->boneca.cont = 0;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    return;
}

void pop(p_pilha pilha) {
/*
Remove o elemento no topo da pilha
--Parameters:

---- pilha (p_pilha): Ponteiro para struct pilha
*/
    p_no topo = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(topo);
    return;
}

p_no adicionar_ordenado(p_no lista, p_no novo) {
/*
Coloca uma cópia do novo elemento na lista na posição correta,
referente ao k, devolvendo uma nova lista com o elemento adicionado

--Parameters:

---- lista (p_no): Ponteiro para struct no

---- novo (p_no): Ponteiro para struct no

--Returns:

---- lista ou copia (p_no): Ponteiro para struct no
*/
    p_no copia = malloc(sizeof(struct no));
    copia->boneca.k = novo->boneca.k;
    copia->boneca.cont = novo->boneca.cont;
    copia->prox = NULL;

    p_no *aux = &lista;
    if (lista == NULL) { //se a lista está vazia
        lista = copia;
        return lista;
    }
    else if (copia->boneca.k < lista->boneca.k) { //se for o primeiro da lista
        copia->prox = lista;
        return copia;
    } else {
        while ((*aux) != NULL) {
            if ((*aux)->boneca.k == copia->boneca.k) { // não faz nada se o elemento já está na lista
                free(copia);
                return lista;
            } else if (copia->boneca.k < (*aux)->boneca.k) {
                break;
            }
            aux = &((*aux)->prox);
        }
        if ((*aux)!=NULL) { //se estiver no meio
            p_no aux2 = (*aux);
            (*aux) = copia;
            copia->prox = aux2;
            return lista;
        } else { //se for o ultimo
            (*aux) = copia;
            return lista;
        }
    }
}

void destruir_pilha(p_pilha pilha) {
/*
Libera toda a memória alocada dinamicamente na pilha
--Parameters:

---- pilha (p_pilha): Ponteiro para struct pilha
*/
    p_no aux = pilha->topo;
    while (aux != NULL) {
        p_no aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }
    free(pilha);
}