#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "fila.h"

#define DEBUG_FILA 1

struct Fila {
    void** tickets;//Vetor de ponteiros que armazena os tickets da fila.
    int qtdTickets;//Quantidade de tickets atualmente na fila.

};

Fila *criaFila() {
    Fila* f = (Fila*)malloc(sizeof(Fila));

    #if DEBUG_FILA
        assert(f != NULL);
    #else
        if (f == NULL)
            return f;
    #endif

    //  A fila inicia vaza, o vetor 'tickets' é alocado com tamanho 0 para ser realocado na medida em que os tickets vao entrando.
    f->qtdTickets = 0;
    f->tickets = (void**)malloc(0);

    return f;
}

void desalocaFila(Fila *f) {
    if (f != NULL) {
        for (int i = 0; i < f->qtdTickets; i++)
            desalocaTicket(f->tickets[i]);
        
        free(f->tickets);
        free(f);
    }
}

void insereTicketFila(Fila *f, char *cpfSol, void *dado, func_ptr_tempoEstimado getTempo, func_ptr_tipo getTipo, func_ptr_notifica notifica, func_ptr_desaloca desaloca) {
    #if DEBUG_FILA
    assert(f != NULL);
    assert(dado != NULL);
    #else
        if (f == NULL || dado == NULL)
            return;
    #endif
    
    Ticket* t = criaTicket(cpfSol, dado, getTempo, getTipo, notifica, desaloca);

    #if DEBUG_FILA
        assert(t != NULL);
    #else
        if (t == NULL)
            return;
    #endif
    
    
    //  Manipulando a memoria para comportar o novo ticket
    f->qtdTickets++;
    f->tickets = (void**)realloc(f->tickets, sizeof(void*) * f->qtdTickets);
    
    #if DEBUG_FILA
        assert(f->tickets != NULL);
    #else
        if (f->tickets == NULL)
            return;
    #endif

    f->tickets[f->qtdTickets - 1] = t;

    char id[MAX_TAM_ID] = "";
    sprintf(id, "Tick-%d", f->qtdTickets);
    setIDTicket(t, id);
}

int getQtdTicketsNaFila(Fila *f) {
    #if DEBUG_FILA
        assert(f != NULL);
    #else
        if (f == NULL)
            return 0;
    #endif

    return f->qtdTickets;
}

int getQtdTicketsPorStatusNaFila(Fila *f, char status) {
    #if DEBUG_FILA
        assert(f != NULL);
    #else
        if (f == NULL)
            return 0;
    #endif


    int qtd = 0;

    for (int i = 0; i < f->qtdTickets; i++) {
        if (getStatusTicket(f->tickets[i]) == status)
            qtd++;
    }

    return qtd;
}

Ticket *getTicketNaFila(Fila *f, int i) {
    #if DEBUG_FILA
        assert(f != NULL);
        assert(i < f->qtdTickets && i >= 0);
    #else
        if (f == NULL)
            return NULL;
        if (i >= f->qtdTickets || i < 0)
            return NULL;
    #endif

    return f->tickets[i];
}

void notificaFila(Fila *f) {
    #if DEBUG_FILA
        assert(f != NULL);
    #else
        if (f == NULL)
            return;
    #endif

    for (int i = 0; i < f->qtdTickets; i++) {
        notificaTicket(((Ticket*)f->tickets[i]));
    }
}