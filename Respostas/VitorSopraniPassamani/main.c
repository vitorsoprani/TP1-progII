#include <stdio.h>
#include <string.h>

#include "sistema.h"
#include "utils.h"

#define MAX_TAM_ENTRADA 10

int main() {
    Data* hoje = criaData(18, 2, 2025);

    Sistema* sistema = criaSistema(hoje);
    
    char opcao = 0;

    while(1) {
        scanf("%c", &opcao);
        CleanBuffer();

        if (opcao == 'F') {
            break;
        } else if (opcao == 'U') {
            insereAtorSistema(sistema, "USUARIO");
        } else if (opcao == 'T') {
           insereAtorSistema(sistema, "TECNICO");
        } else if (opcao == 'A') {
            insereTicketSistema(sistema);
        } else if (opcao == 'E') {
            char entrada[MAX_TAM_ENTRADA];
            scanf("%s", entrada);

            if (strcmp("NOTIFICA", entrada) == 0) {
                CleanBuffer();
                notificaTicketsSistema(sistema);
            } else if (strcmp("TECNICOS", entrada) == 0) {
                CleanBuffer();
                imprimeBancoSistema(sistema, "TECNICOS");
            } else if (strcmp("USUARIOS", entrada) == 0) {
                CleanBuffer();
                imprimeBancoSistema(sistema, "USUARIOS");
            } else if (strcmp("DISTRIBUI", entrada) == 0) {
                CleanBuffer();
                distribuiTicketsSistema(sistema);
            } else if (strcmp("RANKING", entrada) == 0) {
                char opcaoBanco[MAX_TAM_ENTRADA];
                scanf(" %s", opcaoBanco);
                CleanBuffer();

                imprimeRankingSistema(sistema, opcaoBanco);
            } else if (strcmp("RELATORIO", entrada) == 0) {
                CleanBuffer();
                imprimeRelatorioSistema(sistema);
            }
        }
    }

    desalocaSistema(sistema);
    return 0;
}
