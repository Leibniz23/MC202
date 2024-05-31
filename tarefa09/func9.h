#define PRETA 0
#define BRANCA 0xFFFFFF
#define MEDIA_PIXELS 128 // valor inicial arbitrário para o tamanho da fila

typedef struct {
    int cor;
    int i;
    int j;
    int visitado; // 1 se ja foi visitado e 0 se ainda nao
    int distancia; // distancia conhecida até aquele pixel, começa com INT_MAX em todos que não são a raiz
} coord;

typedef struct fc *p_fc;

struct fc { // fila de coordenadas
    coord *coords;
    int n; // posições em uso da fila
    int alocado; // tamanho total da fila
};

typedef struct imagem *p_img;

struct imagem {
    int w, h;
    int **pix;
};

/*
Utilizei uma representação diferente das vistas em aula para o grafo, que pode ser entendido
como a matriz de visitados, sendo que cada coord seria um vértice e seus vizinhos seguem o conceito de
adjacência passado na tarefa, sendo que uma aresta pode ter peso 0 caso os vértices que ela liga sejam da mesma
cor ou então peso 1 caso contrário. (criado na função criar_visitados)
No momento da busca pelo caminho utilizei uma adaptação do algoritmo de Dijkstra para caminhos mínimos,
tipicamente usado em grafos com peso nas arestas, como é o caso. (principalmente na função encontrar_regioes)
*/


p_fc criar_fc(int tam);
/*
Aloca e retorna uma fila de coordenadas

--Parameters:

---- tam (int): Inteiro

--Returns:

---- fila (p_fc): Ponteiro para struct fc
*/

void enfilera(p_fc v, coord x);
/*
Enfileira um elemento em uma fila de coordenadas

--Parameters:

---- fila (p_fc): Ponteiro para struct fc

---- x (coord): Struct coord
*/

void liberar_fila(p_fc fila);
/*
Libera toda a memória alocada em uma fila de coordenadas

--Parameters:

---- fila (p_fc): Ponteiro para struct fc
*/

struct imagem *ler_imagem();

void liberar_imagem(struct imagem *img);

void pintar(p_img img, int i, int j);
/*
Dado uma coordenada (i,j) de uma região branca, pinta a região inteira de preto
*/

coord **criar_visitados(p_img img, coord inicio);
/*
Cria, com base na imagem, uma matriz com os pixel que já foram visitados e
os que ainda serão e suas distancias do início

--Parameters:

---- img (p_img): Ponteiro para struct img

--Return:

---- inicio (coord): Struct coord
*/

void liberar_visitados(coord **visitados, int max_i);
/*
Libera a matriz de visitados
*/

coord marcar_inicio(p_img img);
/*
Escolhe uma região branca da imagem e pinta ela de preto, retornando a
coordenada de um pixel dessa região de início

--Parameters:

---- img (p_img): Ponteiro para struct img

--Return:

---- inicio (coord): Struct coord
*/

int vazia(p_fc fila);
/*
Retorna 1 se a fila estiver vazia e 0 caso contrário
*/

coord extrair_primeiro(p_fc fila);
/*
Extrai o primeiro elemento de uma fila de coordenadas

--Parameters:

---- fila0 (p_fc): Ponteiro para struct fc

--Return:

---- aux (coord): Struct coord
*/

void atualiza_pixel(coord pixel, coord **visitados, p_fc fila0, p_fc fila1, int i, int j);
/*
Muda a distância de um pixel da matriz de visitados e o coloca em alguma fila, caso seja necessário

--Parameters:

---- pixel (coord): Struct coord

---- visitados (coord **): Ponteiro para ponteiro de coord (matriz)

---- fila0 (p_fc): Ponteiro para struct fc

---- fila1 (p_fc): Ponteiro para struct fc

---- i (int): Inteiro

---- j (int): Inteiro
*/

void encontrar_regioes(coord **visitados, p_fc fila0, p_fc fila1, int max_i, int max_j, int *cont);
/*
Encontra o caminho de uma região até a região branca, passando pelo mínimo de regiões possível
e modifica a variável cont para o número de regiões do menor caminho

--Parameters:

---- visitados (coord **): Ponteiro para ponteiro de coord (matriz)

---- fila0 (p_fc): Ponteiro para struct fc

---- fila1 (p_fc): Ponteiro para struct fc

---- max_i (int): Inteiro

---- max_j (int): Inteiro

---- cont (int *): Ponteiro para inteiro
*/

void calcular_adjacencias(coord pixel, coord **visitados, p_fc fila0, p_fc fila1, int max_i, int max_j);
/*
Calcula se a distância dos pixels adjacentes ao analisado deve ser alterada,
caso o caminho por esse pixel analisado para seus adjacentes seja menor que o antigo caminho conhecido

--Parameters:

---- pixel (coord): Struct coord

---- visitados (coord **): Ponteiro para ponteiro de coord (matriz)

---- fila0 (p_fc): Ponteiro para struct fc

---- fila1 (p_fc): Ponteiro para struct fc

---- max_i (int): Inteiro

---- max_j (int): Inteiro
*/