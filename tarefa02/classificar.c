#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define True 1
#define False 0
#define MAX_nome 30

typedef struct {
    char nome[MAX_nome];
    char sobrenome[MAX_nome];
} paciente;

int eh_alfabetica(char *palavra_a, char *palavra_b) {
/*
 *Recebe duas strings a e b;
 *Retorna 0 se b vem antes de a lexicograficamente e 1 se b vem antes de a lexicograficamente;
 */
    int resp = False;
    for (int i=0; i<strlen(palavra_b); i++) {
        if (i<strlen(palavra_a)) {
            if (palavra_a[i] != palavra_b[i]) {
                if (palavra_a[i] < palavra_b[i]) {
                    resp = True;
                }
                else {
                    resp = False;
                }
                return resp;
            }
        } else {
            return True;
        }
    }
    return resp;
}

void listar_homonimos(paciente pacientes[], int n) {
/*
 *Recebe um vetor de pacientes e seu tamanho n;
 *Mostra na tela uma lista com os nomes completos (apenas os homonimos) ordenados lexicograficamente;
 */
    for (int _=0; _<n; _++)
        for (int i=0; i<n-1; i++) {
            if (!eh_alfabetica(pacientes[i].nome, pacientes[i+1].nome)) {
                paciente aux = pacientes[i];
                pacientes[i] = pacientes[i+1];
                pacientes[i+1] = aux;
            }
        }

    for (int _=0; _<n; _++)
        for (int i=0; i<n-1; i++) {
            if (!strcmp(pacientes[i].nome, pacientes[i+1].nome) && !eh_alfabetica(pacientes[i].sobrenome, pacientes[i+1].sobrenome)) {
                paciente aux = pacientes[i];
                pacientes[i] = pacientes[i+1];
                pacientes[i+1] = aux;
            }
        }

    if (!strcmp(pacientes[0].nome, pacientes[1].nome)) {
        printf("%s_%s\n", pacientes[0].nome, pacientes[0].sobrenome);
    }
    for (int i=1;i<n-1; i++) {
        if (!strcmp(pacientes[i-1].nome, pacientes[i].nome) || !strcmp(pacientes[i+1].nome, pacientes[i].nome)) {
            printf("%s_%s\n", pacientes[i].nome, pacientes[i].sobrenome);
        }
    }
    if (!strcmp(pacientes[n-1].nome, pacientes[n-2].nome)) {
        printf("%s_%s\n", pacientes[n-1].nome, pacientes[n-1].sobrenome);
    }
}

void listar_parentes(paciente pacientes[], int n) {
/*
 *Recebe um vetor do tipo paciente e seu tamanho n;
 *Mostra na tela uma lista com os nomes completos (apenas dos parentes) ordenados lexicograficamente;
 */
    for (int _=0; _<n; _++)
        for (int i=0; i<n-1; i++) {
            if (!eh_alfabetica(pacientes[i].sobrenome, pacientes[i+1].sobrenome)){
                paciente aux = pacientes[i];
                pacientes[i] = pacientes[i+1];
                pacientes[i+1] = aux;
            }
        }

    for (int _=0; _<n; _++)
        for (int i=0; i<n-1; i++) {
            if (!strcmp(pacientes[i].sobrenome, pacientes[i+1].sobrenome) && !eh_alfabetica(pacientes[i].nome, pacientes[i+1].nome)) {
                paciente aux = pacientes[i];
                pacientes[i] = pacientes[i+1];
                pacientes[i+1] = aux;
            }
        }
    
    if (!strcmp(pacientes[0].sobrenome, pacientes[1].sobrenome)) {
        printf("%s_%s\n", pacientes[0].nome, pacientes[0].sobrenome);
    }
    for (int i=1;i<n-1; i++) {
        if (!strcmp(pacientes[i-1].sobrenome, pacientes[i].sobrenome) || !strcmp(pacientes[i+1].sobrenome, pacientes[i].sobrenome)) {
            printf("%s_%s\n", pacientes[i].nome, pacientes[i].sobrenome);
        }
    }
    if (!strcmp(pacientes[n-1].sobrenome, pacientes[n-2].sobrenome)) {
        printf("%s_%s\n", pacientes[n-1].nome, pacientes[n-1].sobrenome);
    }
}

void coletar_nomes(paciente *pacientes, int n) {
/*
 *Recebe um vetor do tipo paciente, seguido de seu tamanho n;
 *Altera o vetor, colocando em cada posição o nome de um paciente coletado do teclado;
 */
    for (int i=0; i<n; i++) {
        char pacientes_i[MAX_nome];
        scanf("%s", pacientes_i);
        int underline = 0;
        for (int j=0; j<MAX_nome; j++) {
            if (pacientes_i[j] == '_') {
                underline = j;
                break;
            }
        }
        for (int k=0; k<underline; k++) {
            pacientes[i].nome[k] = pacientes_i[k];
        }
        pacientes[i].nome[underline] = '\0';

        int len_str = strlen(pacientes_i);
        for (int h=0; h<len_str-underline; h++) {
            pacientes[i].sobrenome[h] = pacientes_i[h+underline+1];
        }
        pacientes[i].sobrenome[len_str-underline] = '\0';
    }
    return;
}
int main() {
    int n;
    char criterio[MAX_nome];
    scanf("%d", &n);
    scanf("%s", criterio);
    paciente *pacientes = malloc(n*sizeof(paciente));
    if (pacientes == NULL) {
        exit(1);
    }
    coletar_nomes(pacientes, n);
    if (!strcmp(criterio, "homonimos")) {
        listar_homonimos(pacientes, n);
    }
    else if (!strcmp(criterio, "parentes")) {
        listar_parentes(pacientes, n);
    }
    free(pacientes);
}