#include <stdio.h>

#include "manutencao.h"
#include "software.h"
#include "fila.h"

int main() {
    Fila* tickets = criaFila();

    Software* s;
    Manutencao* m;

    for (int i = 0; i < 1; i++) {
        s = lerSoftware();
        insereTicketFila(tickets, "11111", s, getTempoEstimadoSoftware, getTipoSoftware, notificaSoftware, desalocaSoftware);
    }

    for (int i = 0; i < 2; i++) {
        m = lerManutencao();
        insereTicketFila(tickets, "22222", m, getTempoEstimadoManutencao, getTipoManutencao, notificaManutencao, desalocaManutencao);
    }

    notificaFila(tickets);

    return 0;
}
