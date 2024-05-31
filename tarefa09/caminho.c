#include <stdio.h>
#include <limits.h>
#include "func9.h"

int main() {
    p_img img = ler_imagem();
    coord inicio = marcar_inicio(img);
    p_fc fila0 = criar_fc(MEDIA_PIXELS);
    p_fc fila1 = criar_fc(MEDIA_PIXELS);
    coord **visitados = criar_visitados(img, inicio);
    calcular_adjacencias(visitados[inicio.i][inicio.j], visitados, fila0, fila1, img->h, img->w);
    int regioes;
    encontrar_regioes(visitados, fila0, fila1, img->h, img->w, &regioes);
    liberar_visitados(visitados, img->h);
    liberar_imagem(img);
    liberar_fila(fila0);
    liberar_fila(fila1);
    printf("Maria deve memorizar %d regioes.\n", regioes -1);
}