encontrar_solucao(n, m, coluna) {
    se m=0
        se é uma solução valida()
        printa a solucao
    se nao é um prefixo viavel
        retorna falso
    se a coluna >= n
        coluna = coluna % n
    
    senao
        para cada linha da matriz
            a[i][coluna] = rainha
            se encontrar solucao com(n, m-1, coluna+1)
                retorna true
            a[i][coluna] = espaco
            se encontrar solucao com(n, m, coluna+1)
                retorna true
            a[i][coluna] = peao
            se encontrar solucao com(n, m, coluna+1)
                retorna true
    retorna -1

n=3
m=3
coluna=1
}

prefixo é viavel se nao tiver nenhuma rainha colada com a outra 

. r . . 
r . . . 
. . . . 
. . . . 