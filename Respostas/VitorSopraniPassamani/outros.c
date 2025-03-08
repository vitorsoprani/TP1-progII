#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "outros.h"
#include "utils.h"

#define DEBUG_OUTROS 1

struct Outros {
    char* descricao;
    char* local;

    int dificuldade; //Nivel de dificuldade para resolver o problema.
    int tempoEstimado; //Terá o mesmo valor que a dificuldade, mas por padrao usarei uma variavel diferente.
};

Outros* criaOutros(char* descricao, char* local, int dificuldade) {
    Outros* o = (Outros*)malloc(sizeof(Outros));

    #if DEBUG_OUTROS
        assert(o != NULL);
    #else
        if (o == NULL)
            return NULL;
    #endif

    //  Alocando a quantidade de memória necessária para cada string:
    o->descricao = (char*)malloc(sizeof(char) * (strlen(descricao) + 1));
    o->local = (char*)malloc(sizeof(char) * (strlen(local) + 1));

    #if DEBUG_OUTROS
        assert(o->descricao != NULL);
        assert(o->local != NULL);
    #else
        //DAR O FREE NO O.
        if (o->descricao == NULL || o->local == NULL);
            return NULL;
    #endif

    //  Atribuindo os valores:
    strcpy(o->descricao, descricao);
    strcpy(o->local, local);

    o->dificuldade = dificuldade;
    o->tempoEstimado = 0;

    return o;
}

Outros* lerOutros() {
    char descricao[MAX_TAM_DESCRICAO];
    char local[MAX_TAM_LOCAL];
    int dificuldade = 0;

    //REFORMULAR LEIURA DE DADOS PARA TRATAR ERROS DE USUARIO.
    scanf("%[^\n]", descricao);
    CleanBuffer();
    scanf("%[^\n]", local);
    CleanBuffer();
    scanf("%d", &dificuldade);
    CleanBuffer();

    return criaOutros(descricao, local, dificuldade);
}

void setTempoEstimadoOutros(Outros* o) {
    #if DEBUG_OUTROS
        assert(o != NULL);
    #else
        if (o == NULL)
            return;
    #endif

    o->tempoEstimado = o->dificuldade;
}

int getTempoEstimadoOutros(void* dado) {
    #if DEBUG_OUTROS
        assert(dado != NULL);
    #else
        if (dado == NULL)
            return 0;
    #endif

    return CAST(Outros, dado)->tempoEstimado;
}

char getTipoOutros() {
    return 'O';
}

void desalocaOutros(void* dado) {
    if (dado != NULL) {
        free(CAST(Outros, dado)->descricao);
        free(CAST(Outros, dado)->local);

        free(dado);
    }
}

void notificaOutros(void* dado) {
    #if DEBUG_OUTROS
        assert(dado != NULL);
    #else
        if (dado == NULL)
            return;
    #endif

    printf("- Tipo: Outros\n");
    printf("- Descricao: %s\n", CAST(Outros, dado)->descricao);
    printf("- Local: %s\n", CAST(Outros, dado)->local);
    printf("- Nivel de Dificuldade: %d\n", CAST(Outros, dado)->dificuldade);
    printf("- Tempo Estimado: %dh\n", CAST(Outros, dado)->tempoEstimado);
}