#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 8
#define MOD 256

typedef struct tree *p_tree;

struct tree {
    p_tree pai;
    char *operador;
    p_tree esq;
    p_tree dir;
};

int mod(int n) {
/*
Retorna n mod MOD, com MOD definido

-- Parameters:

---- n (int): Inteiro

-- Return:

---- n (int): n modificado
*/
    if (n >= 0) {
        return n % MOD;
    } else {
        while (n<0) {
            n += MOD;
        }
        return n % MOD;
    }
}

void criar_arvore(p_tree arvore, char *valor) {
/*
Lê do teclado uma expressão e altera a árvore passada por referência, transformando
a expressão numa árvore binária

-- Parameters:

---- arvore (p_tree): Ponteiro para struct tree

---- valor (char *): Ponteiro de char (string)
*/
    while (scanf("%s ", valor) != EOF) {
        if (valor[0]==' ') {
            criar_arvore(arvore, valor);
        }
        if (valor[0]=='(') {
            arvore->esq = malloc(sizeof(struct tree));
            arvore->esq->operador = malloc(MAX*sizeof(char));
            arvore->esq->operador[0] = '0';
            arvore->esq->pai = arvore;
            criar_arvore(arvore->esq, valor);
        } else if (valor[0]=='+' || valor[0]=='-' || valor[0]=='*' || valor[0]=='/') {
            p_tree aux = arvore->pai; 
            while ((aux->operador)[0] != '0') {
                aux = aux->pai;
            }
            strcpy(aux->operador, valor);
            aux->dir = malloc(sizeof(struct tree));
            aux->dir->operador = malloc(MAX*sizeof(char));
            aux->dir->operador[0] = '0';
            aux->dir->pai = aux;
            criar_arvore(aux->dir, valor);
        } else if (valor[0]==')') {
            criar_arvore(arvore->pai, valor);
        } else {
            arvore->esq = NULL;
            arvore->dir = NULL;
            strcpy(arvore->operador, valor);
            criar_arvore(arvore, valor);
        }
    }
    return;
}

void destruir_arvore(p_tree arvore) {
/*
Libera toda a memória alocada em uma arvore

-- Parameters:

---- arvore (p_tree): Ponteiro para struct tree
<<<<<<< HEAD
=======

---- valor (char *): Ponteiro de char (string)
>>>>>>> 6cc391848f6994c3f74437c5013fd52e1ecb4081
*/
    if (arvore!=NULL) {
        destruir_arvore(arvore->esq);
        destruir_arvore(arvore->dir);
        free(arvore->operador);
        free(arvore);
    }
}

int eh_num(char *str) {
/*
Retorna 1 se a string passada é um número, retorna 0 caso contrário

-- Parameters:

---- str (char *): Ponteiro para char (string)

-- Return:

---- 1 ou 0 (int): Verdadeiro ou Falso
*/
    if (!strcmp(str,"0")) {
        return 1;
    } else if (atoi(str)) {
        return 1;
    } else {
        return 0;
    }
}

void ler_express(p_tree arvore) {
/*
Lê a árvore da expressão otimizada e mostra na tela

-- Parameters:

---- arvore (p_tree): Ponteiro para struct tree
*/
    if (arvore!=NULL) {
        if (arvore->operador[0]=='+' || arvore->operador[0]=='-' ||
            arvore->operador[0]=='*' || arvore->operador[0]=='/') {
                printf("( ");
                ler_express(arvore->esq);
                printf(" %s ", arvore->operador);
                ler_express(arvore->dir);
                printf(" )");
        } else {
            printf("%s", arvore->operador);
        }
    }
}

void sobe(p_tree no) {
/*
Recebe um nó que é operador e tem dois filhos numéricos e realiza a operação pedida

-- Parameters:

---- no (p_tree): Ponteiro para struct tree
*/
    char operador = (no->operador)[0];
    int valor;
    if (operador == '+') {
        valor = mod(atoi(no->esq->operador) + atoi(no->dir->operador));
        sprintf(no->operador,"%d",valor);
        destruir_arvore(no->esq);
        destruir_arvore(no->dir);
        no->esq = NULL;
        no->dir = NULL;
        return;
    } else if (operador == '-') {
        valor = mod(atoi(no->esq->operador) - atoi(no->dir->operador));
        sprintf(no->operador,"%d",valor);
        destruir_arvore(no->esq);
        destruir_arvore(no->dir);
        no->esq = NULL;
        no->dir = NULL;
        return;
    } else if (operador == '*') {
        valor = mod(atoi(no->esq->operador) * atoi(no->dir->operador));
        sprintf(no->operador,"%d",valor);
        destruir_arvore(no->esq);
        destruir_arvore(no->dir);
        no->esq = NULL;
        no->dir = NULL;
        return;
    } else if (operador == '/') {
        valor = mod(atoi(no->esq->operador) / atoi(no->dir->operador));
        sprintf(no->operador,"%d",valor);
        destruir_arvore(no->esq);
        destruir_arvore(no->dir);
        no->esq = NULL;
        no->dir = NULL;
        return;
    }
}

void otimizar(p_tree arvore) {
/*
Otimiza a expressão na forma de árvore

-- Parameters:

---- arvore (p_tree): Ponteiro para struct tree
*/
    if (arvore != NULL && arvore->esq!=NULL && arvore->dir!=NULL) {
        otimizar(arvore->esq);
        otimizar(arvore->dir);
        if (eh_num(arvore->esq->operador) && eh_num(arvore->dir->operador)) {
            sobe(arvore);
        }
    }
}

int main() {
    char valor[MAX];
    p_tree raiz = malloc(sizeof(struct tree));
    raiz->pai = NULL;
    raiz->operador = malloc(MAX*sizeof(char));
    (raiz->operador)[0] = '0';
    criar_arvore(raiz, valor);
    otimizar(raiz);
    ler_express(raiz);
    printf("\n");
    destruir_arvore(raiz);
}
