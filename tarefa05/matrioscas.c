#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "func5.h"

int main() {
    p_pilha pilha = criar_pilha();
    int n;
    int flag = False;
    p_no result = criar_lista();
    scanf("%d", &n);
    int novo;
    while (scanf("%d ", &novo) != EOF) {
        if (novo>0) {
            if (pilha->tam_pilha!=0) {
                pilha->topo->boneca.soma += novo;
                pilha->topo->boneca.cont++;
                push(pilha, novo);
                pilha->tam_pilha++;
            } else {
                push(pilha, novo);
                pilha->tam_pilha++;
            }
        } else {
            if (abs(novo)==pilha->topo->boneca.k) {
                if (pilha->topo->boneca.soma == 0 || pilha->topo->boneca.soma == (pilha->topo->boneca.k)-1) {
                    result->prox = adicionar_ordenado(result->prox, pilha->topo);
                    pop(pilha);
                    pilha->tam_pilha--;
                } else {
                    flag = True;
                    break;
                }
            } else {
                flag = True;
                break;
            }
        }
    }

    if (pilha->topo!=NULL || flag) {
        destruir_pilha(pilha);
        printf("sequencia invalida");
    } else {
        p_no aux = result->prox;
        while (aux!=NULL) {
            p_no aux2 = aux->prox;
            printf("%d contem %d bonecas\n", aux->boneca.k, aux->boneca.cont);
            free(aux);
            aux = aux2;
        }
        free(result);
        destruir_pilha(pilha);
    }
}
