#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "manutencao.h"
#include "utils.h"

#define DEBUG_MANUTENCAO 1

struct Manutencao {
    char* item;
    char* estado;
    char* local;

    int tempoEstimado;
};

Manutencao* criaManutencao(char* item, char* estado, char* local) {
    Manutencao* m = (Manutencao*)malloc(sizeof(Manutencao));

    #if DEBUG_MANUTENCAO
        assert(m != NULL);
    #else
        if (m == NULL)
            return NULL;
    #endif

    //  Alocando somente a quantidade de memoria necessária para cada string:
    m->item = (char*)malloc(sizeof(char) * (strlen(item) + 1));
    m->estado = (char*)malloc(sizeof(char) * (strlen(estado) + 1));
    m->local = (char*)malloc(sizeof(char) * (strlen(local) + 1));

    #if DEBUG_MANUTENCAO
        assert(m->item != NULL);
        assert(m->estado != NULL);
        assert(m->local != NULL);
    #else
        if (m->item == NULL || m->estado == NULL || m->local == NULL)
            return NULL;
    #endif

    //  Atribuindo os parametros:
    strcpy(m->item, item);
    strcpy(m->estado, estado);
    strcpy(m->local, local);

    m->tempoEstimado = 0;

    return m;
}

Manutencao* lerManutencao() {
    char item[MAX_TAM_ITEM];
    char estado[MAX_TAM_ESTADO];
    char local[MAX_TAM_LOCAL];


    //REFORMULAR LEIURA DE DADOS PARA TRATAR ERROS DE USUARIO.
    scanf("%[^\n]", item);
    CleanBuffer();
    scanf("%[^\n]", estado);
    CleanBuffer();
    scanf("%[^\n]", local);
    CleanBuffer();

    return criaManutencao(item, estado, local);
}


void setTempoEstimadoManutencao(Manutencao* m, char* setor) {
    #if DEBUG_MANUTENCAO
        assert(m != NULL);
    #else
        if (m == NULL)
            return;
    #endif

    int base = 0;

    if (strcmp(m->estado, "BOM") == 0) {
        base = 1;
    } else if (strcmp(m->estado, "REGULAR") == 0) {
        base = 2;
    } else if (strcmp(m->estado, "RUIM") == 0) {
        base = 3;
    } else {
        #if DEBUG_MANUTENCAO
            printf("[ERRO] - Na funcao 'setTempoEstimadoManutencao'\n\tEstado nao identificado (%s)", setor);
            exit(1);
        #else
            return;
        #endif
    }
    
    if (strcmp(setor, "RH") == 0) {
        m->tempoEstimado = base * 2;
    } else if (strcmp(setor, "FINANCEIRO") == 0) {
        m->tempoEstimado = base * 3;
    } else if (strcmp(setor, "P&D") == 0) {
        m->tempoEstimado = base * 1;
    } else if (strcmp(setor, "VENDAS") == 0) {
        m->tempoEstimado = base * 1;
    } else if (strcmp(setor, "MARKETING") == 0) {
        m->tempoEstimado = base * 1;
    } else {
        #if DEBUG_MANUTENCAO
            printf("[ERRO] - Na funcao 'setTempoEstimadoManutencao'\n\tSetor nao identificado (%s)", setor);
            exit(1);
        #else
            return;
        #endif
    }
}

int getTempoEstimadoManutencao(void* dado) {
    #if DEBUG_MANUTENCAO
        assert(dado != NULL);
    #else
        if (dado == NULL)
            return 0;
    #endif

    return CAST(Manutencao, dado)->tempoEstimado;
}

/**
 * @brief Retorna o tipo do ticket;
 * @return 'M' para manutencao.
 */
char getTipoManutencao() {
    return 'M';
}

void desalocaManutencao(void* dado) {
    if (dado != NULL) {
        free(CAST(Manutencao, dado)->item);
        free(CAST(Manutencao, dado)->estado);
        free(CAST(Manutencao, dado)->local);

        free(dado);
    }
}

void notificaManutencao(void* dado) {
    #if DEBUG_MANUTENCAO
        assert(dado != NULL);
    #else
        if (dado == NULL)
            return;
    #endif
    
    printf("- Tipo: Manutencao\n");
    printf("- Nome do item: %s\n", CAST(Manutencao, dado)->item);
    printf("- Estado de conservacao: %s\n", CAST(Manutencao, dado)->estado);
    printf("- Local: %s\n", CAST(Manutencao, dado)->local);
    printf("- Tempo estimado: %dh\n", CAST(Manutencao, dado)->tempoEstimado);
}