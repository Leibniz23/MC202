#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define True 1
#define False 0
#define MAX_str 128
#define MAX_registro 32
#define MAX_comando 16

typedef struct {
    char nome[MAX_registro];
    char cid[MAX_registro];
    char crm[MAX_registro];
} registro;


typedef struct {
    char str1[MAX_str];
    char str2[MAX_str];
} med_doenca;

int eh_alfabetica(char *palavra_a, char *palavra_b) {
/*
 *Recebe duas strings a e b;
 *Retorna 0 se b vem antes de a lexicograficamente e 1 se b vem antes de a lexicograficamente;
 */
    int resp = False;
    if (!strcmp(palavra_b, "") && strcmp(palavra_a, "")) {
        return True;
    } else if (!strcmp(palavra_a, "") && strcmp(palavra_b, "")) {
        return False;
    }
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

med_doenca *ler_arquivo(char *nome_arq, int *n) {
/*
 * Recebe uma string com o nome de um arquivo;
 * Retorna um vetor de tamanho igual ao número de elementos dito na primeira linha do arquivo,
 * preenchido com elementos med_doenca, dividindo a linha em 2 strings, onde a primeira começa no
 * início e acaba no primeiro espaço (exclusivo) e a segunda começa no primeiro espaço (exclusivo)
 * e vai até o fim da linha;
 * Além disso, altera o valor do n passado, sendo seu novo valor o tamanho do vetor de retorno;
 */
    FILE *arq = fopen(nome_arq, "r");
    if (arq == NULL) {
        perror("Erro ao abrir arquivo de referência\n");
        exit(0);
    }
    int len_arq;
    fscanf(arq,"%d", &len_arq);
    *n = len_arq;
    med_doenca *arquivo = malloc(len_arq * sizeof(med_doenca));
    for (int i=0; i<len_arq; i++) {
        char arquivo_i[MAX_str];
        fscanf(arq, " %[^\n]", arquivo_i);
        int str_len = strlen(arquivo_i);
        int esp = 0;
        while (arquivo_i[esp]!=' ') {
            esp++;
        }
        for (int j=0; j<str_len; j++) {
            if (j<esp) {
                arquivo[i].str1[j] = arquivo_i[j];
        } else if (j>esp)
            arquivo[i].str2[j-esp-1] = arquivo_i[j];
        }
        arquivo[i].str2[strlen(arquivo_i)-esp-1] = '\0';
        arquivo[i].str1[esp] = '\0';
    }
    fclose(arq);
    return arquivo;
}

void ordenar(registro *consultas, int len) {
/*
 * Recebe um vetor de registros e o tamanho dele;
 * Altera o vetor, colocando seus elementos em ordem alfabética baseado no nome;
 */
    for (int _=0; _<len; _++)
        for (int i=0; i<len-1; i++) {
            if (!eh_alfabetica(consultas[i].nome, consultas[i+1].nome) && consultas[i].nome[0]!=0) {
                registro aux = consultas[i];
                consultas[i] = consultas[i+1];
                consultas[i+1] = aux;
            }
        }
}

void relatorio(registro *consultas, int len, med_doenca *medicos, med_doenca *doencas, int n_med, int n_doenca) {
/*
 * Recebe um vetor de registros, seu tamanho e 2 vetores com os dados necessários para gerar o relatório, seguidos de seus tamanhos;
 * Mostra na tela o relatório com o formato pedido;
 */
    for (int i=0; i<len; i++) {
        char *nome_med;
        char *nome_doenca;
        if (consultas[i].nome[0] != 0) {
            for (int j=0; j<n_med; j++) 
                if (!strcmp(medicos[j].str1, consultas[i].crm)) {
                    nome_med = medicos[j].str2;
                }
            for (int k=0; k<n_doenca; k++)
                if (!strcmp(doencas[k].str1, consultas[i].cid)) {
                    nome_doenca = doencas[k].str2;
                }
            printf("%s atendido por %s: %s\n", consultas[i].nome, nome_med, nome_doenca);
        }
    }
}

void deletar(registro *consultas, int pos) {
/*
 * Recebe um vetor de registros e uma posição dele;
 * Altera o vetor, deletando o elemento vetor[pos];
 */
    for (int i=0; i<MAX_registro; i++) {
        consultas[pos].nome[i] = 0;
        consultas[pos].cid[i] = 0;
        consultas[pos].crm[i] = 0;
    }
}

void deslocar(registro *consultas, int pos, int n) {
/*
 * Recebe um vetor de registros, uma posição arbitrária diferente de 0 e o tamanho n do vetor;
 * Altera o vetor, deslocando todos os elementos de índice >= pos uma posição para trás;
 */
    for (int i=pos; i<n-1; i++)
        consultas[i] = consultas[i+1];
    deletar(consultas, n-1);
}

int main() {
    int n, n_med, n_doenca, cont=0;
    registro *consultas;
    med_doenca *medicos = ler_arquivo("dados/medicos.txt", &n_med);
    med_doenca *doencas = ler_arquivo("dados/doencas.txt", &n_doenca);
    while (True) {
    char comando[MAX_comando];
    scanf("%s ", comando);
    if (!strcmp(comando, "abrir")) {
        scanf("%d\n", &n);
        consultas = malloc(n*sizeof(registro));
        for (int i=0; i<n; i++) {
            deletar(consultas, i);
        }
    } else if (!strcmp(comando, "fechar")) {
        ordenar(consultas, n);
        relatorio(consultas, n, medicos, doencas, n_med, n_doenca);
        free(consultas);
        free(medicos);
        free(doencas);
        exit(0);
    } else if (!strcmp(comando, "registrar") && cont<=n) {
        registro consulta;
        scanf("%s %s %s\n", consulta.nome, consulta.cid, consulta.crm);
        consultas[cont] = consulta;
        cont++;
    } else if (!strcmp(comando, "alterar")) {
        registro nova_consulta;
        scanf("%s %s\n", nova_consulta.nome, nova_consulta.cid);
        for (int i=0; i<n; i++) {
            if (!strcmp(consultas[i].nome, nova_consulta.nome)) {
                for (int j=0; j<MAX_registro; j++)
                    consultas[i].cid[j] = nova_consulta.cid[j];
            }
        }
    } else if (!strcmp(comando, "remover")) {
        registro remover;
        scanf("%s\n", remover.nome);
        for (int i=0; i<n; i++) {
            if (!strcmp(consultas[i].nome, remover.nome)) {
                deslocar(consultas, i, n);
                cont--;
            }
        }
    }
    }
}

//enquanto tiver elementos na linha o scanf vai ler a mesma linha, ele so le outra quando acabar os elementos daquela linha