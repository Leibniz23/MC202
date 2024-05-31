#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 21
#define MAX_DIFF 1 /* Maior diferença de tamanho aceitável entre os heaps*/
#define PAI(i) ((i-1) /2)
#define F_ESQ(i) (2*i+1) /* Filho esquerdo de i*/
#define F_DIR(i) (2*i+2) /* Filho direito de i*/

typedef struct {
    char nome[MAX_NOME];
    int peso;
} Fruta;

struct fp {
    Fruta *caixas;
    int n, tam;
};

typedef struct fp *p_fp;

p_fp criar_heap(int tam) {
/*
<<<<<<< HEAD
Cria um heap de Frutas com o tamanho indicado

--Parameters:

---- tam (int): Inteiro

--Returns:

---- heap (p_fp): Ponteiro para struct fp
=======
Cria um heap do tamanho indicado

-- Parameters:

---- n (int): Inteiro

-- Return:

---- n (int): n modificado
>>>>>>> 6cc391848f6994c3f74437c5013fd52e1ecb4081
*/
    p_fp heap = malloc(sizeof(struct fp));
    heap->caixas = malloc(tam * sizeof(Fruta));
    heap->n = 0;
    heap->tam = tam;
    return heap;
}

void troca(Fruta *a, Fruta *b) {
/*
Troca dois elementos do tipo Fruta de lugar

--Parameters:

---- a e b (Fruta *): Ponteiro para struct Fruta
*/
    Fruta aux = *a;
    *a = *b;
    *b = aux;
}

void sobe_no_max(p_fp heap, int k) {
/*
Sobe no max-heap um elemento que é maior que seu pai

--Parameters:

---- heap (p_fp): Ponteiro para struct fp

---- k (int): Inteiro
*/
    if (k > 0 && heap->caixas[PAI(k)].peso < heap->caixas[k].peso) {
        troca(&heap->caixas[k], &heap->caixas[PAI(k)]);
        sobe_no_max(heap, PAI(k));
    }
}

void sobe_no_min(p_fp heap, int k) {
/*
Sobe no min-heap um elemento que é menor que seu pai

--Parameters:

---- heap (p_fp): Ponteiro para struct fp

---- k (int): Inteiro
*/
    if (k > 0 && heap->caixas[PAI(k)].peso > heap->caixas[k].peso) {
        troca(&heap->caixas[k], &heap->caixas[PAI(k)]);
        sobe_no_min(heap, PAI(k));
    }
}

void desce_no_max(p_fp heap, int k) {
/*
Desce no max-heap um elemento que é menor que seu maior filho

--Parameters:

---- heap (p_fp): Ponteiro para struct fp

---- k (int): Inteiro
*/
    int maior_filho;
    if (F_ESQ(k) < heap->n) {
        maior_filho = F_ESQ(k);
        if (F_DIR(k) < heap->n && heap->caixas[F_ESQ(k)].peso < heap->caixas[F_DIR(k)].peso) {
            maior_filho = F_DIR(k);
        }
        if (heap->caixas[k].peso < heap->caixas[maior_filho].peso) {
            troca(&heap->caixas[k], &heap->caixas[maior_filho]);
            desce_no_max(heap, maior_filho);
        }
    }
}

void desce_no_min(p_fp heap, int k) {
/*
Desce no min-heap um elemento que é maior que seu menor filho

--Parameters:

---- heap (p_fp): Ponteiro para struct fp

---- k (int): Inteiro
*/
    int menor_filho;
    if (F_ESQ(k) < heap->n) {
        menor_filho = F_ESQ(k);
        if (F_DIR(k) < heap->n && heap->caixas[F_ESQ(k)].peso > heap->caixas[F_DIR(k)].peso) {
            menor_filho = F_DIR(k);
        }
        if (heap->caixas[k].peso > heap->caixas[menor_filho].peso) {
            troca(&heap->caixas[k], &heap->caixas[menor_filho]);
            desce_no_min(heap, menor_filho);
        }
    }
}

