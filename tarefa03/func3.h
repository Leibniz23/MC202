#define False 0
#define True 1
#define MAX_peoes 6

void eh_max_min(int valor, int *max, int *min);

void imprimir(char **matriz, int n, int p);

int eh_solucao(char **matriz, int n);

int prefixo_valido(char **matriz, int n, int j, int i);

int ataque_linha(char *vetor, int ini, int fim, int j);

int prefixo_valido_peoes(char **matriz, int n, int j, int i);

int solucao_sem_peoes(char **matriz, int n, int m, int j, int i);

int solucao_com_peoes(char **matriz, int n, int m, int j, int i, int p, int p_ini);

int pode_peao(char **matriz, int n, int p, int i, int j);