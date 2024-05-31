/*
Este arquivo conterá a implementação do índice.
Na versão atual, a estrutura de dados corresponde
somente a uma lista de períodos e não há nenhuma
estrutura pensada para realizar buscas rapidamente.

Você DEVE completar este arquivo, modificando-o livremente.
*/

#include "indice.h"
#include "utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIMO 3023 // Número primo arbitrário
#define MAX_PALAVRAS 40000 // Metade do total de palavras (no max duas colisões)

/*
Defina todas as estruturas de dados
auxiliares que desejar. Em particular,
é obrigatório definir e utilizar uma
tabela de espalhamento.
*/

typedef struct Item *p_Item;

typedef struct Item {
    char *palavra; // chave de busca
    int n_ocorrencias; // quantidade de elementos do vetor de periodos
    p_no_str *periodos; // vetor com todos os periodos em que essa palavra aparece
    int periodo_atual; // último periodo que foi inserido nesse item
    p_Item prox;
} Item;

typedef struct hash *p_hash;

struct hash {
    p_Item tabela[MAX_PALAVRAS];
};

void inicializa_hash(p_hash hash, int tam_periodos) {
/*
Inicializa os itens iniciais da tabela hash, não garante nada sobre os nós
vindos de colisão
*/
    for (int i = 0; i<MAX_PALAVRAS; i++) {
        p_Item item = malloc(sizeof(Item));
        hash->tabela[i] = item;
        hash->tabela[i]->palavra = NULL;
        hash->tabela[i]->n_ocorrencias = 0;
        hash->tabela[i]->periodo_atual = 0;
        hash->tabela[i]->periodos = malloc(tam_periodos*sizeof(struct no_str));
        hash->tabela[i]->prox = NULL;
    }
}

int hash(char *chave) {
/*
Cria e devolve uma chave númerica baseada nos caractéres da chave dada

Utilizei o método da divisão, escolhendo um número primo arbitrário e distante
de potências de dois para melhorar o espalhamento da tabela


*/
    int i, n = 0;
    for (i = 0; i < strlen(chave); i++){
        n = (PRIMO * n + chave[i]) % MAX_PALAVRAS;
    }
    return n;
}

struct indice {
    /*
     Você deve modificar essa estrutura
     para que ela contenha todos os dados
     necessários para o índice.
     Em particular, a variável que
     guarda a tabela de espalhamento
     deve ser colocada aqui.

     Neste exemplo, guardamos apenas uma
     lista de períodos.
    */

    p_hash hash; 
    p_no_str lista_periodos; // transformar essa lista em uma tabela de hashing e fazer a busca
};

p_Item buscar_hash(p_hash hash_table, char *chave) {
/*
Devolve NULL se essa chave não está na tabela ou então devolve o item no hash em que a chave está
(ainda tem que procurar caso tenha tido colisão)

--Parameters:

---- hash_table (p_hash): Ponteiro para struct hash

---- chave (char *): Ponteiro para char (vetor)
*/
    int n = hash(chave);
    if (hash_table->tabela[n]->n_ocorrencias != 0) {
        for (p_Item possivel = hash_table->tabela[n]; possivel != NULL; possivel = possivel->prox) {
            if (!strcmp(chave, possivel->palavra)) {
                return possivel;
            }
        }
        return NULL;
    } else {
        return NULL;
    }
}

p_Item cria_n_inicializado(p_Item ant, char *chave , p_no_str periodo, int n_periodos, int n, int periodo_atual) {
/*
Cria um item no hash quando esse elemento não foi inicializado pela função inicializa_hash,
ou seja, é fruto de uma colisão ou se é uma palavra que já foi catalogada, mas este novo periodo deve

--Parameters:

---- ant (p_Item): Ponteiro para Item (typedef)

---- chave (char *): Ponteiro para char (vetor)

---- periodo (p_no_str): Ponteiro para struct no_str

---- n_periodos (int): Inteiro

---- n (int): Inteiro

---- periodo_atual (int): Inteiro

--Returns:

---- ant->prox (p_Item): Ponteiro para Item (typedef)
*/
    ant->prox = malloc(sizeof(Item));
    ant->prox->periodos = malloc(n_periodos*sizeof(p_no_str));
    ant->prox->palavra = malloc((strlen(chave)+1)*sizeof(char));
    strcpy(ant->prox->palavra, chave);
    ant->prox->n_ocorrencias = 0;
    ant->prox->periodos[ant->prox->n_ocorrencias] = periodo;
    ant->prox->periodo_atual = periodo_atual;
    ant->prox->n_ocorrencias++;
    ant->prox->prox = NULL;
    return ant->prox;

}

