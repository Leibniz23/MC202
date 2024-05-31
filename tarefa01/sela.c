#include <stdio.h>
#define MAX 100
#define True 1
#define False 0

int encontrar_menores(int menores[][4], int entradas[][MAX], int m, int n) {
    int cont = 0;
    for (int i=0; i<m; i++) {
        int menor[4] = {entradas[i][0],0,0,0};
        int cont_menor = 0;
        for (int j=0; j<n; j++) {
            if (entradas[i][j] <= menor[0]) {
                menor[0] = entradas[i][j];
                menor[1] = i;
                menor[2] = j;
            }
        }
        for (int j=0; j<n; j++) {
            if (entradas[i][j] == menor[0]) {
                cont_menor++;
            }
        }
        menor[3] = cont_menor;
        for (int k=0; k<4; k++) {
            menores[cont][k] = menor[k];
        }
        cont++;
    }
    return cont;
}

int encontrar_sela(int menores[][4], int entradas[][MAX], int m, int n, int len_menores, int sela[]) {
    int flag = False;
    for (int k=0; k<len_menores; k++) {
        int maior[3]={entradas[0][menores[k][2]], 0, 0};
        int cont_maior = 0;
        for (int i=0; i<m; i++) {
            if (entradas[i][menores[k][2]] > maior[0] && menores[k][3] == 1) {
                maior[0] = entradas[i][menores[k][2]];
                maior[1] = i;
            }
        }
        for (int i=0; i<m; i++) {
            if (entradas[i][menores[k][2]] == maior[0]) {
                cont_maior++;
            }
        }
        if (maior[0] == menores[k][0] && cont_maior == 1 && menores[k][3] == 1) {
            menores[k][1] = maior[1];
            for (int p=0; p<3; p++) {
                sela[p] = menores[k][p];
            }
            flag = True;
        }
    }
    return flag;
}

int main() {
    int entrada[MAX][MAX];
    int m, n;
    scanf("%d %d", &m, &n);
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            scanf("%d ", &entrada[i][j]);
        }
    }
    int menores[MAX][4];
    int sela[3];
    int len_menores = encontrar_menores(menores, entrada, m, n);
    int flag = encontrar_sela(menores, entrada, m, n, len_menores, sela);
    if (flag) {
        printf("(%d, %d) eh ponto de sela com valor %d\n", sela[1], sela[2], sela[0]);
    } else {
        printf("nao existe ponto de sela\n");
    }
}