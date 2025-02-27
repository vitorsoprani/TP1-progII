#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "software.h"

#define DEBUG_SOFTWARE  1

//Faz o casting de um ponteiro qualquer 'b' para um ponteiro do tipo 'a'.
#define CAST(a, b) ((a*)b)

struct Software {
    char* nome;
    char* categoria;
    char* motivo;

    int tempoEstimado;
    int impacto;
};

void CleanBuffer() {
    while(getchar() != '\n') {};
}

Software *criaSoftware(char *nome, char *categoria, int impacto, char *motivo) {
    Software* s = (Software*)malloc(sizeof(Software));
    
    #if DEBUG_SOFTWARE
        assert(s != NULL);
    #else
        if (s == NULL)
            return NULL;
    #endif

    //  Alocando a memoria necessária para cada string (sem deseperdiçar espaço)
    //      (o numero de caracteres correspondente à string + o caracter nulo '\0')
    s->nome = (char*)malloc(sizeof(char) * (strlen(nome) + 1));
    s->categoria = (char*)malloc(sizeof(char) * (strlen(categoria) + 1));
    s->motivo = (char*)malloc(sizeof(char) * (strlen(motivo) + 1));

    #if DEBUG_SOFTWARE
        assert(s->nome != NULL);
        assert(s->categoria != NULL);
        assert(s->motivo != NULL);
    #else
        if (s->nome == NULL || s->categoria==NULL || s->motivo == NULL)
            return NULL;
    #endif

    //  Atribuindo os atributos para o objeto:
    strcpy(s->nome, nome);
    strcpy(s->categoria, categoria);
    strcpy(s->motivo, motivo);

    s->impacto = impacto;

    setTempoEstimadoSoftware(s);

    return s;
}

Software *lerSoftware() {
    char nome[MAX_TAM_NOME_SOFTWARE];
    char categoria[MAX_TAM_CAT];
    char motivo[MAX_TAM_MOTIVO];
    int impacto;


    // PARA DEPOIS: REFORMULAR LEIURA DE DADOS PARA TRATAR ERROS DE USUARIO.
    scanf("%[^\n]", nome);
    CleanBuffer();
    scanf("%[^\n]", categoria);
    CleanBuffer();
    scanf("%d", &impacto);
    CleanBuffer();
    scanf("%[^\n]", motivo);

    return criaSoftware(nome, categoria, impacto, motivo);
}

void setTempoEstimadoSoftware(Software *s) {
    #if DEBUG_SOFTWARE
        assert(s != NULL);
    #else 
        if (s == NULL)
            return;
    #endif

    if (strcmp(s->categoria, "BUG") == 0) {
        s->tempoEstimado = TEMPO_ESTIMADO_BUG + s->impacto;
    } else if (strcmp(s->categoria, "OUTROS") == 0) {
        s->tempoEstimado = TEMPO_ESTIMADO_OUTROS + s->impacto;
    } else if (strcmp(s->categoria, "DUVIDA") == 0) {
        s->tempoEstimado = TEMPO_ESTIMADO_DUVIDA + s->impacto;
    } else {
        #if DEBUG_SOFTWARE
            printf("[ERRO] - Na função setTempoEstimadoSoftware.\n\tCategoria nao identificada: (%s).\n", s->categoria);
            exit(1);
        #endif
    }
}

int getTempoEstimadoSoftware(void *dado) {
    #if DEBUG_SOFTWARE
        assert(dado != NULL);
    #else 
        if (s == NULL)
            return 0;
    #endif

    return CAST(Software, dado)->tempoEstimado;
}

char getTipoSoftware() {
    //???
    return 'S';
}

void desalocaSoftware(void *s) {
    if (s != NULL) {
        free(CAST(Software, s)->nome);
        free(CAST(Software, s)->categoria);
        free(CAST(Software, s)->motivo);

        free(s);
    }
}

void notificaSoftware(void *dado) {
    #if DEBUG_SOFTWARE
        assert(dado != NULL);
    #else
        if (dado == NULL)
            return;
    #endif
    
    printf("- Tipo: Software\n");
    printf("- Nome do software: %s\n", CAST(Software, dado)->nome);
    printf("- Categoria: %s\n", CAST(Software, dado)->categoria);
    printf("- Nível do impacto: %d\n", CAST(Software, dado)->impacto);
    printf("- Motivo: %s\n", CAST(Software, dado)->motivo);
    printf("- Tempo estimado: %dh\n", CAST(Software, dado)->tempoEstimado);
}