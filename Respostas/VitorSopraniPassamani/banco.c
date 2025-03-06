#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "banco.h"

#define DEBUG_BANCO 1

struct Banco {
    Ator** atores;
    int qtdAtores;
    
    fptr_comparaDados compara;
};

Banco* criaBanco(fptr_comparaDados compara) {
    Banco* b = (Banco*)malloc(sizeof(Banco));

    #if DEBUG_BANCO
        assert(b != NULL);
    #else
        if (b == NULL)
            return NULL;
    #endif

    b->atores = (Ator**)malloc(0);//Alocando com tamanho 0 para posteriormente fazer os reallocs na medida qe atores são adicionados.

    b->qtdAtores = 0;
    b->compara = compara;

    return b;
}

void desalocaBanco(Banco* b) {
    if (b != NULL) {
        if (b->atores != NULL) {
            for (int i = 0; i < b->qtdAtores; i++)
                desalocaAtor(b->atores[i]);
            
            free(b->atores);
        }

        free(b);
    }
}


void imprimeBanco(Banco* b) {
    #if DEBUG_BANCO
        assert( b != NULL);
    #else
        if (b == NULL)
            return;
    #endif

    for (int i = 0; i < b->qtdAtores; i++) {
        imprimeAtor(b->atores[i]);
    }
}

Ator* getAtorBanco(Banco* b, int idx) {
    #if DEBUG_BANCO
        assert(b != NULL);
        assert(idx >= 0);
        assert(idx < b->qtdAtores);
    #else
        if (b == NULL)
            return NULL;
        if (idx < 0 || idx >= b->qtdAtores)
            return NULL;
    #endif

    return b->atores[idx];
}

void insereAtorBanco(Banco* b, Ator* a) {
    #if DEBUG_BANCO
        assert(b != NULL);
        assert(a != NULL);
    #else
        if (b == NULL || a == NULL)
            return;
    #endif

    b->qtdAtores++;
    
    b->atores = (Ator**)realloc(b->atores, sizeof(Ator*) * b->qtdAtores);

    #if DEBUG_BANCO
        assert(b->atores != NULL);
    #else
        if (b->atores == NULL)
            return;
    #endif

    b->atores[b->qtdAtores - 1] = a;
}

int getTamanhoBanco(Banco* b) {
    #if DEBUG_BANCO
        assert(b != NULL);
    #else
        if (b == NULL);
            return 0;
    #endif

    return b->qtdAtores;
}

/**
 * @brief Função que ordena um banco de acordo com sua função callback de comparação.
 * @param b O banco a ser ordenado.
 */
void ordenaBanco(Banco* b);

/**
 * @brief Função que cria uma copia de um banco.
 * @param destino Estrutura do tipo banco que receberá a cópia.
 * @param origem Estrutura original que será copiada.
 */
void copiaBanco(Banco* destino, Banco* origem);

int comparaAtoresBanco(Banco* b, int idx1, int idx2) {
    #if DEBUG_BANCO
        assert(b != NULL);
    #else
        if (b == NULL)
            return 0;
    #endif

    Ator* a1 = getAtorBanco(b, idx1);
    Ator* a2 = getAtorBanco(b, idx2);

    return b->compara(getDadoAtor(a1), getDadoAtor(a2));
}