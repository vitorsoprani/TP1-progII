#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "data.h"
#include "utils.h"

#define DEBUG_DATA 1

struct Data {
    int dia;
    int mes;
    int ano;
};

Data* criaData(int dia, int mes, int ano) {
    Data* d = (Data*)malloc(sizeof(Data));

    #if DEBUG_DATA
        assert(d != NULL);
    #else
        if (d == NULL)
            return NULL;
    #endif

    d->dia = dia;
    d->mes = mes;
    d->ano = ano;

    return d;
}

Data* lerData() {
    int dia, mes, ano;

    scanf("%d/%d/%d", &dia, &mes, &ano);
    CleanBuffer();

    return criaData(dia, mes, ano);
}

void imprimeData(Data* d) {
    #if DEBUG_DATA
        assert(d != NULL);
    #else
        if (d == NULL)
            return;
    #endif

    printf("%d/%d/%d\n", d->dia, d->mes, d->ano);
}

int calculaDiferencaAnosData(Data* d1, Data* d2) {
    #if DEBUG_DATA
        assert(d1 != NULL);
        assert(d2 != NULL);
    #else
        if (d1 == NULL || d2 == NULL)
            return 0;
    #endif

    int diferenca = d2->ano - d1->ano;

    if (d2->mes < d1->mes)
        return diferenca - 1;
    
    if (d2->mes == d1->mes && d2->dia < d1->dia)
        return diferenca - 1;
    
    return diferenca;
}

void desalocaData(Data* d) {
    free(d);
}