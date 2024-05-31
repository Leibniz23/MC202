#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "func4.h"

void atualizar_index(p_no inicio, int fator) {
/*
Modifica o início e o fim de todos os nós, somando o fator dado, a partir do início.
--Parameters:

---- inicio (p_no): Ponteiro para struct no

---- fator (int): Inteiro
*/
    p_no aux = inicio;
    while(aux!=NULL) {
        aux->inter.ini += fator;
        aux->inter.fim += fator;
        aux = aux->prox;
    }
}

p_no encontrar_no(p_no lista, int index, p_no *ant) {
/*
Encontra, com base no índice fornecido, o nó correspondente, além de alterar o valor do
ant passado para o endereço do nó anterior ao retorno da função
--Parameters:

---- lista (p_no): Ponteiro para struct no

---- index (int): Inteiro

---- ant (p_no): Ponteiro para ponteiro para struct no

--Returns:

---- aux or NULL (p_no): Ponteiro para struct no ou NULL
*/
    if (lista == NULL) {
        return NULL;
    }
    p_no aux = lista;
    while(aux!=NULL) {
        if (aux->inter.ini <= index && index < aux->inter.fim) {
            return aux;
        }
        *ant = aux;
        aux = aux->prox;
    }
    return NULL;
}

char *str_concat(p_no no_1, char *str_2, int pos) {
/*
Concatena duas strings, colocando a segunda string na posição relativa indicada da primeira
Uma das strings está contida em um struct no e a outra é uma string comum
--Parameters:

---- no1 (p_no): Ponteiro para struct no

---- str_2 (char *): Ponteiro para char

---- pos (int): Inteiro

--Returns:

---- buffer (char *): Ponteiro para char
*/
    char *buffer;
    int n = strlen(no_1->vetor) + strlen(str_2)+1;
    buffer = malloc(n*sizeof(char));
    int i;
    int pos_relativa = pos-no_1->inter.ini;
    for (i=0; i<pos_relativa; i++) {
        buffer[i] = no_1->vetor[i];
    }            
    int tam_2 = strlen(str_2)+pos_relativa;
    for (i=pos_relativa; i<tam_2; i++) {
        buffer[i] = str_2[i-pos_relativa];
    }
    for (i=pos_relativa; i<strlen(no_1->vetor); i++) {
        int j = i+strlen(str_2);
        buffer[j] = no_1->vetor[i];
    }
    buffer[n-1] = '\0';
    return buffer;
}

void unir_nos(p_no no1, p_no no2) {
/*
Une dois struct no, modificando o primeiro para conter as informações, já corrigidas, de ambos
--Parameters:

---- no1 (p_no): Ponteiro para struct no

---- no2 (p_no): Ponteiro para struct no
*/
    if (no1->vetor==NULL) {
        no1->vetor = malloc((strlen(no2->vetor)+1)*sizeof(char));
        strcpy(no1->vetor, no2->vetor);
    } else {
        char *aux = no1->vetor;
        no1->vetor = str_concat(no1, no2->vetor, strlen(no1->vetor)+no1->inter.ini);
        free(aux);
    }
    free(no2->vetor);
    no1->inter.fim = no2->inter.fim;
    no1->prox = no2->prox;
    free(no2);
}

char *recortar(char *vetor, int ini, int fim) {
/*
Retorna um novo vetor contendo o intervalo [ini, fim) do vetor passado, relativa aos índice ini e fim
--Parameters:

---- vetor (char *): Ponteiro para char

---- ini (int): Inteiro

---- fim (int): Inteiro

--Returns:

---- novo_vet (char *): Ponteiro para char
*/
    int len = fim - ini;
    char *novo_vet = malloc((len+1)*sizeof(char));
    if (len!=0) {
        int c=0;
        for (int i=ini; i<fim; i++) {
            novo_vet[c] = vetor[i];
            c++;
        }
        novo_vet[c] = '\0';
    } else {
        novo_vet[0] = '\0';
    }
    return novo_vet;
}

