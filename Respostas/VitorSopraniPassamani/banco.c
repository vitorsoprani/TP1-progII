#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

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
        printf("--------------------\n");
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

Ator* getAtorPorCPFBanco(Banco* b, char* cpf) {
    #if DEBUG_BANCO
        assert(b != NULL);
    #else
        if (b == NULL)
            return NULL;
    #endif

    for (int i = 0; i < b->qtdAtores; i++) {
        if (strcmp(getCPFAtor(b->atores[i]), cpf) == 0)
            return b->atores[i];
    }

    return NULL;
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
void ordenaBanco(Banco* b) {
    #if DEBUG_BANCO
        assert(b != NULL);
    #else
        if (b == NULL)
            return NULL;
    #endif

    //BUBBLE SORT:
    for (int i = 0; i < getTamanhoBanco(b) - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < getTamanhoBanco(b) - i - 1; j++) {
            if (comparaAtoresBanco(b, j, j + 1) > 0) {
                Ator* aux = b->atores[j];
                b->atores[j] = b->atores[j + 1];
                b->atores[j + 1] = aux;

                trocou = 1;
            }
        }
        if (!trocou)
            break;
    }
}

/**
 * @brief Função que cria uma copia de um banco.
 * @brief ATENÇÃO: as referencias são compartilhadas entre a copia e o original. as alterações feitas em um aparecerão no outro.
 * @param origem Estrutura original que será copiada.
 * @return A copia da estrurura fornecida.
 */
Banco* copiaBanco(Banco* origem) {
    #if DEBUG_BANCO
        assert(origem != NULL);
    #else
        if (origem == NULL)
            return NULL;
    #endif

    Banco* copia = (Banco*)malloc(sizeof(Banco));

    #if DEBUG_BANCO
        assert(copia != NULL);
    #else
        if (copia == NULL)
            return NULL;
    #endif

    copia->qtdAtores = origem->qtdAtores;
    copia->compara = origem->compara;
    
    copia->atores = (Ator**)malloc(sizeof(Ator*) * copia->qtdAtores);

    #if DEBUG_BANCO
        assert(copia->atores != NULL);
    #else
        if (copia->atores == NULL)
            return NULL;
    #endif

    for (int i = 0; i < copia->qtdAtores; i++) {
        copia->atores[i] = origem->atores[i];
    }

    return copia;
}

void desalocaCopiaBanco(Banco* b) {
    if (b != NULL) {
        free(b->atores);
        free(b);
    }
}

int comparaAtoresBanco(Banco* b, int idx1, int idx2) {
    #if DEBUG_BANCO
        assert(b != NULL);
    #else
        if (b == NULL)
            return 0;
    #endif

    Ator* a1 = getAtorBanco(b, idx1);
    Ator* a2 = getAtorBanco(b, idx2);

    int result = b->compara(getDadoAtor(a1), getDadoAtor(a2));

    if (result == 0) {
        return strcmp(getNomeAtor(a1), getNomeAtor(a2));
    }

    return result;
}