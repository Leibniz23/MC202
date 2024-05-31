#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func4.h"

char *str_concat(char *str_1, char *str_2, int pos) {
    char *buffer;
    int n = strlen(str_1) + strlen(str_2)+1; //-1 por causa do \0
    buffer = malloc(n*sizeof(char));
    int i;
    for (i=0; i<=pos; i++) {
        buffer[i] = str_1[i];
    }
    for (i=pos+1; i<=strlen(str_2)+pos; i++) {
        buffer[i] = str_2[i-(pos+1)];
    }
    for (i=pos+1; i<strlen(str_1); i++) {
        int j = i+strlen(str_2);
        buffer[j] = str_1[i];
    }
    buffer[n-1] = '\0';
    return buffer;
}

void remover_no(p_no lista, p_no no) {
    if (lista==no) {
        free(lista);
        return;
    }
    if (lista->prox==NULL) {
        printf("Elemento não existe\n");
        return;
    }
    p_no aux = lista->prox;
    while (True) {
        if (lista->prox == no) {
            lista->prox = no->prox;
            free(no);
            break;
        }
        aux = aux->prox;
    }
}

p_no encontrar_no(p_no lista, int index) {
    if (lista->prox == NULL) {
        printf("Indice não existe\n");
        return;
    }
    p_no aux = lista;
    while(True) {
        if (aux->inter.ini <= index < aux->inter.fim) {
            return aux;
        }
        aux = aux->prox;
    }
    printf("Indice não existe\n");
    return;
}