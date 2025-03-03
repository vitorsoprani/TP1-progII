#include <stdio.h>

#include "manutencao.h"
#include "software.h"
#include "outros.h"
#include "fila.h"

int main() {
    Fila* tickets = criaFila();

    Software* s;
    Manutencao* m;
    Outros* o;

    char tipo = '\0';
    char cpf[MAX_TAM_CPF];

    while(1) {
        scanf("%c%*c", &tipo);
        
        if (tipo == 's') {
            scanf("%[^\n]%*c", cpf);
            s = lerSoftware();
            insereTicketFila(tickets, cpf, s, getTempoEstimadoSoftware, getTipoSoftware, notificaSoftware, desalocaSoftware);
        } else if (tipo == 'm') {
            scanf("%[^\n]%*c", cpf);
            m = lerManutencao();
            insereTicketFila(tickets, cpf, m, getTempoEstimadoManutencao, getTipoManutencao, notificaManutencao, desalocaManutencao);
        } else if (tipo == 'o') {
            scanf("%[^\n]%*c", cpf);
            o = lerOutros();
            insereTicketFila(tickets, cpf, o, getTempoEstimadoOutros, getTipoOutros, notificaOutros, desalocaOutros);
        } else {
            break;
        }
    }
    
    notificaFila(tickets);
    desalocaFila(tickets);
    return 0;
}