void inserir_hash(p_hash hash_table, char *chave , p_no_str periodo, int n_periodos, int n_periodo_atual) {
/*
Insere uma palavra na tabela hash

--Parameters:

---- hash_table (p_hash): Ponteiro para struct hash

---- chave (char *): Ponteiro para char (vetor)

---- periodo (p_no_str): Ponteiro para struct no_str

---- n_periodos (int): Inteiro

---- n_periodo_atual (int): Inteiro
*/
    int n = hash(chave);
    p_Item aux = hash_table->tabela[n];
    if (n_periodo_atual != hash_table->tabela[n]->periodo_atual) {
        if (aux->palavra==NULL) { // se é o primeiro com essa chave
            aux->palavra = malloc((strlen(chave)+1)*sizeof(char));
            strcpy(aux->palavra, chave);
            aux->periodos[aux->n_ocorrencias] = periodo;
            aux->periodo_atual = n_periodo_atual;
            hash_table->tabela[n]->n_ocorrencias++;
            aux->prox = NULL;
        } else {
            p_Item ant;
            while (aux != NULL) { // se a palavra já foi adicionada
                if (strcmp(aux->palavra, chave) == 0) {
                    if (aux->periodo_atual != n_periodo_atual) {
                        aux->periodos[aux->n_ocorrencias] = periodo;
                        aux->periodo_atual = n_periodo_atual;
                        aux->n_ocorrencias++;
                        return;
                    } else {
                        return;
                    }
                }
                ant = aux;
                aux = aux->prox;
            }
            ant->prox = cria_n_inicializado(ant, chave, periodo, n_periodos, n, n_periodo_atual);
        }
    }
}

p_indice criar_indice(char *nome_arquivo) {
    p_indice indice = malloc(sizeof(struct indice));
    assert(indice);
    int numero_periodos;
    indice->lista_periodos = ler_lista_periodos(nome_arquivo, &numero_periodos);
    indice->hash = malloc(sizeof(struct hash));
    inicializa_hash(indice->hash, numero_periodos);
    int n_periodo = 0;
    for (p_no_str periodo = indice->lista_periodos; periodo != NULL; periodo = periodo->prox) {
        p_no_str lista_palavras = extrair_palavras(periodo->str);
        n_periodo++;
        for (p_no_str palavra = lista_palavras; palavra != NULL; palavra = palavra->prox) {
            inserir_hash(indice->hash, palavra->str, periodo, numero_periodos, n_periodo);
        }
        liberar_lista_str(lista_palavras);
    }
    return indice;
}

void libera_item(p_Item item) {
/*
Libera um p_item

--Parameters:

---- item (p_Item): Ponteiro para Item (typedef)
*/
    if (item) {
        free(item->palavra);
        free(item->periodos);
        libera_item(item->prox);
        free(item);
    }
}

void liberar_hash_table(p_hash hash_table) {
/*
Libera toda a tabela de hashing

--Parameters:

---- hash_table (p_hash): Ponteiro para struct hash (typedef)
*/
    for (int i=0; i<MAX_PALAVRAS; i++) {
        libera_item(hash_table->tabela[i]);
    }
    free(hash_table); 
}


void liberar_indice(p_indice indice) {
    liberar_hash_table(indice->hash);
    liberar_lista_str(indice->lista_periodos);
    free(indice);
}

int consultar_indice(
    p_indice indice,
    char *consulta,
    void(callback)(char *periodo, int numero_ocorrencia))
{
    p_no_str lista_consulta = extrair_palavras(consulta);
    assert(lista_consulta);
    if (lista_consulta->prox == NULL) { // a consulta só tem uma palavra
        p_Item alvo = buscar_hash(indice->hash, consulta);
        if (alvo==NULL) {
            return 0;
        }
        p_no_str *periodos_alvo = alvo->periodos;
        for (int i = 0; i < alvo->n_ocorrencias; i++) {
            callback(periodos_alvo[i]->str, i+1);
        }
        liberar_lista_str(lista_consulta);
        return alvo->n_ocorrencias;

    } else { // a consulta é uma expressão
        char *primeira_palavra = lista_consulta->str;
        int num_ocorrencia = 0;
        p_Item alvo = buscar_hash(indice->hash, primeira_palavra);
        if (alvo==NULL) {
            return 0;
        }
        p_no_str *periodos_alvo = alvo->periodos;
        p_no_str palavras_periodo;
        for (int i = 0; i < alvo->n_ocorrencias; i++) {
            palavras_periodo = extrair_palavras(periodos_alvo[i]->str);
            if (corresponde(lista_consulta, palavras_periodo)) {
                num_ocorrencia++;
                callback(periodos_alvo[i]->str, num_ocorrencia);
            }
            liberar_lista_str(palavras_periodo);
        }
        liberar_lista_str(lista_consulta);
        return num_ocorrencia;
    }
}