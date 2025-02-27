#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "ticket.h"

#define DEBUG_TICKET    1

#define ABERTO          'A'
#define FINALIZADO      'F'  

struct Ticket {
    void* dado;
    char* cpfSol;
    char* id;
    char status;

    func_ptr_tempoEstimado getTempo;
    func_ptr_tipo getTipo;
    func_ptr_notifica notifica;
    func_ptr_desaloca desaloca;
};

Ticket *criaTicket(char *cpfSol, void *dado, func_ptr_tempoEstimado getTempo, func_ptr_tipo getTipo, func_ptr_notifica notifica, func_ptr_desaloca desaloca) {
    #if DEBUG_TICKET
        assert(dado != NULL);
    #else
        if (dado == NULL)
            return NULL;
    #endif
    
    //  Alocando o ticket e tratando erros:
    Ticket* t = (Ticket*)malloc(sizeof(Ticket));    
    #if DEBUG_TICKET
        assert(t != NULL);
    #else
        if (t == NULL)
            return NULL;
    #endif

    //  Atribuindo os "métodos":
    t->getTempo = getTempo;
    t->getTipo = getTipo;
    t->notifica = notifica;
    t->desaloca = desaloca;

    //  Alocando a string com espaço justificado:
    t->cpfSol = (char*)malloc(sizeof(char) * (strlen(cpfSol) + 1)); 
    #if DEBUG_TICKET
        assert(t->cpfSol != NULL);
    #endif

    //  Atribuindo as strings:
    if (t->cpfSol != NULL)
        strcpy(t->cpfSol, cpfSol);
    t->id = NULL;

    t->dado = dado;
    t->status = ABERTO;

    return t;
}

void setIDTicket(Ticket *d, char *id) {
    #if DEBUG_TICKET
        assert(d != NULL);
        assert(id != NULL);
    #else
        if (id == NULL || id == NULL)
            return;
    #endif

    //  Alocando a string com espaço justificado:
    d->id = malloc(sizeof(char) * (strlen(id) + 1));
    #if DEBUG_TICKET
        assert(d != NULL);
    #else
        if (d->id == NULL)
            return;
    #endif

    strcpy(d->id, id);
}

void finalizaTicket(Ticket *t) {
    #if DEBUG_TICKET
        assert(t != NULL);
        assert(t->status == ABERTO);
    #else
        if (t == NULL)
            return;
    #endif

    t->status = FINALIZADO;
}

char *getCPFSolicitanteTicket(Ticket *t) {
    #if DEBUG_TICKET
        assert(t != NULL);
        assert(t->cpfSol != NULL);
    #else
        if (t==NULL)
            return "";
        if (t->cpfSol == NULL)
            return "";
    #endif

    return t->cpfSol;
}

int getTempoEstimadoTicket(Ticket *t) {
    #if DEBUG_TICKET
        assert(t != NULL);
    #else
        if (t == NULL)
            return 0;
    #endif

    return t->getTempo(t->dado);
}

char getTipoTicket(Ticket *t) {
    #if DEBUG_TICKET
        assert(t != NULL);
    #else
        if (t == NULL)
            return '\0';
    #endif

    return t->getTipo();
}

char getStatusTicket(Ticket *t) {
    #if DEBUG_TICKET
        assert(t != NULL);
    #else
        if (t == NULL)
            return '\0';
    #endif

    return t->status;
}

void desalocaTicket(Ticket *doc) {
    if (doc != NULL) {
        free(doc->cpfSol);
        free(doc->id);

        doc->desaloca(doc->dado);
        
        free(doc);
    }
}

void notificaTicket(Ticket *doc) {
    #if DEBUG_TICKET
        assert(doc != NULL);
        assert(doc->dado != NULL);
    #else
        if (doc == NULL)
            return;
        if (doc->dado == NULL)
            return;
    #endif

    printf("---------TICKET-----------\n");
    printf("- ID: %s\n", doc->id);
    printf("- Usuario solicitante: %s\n", doc->cpfSol);

    doc->notifica(doc->dado);

    printf("- Status: ");
    if (doc->status == FINALIZADO) {
        printf("Finalizado\n");
    } else if (doc->status == ABERTO) {
        printf("Aberto\n");
    } else {
        #if DEBUG_TICKET
            printf("[ERRO] - Na funcao notificaTicket.\n\tStatus invalido. (%c).\n", doc->status);
        #else
            printf(" - ");
        #endif
    }

    printf("-------------------------\n\n");
}