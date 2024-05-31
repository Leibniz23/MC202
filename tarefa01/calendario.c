#include <stdio.h>

int elevar(int base, int expoente) {
    if (expoente == 0 && base != 0)
        return 1;
    int result = 1;
    for (int i = 1; i <= expoente; i++) {
        result *= base;
    }
    return result;
}

int base10(int base6) {
    int exp, fator, base10 = 0;
    for (exp = 8; exp >= 0; exp--){
        fator = base6 / elevar(10, exp);
        base6 = base6 % elevar(10, exp);
        base10 += fator*elevar(6, exp);
    }
    return base10;
}

int main() {
    int datas[3];
    int mes, ano, t6, t10;
    scanf("%d/%d/%d", &datas[0], &datas[1], &datas[2]);
    scanf("%d %d", &mes, &ano);
    scanf("%d", &t6);
    t10 = base10(t6);
    int dias_ano = mes*ano;
    datas[2] += t10 / dias_ano;
    t10 = t10 % dias_ano;
    datas[1] += t10 / mes;
    t10 = t10 % mes;
    datas[0] += t10;
    if (datas[0] > mes) {
        int aux;
        aux = datas[0] % mes;
        datas[1] += datas[0]/mes;
        datas[0] = aux;
    }
    if (datas[1] > ano) {
        int aux;
        aux = datas[1] % ano;
        datas[2] += datas[1] / ano;
        datas[1] = aux;
    }
    printf("%d/%d/%d\n", datas[0], datas[1], datas[2]); 
}