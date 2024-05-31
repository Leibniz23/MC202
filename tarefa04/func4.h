#define MAX_BUFFER 128
#define MAX_COMANDO 16
#define True 1
#define False 0

typedef struct no *p_no;

typedef struct {
    int ini;
    int fim;
} intervalo;

struct no {
    int eh_negrito;
    char *vetor;
    intervalo inter;
    p_no prox;
};

char *str_concat(p_no no_1, char *str_2, int pos);
/*
 *Concatena duas strings, criando um novo vetor dinâmico com a segunda string colocada na posição imediatamente depois da indicada
 *Retorna a primeira string modificada
 */

// str_1 é o vetor que já esta no nó, str_2 é o que deve ser adicionado, 

void remover_no(p_no lista, p_no no);

p_no encontrar_no(p_no lista, int index, p_no *ant);