#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include "func9.h"

p_fc criar_fc(int tam) {
    p_fc fila;
    fila = malloc(sizeof(struct fc));
    fila->coords = malloc(tam*sizeof(coord));
    fila->n = 0;
    fila->alocado = tam;
    return fila;
}

void enfileira(p_fc fila, coord x) {
    int i;
    coord *temp;
    if (fila->n == fila->alocado) {
        temp = fila->coords;
        fila->alocado *= 2;
        fila->coords = malloc(fila->alocado * sizeof(coord));
        for (i = 0; i < fila->n; i++) {
            fila->coords[i] = temp[i];
        }
        free(temp);
    }
    fila->coords[fila->n] = x;
    fila->n++;
}

void liberar_fila(p_fc fila) {
    free(fila->coords);
    free(fila);
}

struct imagem *ler_imagem() {
    struct imagem *img;
    char peek;
    int i, j, r, g, b;
    assert(img = malloc(sizeof(*img)));
    scanf("P3 ");
    while ((peek = getchar()) == '#')
        scanf("%*[^\r\n]%*[\r\n]");
    ungetc(peek, stdin);
    assert(scanf("%d %d %*d", &img->w, &img->h) == 2);
    assert(img->pix = malloc(sizeof(*img->pix) * img->h));
    for (i = 0; i < img->h; i++) {
        assert(img->pix[i] = malloc(sizeof(**img->pix) * img->w));
        for (j = 0; j < img->w; j++) {
            assert(scanf("%d%d%d", &r, &g, &b) == 3);
            img->pix[i][j] = (r << 16) + (g << 8) + b;
        }
    }
    return img;
}

void liberar_imagem(struct imagem *img) {
    int i;
    for (i = 0; i < img->h; i++)
        free(img->pix[i]);
    free(img->pix);
    free(img);
}

void pintar(p_img img, int i, int j) {
    img->pix[i][j] = PRETA;
    if (i > 0) {
        if (img->pix[i-1][j] == BRANCA) {
            pintar(img, i-1, j);
        }
    }
    if (i < img->h - 1) {
        if (img->pix[i+1][j] == BRANCA) {
            pintar(img, i+1, j);
        }
    }
    if (j > 0) {
        if (img->pix[i][j-1] == BRANCA) {
            pintar(img, i, j-1);;
        }
    }
    if (j < img->w -1) {
        if (img->pix[i][j+1] == BRANCA) {
            pintar(img, i, j+1);
        }
    }
}

coord **criar_visitados(p_img img, coord inicio) {
    coord **visitados = malloc(img->h * sizeof(coord *));
    for (int i = 0; i < img->h; i++) {
        visitados[i] = malloc((img->w) * sizeof(coord));
        for (int j = 0; j<img->w; j++) {
            coord v;
            v.cor = img->pix[i][j];
            v.i = i;
            v.j = j;
            v.visitado = 0;
            v.distancia = INT_MAX;
            visitados[i][j] = v;
        }
    }
    visitados[inicio.i][inicio.j].cor = PRETA;
    visitados[inicio.i][inicio.j].visitado = 1;
    visitados[inicio.i][inicio.j].distancia = 0;
    return visitados;
}

void liberar_visitados(coord **visitados, int max_i) {
    for (int i = 0; i < max_i; i++) {
        free(visitados[i]);
    }
    free(visitados);
}

coord marcar_inicio(p_img img) {
    coord inicio;
    inicio.i = 0;
    inicio.j = 0;
    for (int i = 0; i < img->h; i++){
        for (int j = 0; j < img->w; j++) {
            if (img->pix[i][j] == BRANCA) {
                pintar(img, i, j);
                inicio.cor = PRETA;
                inicio.i = i;
                inicio.j = j;
                return inicio;
            }
        }
    }
    return inicio;
}

int vazia(p_fc fila) {
    if (fila->n <= 0) {
        return 1; // fila vazia
    } else {
        return 0; // fila não vazia
    }
}

coord extrair_primeiro(p_fc fila) {
    coord aux = fila->coords[0];
    for (int i = 1; i<fila->n; i++) {
        fila->coords[i-1] = fila->coords[i];
    }
    fila->n--;
    return aux;
}

void atualiza_pixel(coord pixel, coord **visitados, p_fc fila0, p_fc fila1, int i, int j) {
    if (!visitados[i][j].visitado) {
        if (pixel.cor == visitados[i][j].cor) {
            if (pixel.distancia < visitados[i][j].distancia) {
                visitados[i][j].distancia = pixel.distancia;
                enfileira(fila0, visitados[i][j]);
            }    
        } else {
            if (pixel.distancia + 1 < visitados[i][j].distancia) { // +1 é o custo pra ir em uma cor diferente
                visitados[i][j].distancia = pixel.distancia + 1;
                enfileira(fila1, visitados[i][j]);
            }
        }
    }
}

void calcular_adjacencias(coord pixel, coord **visitados, p_fc fila0, p_fc fila1, int max_i, int max_j) {
    if (pixel.i > 0) {
        atualiza_pixel(pixel, visitados, fila0, fila1, pixel.i-1, pixel.j);
    }
    if (pixel.i < max_i - 1) {
        atualiza_pixel(pixel, visitados, fila0, fila1, pixel.i+1, pixel.j);
    }
    if (pixel.j > 0) {
        atualiza_pixel(pixel, visitados, fila0, fila1, pixel.i, pixel.j-1);
    }
    if (pixel.j < max_j -1) {
        atualiza_pixel(pixel, visitados, fila0, fila1, pixel.i, pixel.j+1);
    }
}

void encontrar_regioes(coord **visitados, p_fc fila0, p_fc fila1, int max_i, int max_j, int *cont) { // vai ser tipo dijkstra
    coord pix;
    while (!vazia(fila0) || !vazia(fila1)) {
        if (!vazia(fila0)) {
            pix = extrair_primeiro(fila0);
        } else {
            pix = extrair_primeiro(fila1);
        }
        if (!pix.visitado) {
            visitados[pix.i][pix.j].visitado = 1;
            if (pix.cor == BRANCA) {
                *cont = pix.distancia;
                return;
            } else {
                calcular_adjacencias(pix, visitados, fila0, fila1, max_i, max_j);
            }
        }
    }
}