void insere_max(p_fp heap , Fruta item) {
/*
Insere um elemento do tipo Fruta no max-heap, mantendo suas propriedades

--Parameters:

---- heap (p_fp): Ponteiro para struct fp

---- item (Fruta): struct Fruta
*/
    heap->caixas[heap->n] = item;
    heap->n++;
    sobe_no_max(heap, heap->n - 1);
}

void insere_min(p_fp heap, Fruta item) {
/*
Insere um elemento do tipo Fruta no max-heap, mantendo suas propriedades

--Parameters:

---- heap (p_fp): Ponteiro para struct fp

---- item (Fruta): struct Fruta
*/
    heap->caixas[heap->n] = item;
    heap->n++;
    sobe_no_min(heap, heap->n - 1);
}

Fruta extrai_max(p_fp heap) {
/*
Extrai o primeiro elemento do max-heap, mantendo suas propriedades

--Parameters:

---- heap (p_fp): Ponteiro para struct fp
*/
    Fruta item = heap->caixas[0];
    troca(&heap->caixas[0], &heap->caixas[heap->n - 1]);
    heap->n--;
    desce_no_max(heap, 0);
    return item;
}

Fruta extrai_min(p_fp heap) {
/*
Extrai o primeiro elemento do min-heap, mantendo suas propriedades

--Parameters:

---- heap (p_fp): Ponteiro para struct fp
*/
    Fruta item = heap->caixas[0];
    troca(&heap->caixas[0], &heap->caixas[heap->n - 1]);
    heap->n--;
    desce_no_min(heap, 0);
    return item;
}

void destruir_heap(p_fp heap) {
/*
Libera toda a memória alocada no heap

--Parameters:

---- heap (p_fp): Ponteiro para struct fp
*/
    free(heap->caixas);
    free(heap);
}

void corrige(p_fp max_heap, p_fp min_heap) {
/*
Corrige o max-heap e o min-heap para garantir que eles não tenham mais de
um elemento de diferença entre si

--Parameters:

---- max_heap (p_fp): Ponteiro para struct fp

---- min_heap (p_fp): Ponteiro para struct fp
*/
    Fruta aux;
    if (max_heap->n > min_heap->n) {
        aux = extrai_max(max_heap);
        insere_min(min_heap, aux);
    } else {
        aux = extrai_min(min_heap);
        insere_max(max_heap, aux);
    }
}

void insere_certo(p_fp max_heap, p_fp min_heap, Fruta nova_fruta) {
/*
Insere a nova_fruta no heap correspondente e faz as devidas mudanças para
manter as propriedades

--Parameters:

---- max_heap (p_fp): Ponteiro para struct fp

---- min_heap (p_fp): Ponteiro para struct fp

---- nova_fruta (Fruta) : typedef Fruta
*/

    if (!max_heap->n) {
        insere_max(max_heap, nova_fruta);
    } else if (nova_fruta.peso > max_heap->caixas[0].peso) {
        insere_min(min_heap, nova_fruta);
    } else {
        insere_max(max_heap, nova_fruta);
    }
/* Caso tenha danificado a estrutura, corrige */
    if (abs(max_heap->n - min_heap->n) > MAX_DIFF) {
        corrige(max_heap, min_heap);
    }
}

int main() {
    int n;
    Fruta nova_fruta;
    scanf("%d ", &n);
    p_fp max_heap = criar_heap(n); // Do começo até a metade da lista
    p_fp min_heap = criar_heap(n); // Da metade pro final da lista
    while (scanf("%s %d ", nova_fruta.nome, &nova_fruta.peso) != EOF) {
        insere_certo(max_heap, min_heap, nova_fruta);
        if (max_heap->n > min_heap->n) {
            printf("%s: %d\n", max_heap->caixas[0].nome, max_heap->caixas[0].peso);
        } else if (max_heap->n < min_heap->n) {
            printf("%s: %d\n", min_heap->caixas[0].nome, min_heap->caixas[0].peso);
        } else {
            printf("%s: %d\n", max_heap->caixas[0].nome, max_heap->caixas[0].peso);
            printf("%s: %d\n", min_heap->caixas[0].nome, min_heap->caixas[0].peso);
        }
    }
    destruir_heap(max_heap);
    destruir_heap(min_heap);
}