#define True 1
#define False 0

typedef struct {
    int k; // k dessa boneca especificamente
    int soma; // valor da soma direta das bonecas dentro dessa
    int cont; // quantidade de bonecas contidas nessa
} Boneca;

typedef struct no *p_no;

typedef struct pilha *p_pilha;

struct no {
    Boneca boneca;
    p_no prox;
};

struct pilha {
    int tam_pilha;
    p_no topo;
};

p_no criar_lista();

p_pilha criar_pilha();

void push(p_pilha pilha, int x);

void pop(p_pilha pilha);

p_no adicionar_ordenado(p_no lista, p_no novo);

void destruir_pilha(p_pilha pilha);