void destacar(p_no no_comeco, int ini, int fim, p_no ant) {
/*
Recebe o no inicial, os limites da operação de destacar e o ponteiro para o no anterior ao inicial
e cria um novo no com eh_negrito==True, com o vetor [ini, fim) e corrigindo os ini e fim dos nos posteriores,
além de avaliar se há algum no que deve ser unido a outro adjacente (caso ambos tenham eh_negrito iguais)
--Parameters:

---- no_comeco (p_no): Ponteiro para struct no

---- ini (int): Inteiro

---- fim (int): Inteiro

---- ant (p_no): Ponteiro para struct no

--Returns:

---- novo_vet (char *): Ponteiro para char
*/
    if (fim <= no_comeco->inter.fim) {
        char *novo_vet = recortar(no_comeco->vetor, ini-no_comeco->inter.ini, fim-no_comeco->inter.ini);
        char *vet_comeco = recortar(no_comeco->vetor, 0, ini - no_comeco->inter.ini);
        char *vet_final = recortar(no_comeco->vetor, fim-no_comeco->inter.ini, no_comeco->inter.fim - no_comeco->inter.ini);
        if (strcmp(novo_vet, "")){ // caso os indices sejam válidos
            p_no no_meio = malloc(sizeof(struct no));
            no_meio->eh_negrito = True;
            no_meio->vetor = novo_vet;
            no_meio->inter.ini = ini;
            no_meio->inter.fim = fim;
            if (strcmp(vet_final,"")) { // caso o destaque não seja até o fim da string
                p_no no_final = malloc(sizeof(struct no));
                no_meio->prox = no_final;
                no_final->eh_negrito = no_comeco->eh_negrito;
                no_final->vetor = vet_final;
                no_final->inter.ini = fim;
                no_final->inter.fim = no_comeco->inter.fim;
                if (no_comeco->prox!=NULL && no_final->eh_negrito == no_comeco->prox->eh_negrito) {
                    unir_nos(no_final, no_comeco->prox);
                } else {
                    no_final->prox = no_comeco->prox;
                }
            } else { // se vai até o final da string então nem cria um no final
                if (no_comeco->prox!=NULL && no_meio->eh_negrito == no_comeco->prox->eh_negrito) {
                    unir_nos(no_meio, no_comeco->prox);
                } else {
                    no_meio->prox = no_comeco->prox;
                    free(vet_final);
                }
            }
            if (strcmp(vet_comeco,"")) { // caso o destaque comece depois do inicio da string
                free(no_comeco->vetor);
                no_comeco->vetor = vet_comeco; 
                no_comeco->inter.fim = ini;
                no_comeco->prox = no_meio;
                if (ant!=NULL && ant->eh_negrito == no_comeco->eh_negrito) {
                    unir_nos(ant, no_comeco);
                }
            } else { // se comeca no inicio da string então o no_comeco se torna o no_meio
                free(no_comeco->vetor);
                free(vet_comeco);
                if (ant!=NULL) {
                    free(no_comeco);
                    if (ant->eh_negrito == no_meio->eh_negrito) {
                        ant->prox = no_meio;
                        unir_nos(ant, no_meio);
                    } else {
                        ant->prox = no_meio;
                    }
                } else {
                    no_comeco->vetor = NULL;
                    no_comeco->eh_negrito = True;                   
                    unir_nos(no_comeco, no_meio);
                }
                
            }     
        }
    } else {
        if (fim <= no_comeco->prox->inter.fim) {
            destacar(no_comeco, ini, no_comeco->inter.fim, ant);
            if (no_comeco->eh_negrito==no_comeco->prox->eh_negrito) {
                unir_nos(no_comeco, no_comeco->prox);
            }
            destacar(no_comeco->prox, no_comeco->prox->inter.ini, fim, no_comeco);
            if (no_comeco->prox->eh_negrito==no_comeco->eh_negrito) {
                unir_nos(no_comeco, no_comeco->prox);
            }
        }
    }
    return;
}

void deletar(p_no lista) {
/*
Destroi a lista ligada (não circular) passada, considerando que os vetores de cada no 
foram alocados dinamicamente
--Parameters:

---- lista (p_no): Ponteiro para struct no
*/
    if (lista!=NULL) {
        deletar(lista->prox);
        free(lista->vetor);
        free(lista);
    }
}

p_no adicionar(p_no lista, char *nova_str, int index_ini) {
/*
Adiciona nova_string à lista, colocando no nó corresponde, caso exista, ou criando um novo, caso a lista
esteja vazia ou index_ini seja o último indice
--Parameters:

---- lista (p_no): Ponteiro para struct no

---- nova_str (char *): Ponteiro para char

---- index_ini (int): Inteiro

--Returns:

---- novo ou lista (char *): Ponteiro para char
*/
    p_no ant;
    p_no dest = encontrar_no(lista, index_ini, &ant);
    if (dest==NULL) {
        if (lista==NULL) { //lista está vazia
            p_no novo = malloc(sizeof(struct no));
            novo->eh_negrito = False;
            char *aux = malloc((strlen(nova_str)+1)*sizeof(char));
            novo->vetor = strcpy(aux, nova_str);
            novo->inter.ini = 0;
            novo->inter.fim = strlen(nova_str);
            novo->prox = lista;
            return novo;
        } else { //deve ser colocado no final da lista
            p_no novo = malloc(sizeof(struct no));
            novo->eh_negrito = ant->eh_negrito;
            char *aux = malloc((strlen(nova_str)+1)*sizeof(char));
            novo->vetor = strcpy(aux, nova_str);
            novo->inter.ini = index_ini;
            novo->inter.fim = index_ini + strlen(nova_str);
            novo->prox = ant->prox;
            unir_nos(ant, novo);
        }
    } else {
        char *aux = dest->vetor;
        dest->vetor = str_concat(dest, nova_str, index_ini);
        free(aux);
        dest->inter.fim += strlen(nova_str);
        atualizar_index(dest->prox, strlen(nova_str));
    }
    return lista;
}

int main() {
    p_no lista = NULL;
    while (True) {
        char comando[MAX_COMANDO];
        scanf("%s ", comando);
        if (!strcmp(comando, "INSERIR")) {
            int index;
            char buffer[MAX_BUFFER];
            scanf("%d '%[^']'", &index, buffer);
            lista = adicionar(lista, buffer, index);
        } else if (!strcmp(comando, "DESTACAR")) {
            int n, m;
            scanf("%d %d", &n, &m);
            p_no ant=NULL;
            p_no no = encontrar_no(lista, n, &ant);
            destacar(no, n, m, ant);
        } else if (!strcmp(comando, "MOSTRAR")) {
            p_no aux = lista;
            while (aux!=NULL) {
                if (aux->eh_negrito) {
                    printf("NEGRITO '%s'\n", aux->vetor);
                } else {
                    printf("NORMAL '%s'\n", aux->vetor);
                }
                aux = aux->prox;
            }
            deletar(lista);
            exit(0);
        }
    }
}