#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "usuario.h"
#include "utils.h"

#define DEBUG_USUARIO 1

struct Usuario {
    char* setor;

    int qtdTickets;
};

Usuario* criaUsuario(char* setor) {
    Usuario* u = (Usuario*)malloc(sizeof(Usuario));

    #if DEBUG_USUARIO
        assert(u != NULL);
    #else
        if (u == NULL)
            return NULL;
    #endif

    //  Alocando a string com o tamanho necessário:
    u->setor = (char*)malloc(sizeof(char) * (strlen(setor) + 1));

    #if DEBUG_USUARIO
        assert(u->setor != NULL);
    #else
        if (u->setor == NULL)
            return NULL;
    #endif
    
    //  Atribuindo os valores:
    strcpy(u->setor, setor);

    u->qtdTickets = 0;

    return u;
}

Usuario* lerUsuario() {
    char setor[MAX_TAM_SETOR];

    scanf("%[^\n]", setor);
    CleanBuffer();

    return criaUsuario(setor);
}

void incrementaTicketsUsuario(Usuario* u) {
    #if DEBUG_USUARIO
        assert(u != NULL);
    #else
        if (u == NULL)
            return;
    #endif

    u->qtdTickets++;
}

int getTicketsUsuario(Usuario* u) {
    #if DEBUG_USUARIO
        assert(u != NULL);
    #else
        if (u == NULL)
            return 0;
    #endif

    return u->qtdTickets;
}

void desalocaUsuario(void* dado) {
    if (dado != NULL) {
        free(CAST(Usuario, dado)->setor);
        
        free(dado);
    }
}

void imprimeUsuario(void* dado) {
    #if DEBUG_USUARIO
        assert(dado != NULL);
    #else
        if (dado == NULL)
            return;
    #endif

    printf("- Setor: %s\n", CAST(Usuario, dado)->setor);
    printf("- Tickets soliciatos: %d\n", CAST(Usuario, dado)->qtdTickets);
}