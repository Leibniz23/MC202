#include <stdio.h>
#define MAX 50
#define True 1
#define False 0

int encontrar_diff(int diffs[], int s[], int t[], int lens, int lent, int cont) {
    int flag = True;
    for (int i=0; i<lens; i++) {
        flag = True;
        for (int j=0; j<lent; j++) {
            if (s[i] == t[j]) {
                flag = False;
            }
        }
        if (flag) {
            diffs[cont] = s[i];
            cont++; 
        }
    }
    return cont;
}

void bubble_sort(int vetor[], int len) {
    int aux;
    for (int _=len-1; _>0; _--)
        for (int i=0; i<_; i++) {
            if (vetor[i] > vetor[i+1]) {
                aux = vetor[i];
                vetor[i] = vetor[i+1];
                vetor[i+1] = aux;
            }
        }
}

int main() {
    int lenv, lenu;
    scanf("%d %d", &lenv, &lenu);
    int v[MAX];
    int u[MAX];
    for (int i=0; i<lenv; i++) {
        scanf("%d ", &v[i]);
    }
    for (int i=0; i<lenu; i++){
        scanf("%d ", &u[i]);
    }
    int uv[2*MAX];
    int lenuv;
    lenuv = encontrar_diff(uv, v, u, lenv, lenu, 0);
    lenuv = encontrar_diff(uv, u, v, lenu, lenv, lenuv);
    bubble_sort(uv, lenuv);
    if (lenuv!=0) {
        printf("%d", uv[0]);
        for (int i=1; i<lenuv; i++) {
            printf(" %d", uv[i]);
            }
        printf("\n");
    } else {
        printf("\n");
    }

}