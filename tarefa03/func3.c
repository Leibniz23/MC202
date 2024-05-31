#include <stdio.h>
#include <stdlib.h>
#include "func3.h"

void eh_max_min(int valor, int *max, int *min) {
    if (valor<*min) {
        *min = valor;
        return;
    } else if (valor>*max) {
        *max = valor;
        return;
    }
    return;
}
void imprimir(char **matriz, int n, int p) {
    printf("%d\n", p);
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf("%c ", matriz[i][j]);
        }
    printf("\n");
    }
    printf("\n");
}

int eh_solucao(char **matriz, int n) {
    return True;
}

int prefixo_valido(char **matriz, int n, int j, int i) {
/*recebe a matriz e seu tamanho, o valor da proxima coluna que sera colocada uma rainha e a linha q foi colocada a ultima rainha*/
    for (int col=0; col<n; col++) {
        //verifica se tem mais rainhas na mesma linha
        if (col!=j-1 && matriz[i][col]=='r') {
            //modificar pra ver se tem peao na coluna entre a rainha atual e a suposta outra e se tiver nao retorna false,
            // uma ideia é pegar o valor de cada casa e ver se é um peao, se for e a linha dele for menor q a linha q a rainha esta então ta td bem 
            return False;
        }
    }

    for (int lin=0; lin<n; lin++) {
        for (int col=0; col<n; col++) {
            //verifica se nao esta na diagonal secundaria da rainha
            if (i+j-1==lin+col && matriz[lin][col]=='r' && i!= lin && j-1!=col) {
                return False;
            }
        }
    }
    //verifica se nao esta na diagonal principal da rainha
    int c=1;
    while(c<n) {
    if (0<=(i-c) && (i-c)<=n-1 && 0<=(j-1-c) && (j-1-c)<=n-1)
        if (matriz[i-c][j-1-c]=='r')
            return False;
    if(0<=(i+c) && (i+c)<=n-1 && 0<=(j-1+c) && (j-1+c)<=n-1)
        if(matriz[i+c][j-1+c]=='r')
            return False;
    c++;
    }
    return True;
}   

int ataque_linha(char *vetor, int ini, int fim, int j) {
//verifica se tem rainhas se atacando numa mesma linha, usar nas diagonais linearizadas com peoes
    for (int pos=ini; pos<=fim; pos++) {
        if (vetor[pos]=='p') {
            if (pos<j) {
                for (int posi=pos+1; posi!=j; posi++) {
                    if (vetor[posi] == 'r') {
                        return True;}
                }
            }
            if (pos>j) {
                for (int posi=pos-1; posi!=j; posi--) {
                    if (vetor[pos] == 'r') {
                        return True;}
                }
            }
        }
    }
    return False;
}

int prefixo_valido_peoes(char **matriz, int n, int j, int i) {
    //verifica se tem rainhas se atacando na mesma linha, considerando os peões
    if (ataque_linha(matriz[i], 0, n-1, j-1)) {
        return False;
    }
    //verifica se tem rainhas se atacando na coluna, considerando peoes
    for (int lin=0; lin<n; lin++) {
        if (matriz[lin][j-1]=='p') {
            if (lin<i) {
                for (int pos=lin+1; pos==i; pos++) {
                    if (matriz[pos][j-1] == 'r') {
                        return False;}
                }
            }
            if (lin>i) {
                for (int pos=lin-1; pos==i; pos--) {
                    if (matriz[pos][j-1] == 'r') {
                        return False;}
                }
            }
        }
    }
    //verifica se tem rainhas se atacando na diagonal, considerando peoes
    char *diag = malloc(n*sizeof(char));
    int min=n-1, max=0;
    for (int lin=0; lin<n; lin++) {
        for (int col=0; col<n; col++) {
            if (i+j-1==lin+col) {
                diag[col] = matriz[lin][col];
                eh_max_min(col, &max, &min);
            }
        }
    }
    if (ataque_linha(diag, min, max, j-1)) {
        return False;
    }

    diag[j-1] = matriz[i][j-1];
    int c=1;
    min=n-1, max=0;
    while(c<n) {
        if (0<=(i-c) && (i-c)<=n-1 && 0<=(j-1-c) && (j-1-c)<=n-1) {
            diag[j-1-c] = matriz[i-c][j-1-c];
            eh_max_min(j-1-c, &max, &min);
        }
        if(0<=(i+c) && (i+c)<=n-1 && 0<=(j-1+c) && (j-1+c)<=n-1) {
            diag[j-1+c] = matriz[i+c][j-1+c];
            eh_max_min(j-1+c, &max, &min);
        }
        c++;
    }
    if (ataque_linha(diag, min, max, j-1)) {
        return False;
    }
    free(diag);
    return True;
}

int solucao_sem_peoes(char **matriz, int n, int m, int j, int i) {
//recebe uma matriz parcialmente preenchida e retorna True se existe uma solucao possivel ainda ou se ele encontrou a solucao
//e retorna False se não tem solucao
    if (m==0) {
        if (prefixo_valido(matriz, n, j, i)) {
            imprimir(matriz, n, 0);
            return True;
        }
    } else if (!prefixo_valido(matriz, n, j, i)) {
        return False;

    } else {
        for (int u=0; u<n; u++) {
            matriz[u][j] = 'r';
            //imprimir(matriz, n, 0);
            if (solucao_sem_peoes(matriz, n, m-1, j+1, u)) {
                return True;
            }
            matriz[u][j] = '.';
            // a parte de colocar os peoes deve ser por aqui, depois de testar as rainhas em tds os lugares ou entao quando m=1 e j=n-1 que vai estar numa posicao quase completa
        }
    }
    return False;
}

int pode_peao(char **matriz, int n, int p, int i, int j) {
    if (i==0 && j==0) {
        return False;
    } else if (i==0 && j==n-1) {
        return False;
    } else if (i==n-1 && j==0) {
        return False;
    } else if (i==n-1 && j==n-1) {
        return False;
    } else if (matriz[i][j]=='r') {
        return False;
    } else {
        return True;
    }
}

int solucao_com_peoes(char **matriz, int n, int m, int j, int i, int p, int p_ini) {
    if (m==0) {
        if (eh_solucao(matriz, n)) {
            imprimir(matriz, n, p);
        }
    } else if (!prefixo_valido_peoes(matriz, n, j, i)) {
        return False;
    }
    
    else {
        for (int u=0; u<n; u++) {
            matriz[u][j] = 'r';
            if (solucao_com_peoes(matriz, n, m-1, j+1, u, p, p_ini)) {
                return True;
            }
            matriz[u][j] = '.';
        }
        if (p>0) {
            for (int v=0; v<n; v++){
                for (int k=0; k<n; k++) {
                    if (pode_peao(matriz, n, p, v, k)) {
                        matriz[v][k] = 'p';
                        if (solucao_com_peoes(matriz, n, m, j+1, v, p-1, p_ini)) {
                            return True;
                        }
                        matriz[v][k] = '.';
                    }
                
                }
            }
        }
    }   
    return False;
}