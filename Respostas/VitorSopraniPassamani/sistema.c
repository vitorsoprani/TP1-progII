/**
 * ATENÇÂO: Recado ao programador que eventualmente pode ler esse código.
 * Se você está lendo isso significa que eu nunca voltei aqui para consertar as linhas de códigos "temporarias".
 * Me sinto no dever de deixar claro que me envergonho de mais de 90% do código que está escrito neste arquivo
 * (nos outros até que a situação está aceitável).
 * Prometo que sou melhor que isso e que algum dia ainda retorno para consertar, mas agora não da, parece que
 * todas as provas do semestre se acumularam para uma única semana e eu preciso colocar muito conteudo em dia.
 * Ass. Vitor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "sistema.h"
#include "utils.h"

#define DEBUG_SISTEMA 1

struct Sistema {
    Banco* usuarios;
    Banco* tecnicos;

    Fila* tickets;

    Data* dataAtual;
};

Sistema* criaSistema(Data* dataAtual) {
    #if DEBUG_SISTEMA
        assert(dataAtual != NULL);
    #else
        if (dataAtual == NULL)
            return NULL;
    #endif

    Sistema* sis = (Sistema*)malloc(sizeof(Sistema));

    #if DEBUG_SISTEMA
        assert(sis != NULL);
    #else
        if (sis == NULL)
            return NULL;
    #endif

    sis->usuarios = criaBanco(comparaUsuarios);
    sis->tecnicos = criaBanco(comparaTecnicos);
    sis->tickets = criaFila();

    sis->dataAtual = dataAtual;

    return sis;
}

void desalocaSistema(Sistema* sis) {
    if (sis != NULL) {
        desalocaBanco(sis->usuarios);
        desalocaBanco(sis->tecnicos);

        desalocaFila(sis->tickets);

        desalocaData(sis->dataAtual);

        free(sis);
    }
}

void insereTicketSistema(Sistema* sis) {
    #if DEBUG_SISTEMA
        assert(sis != NULL);
    #else
        if (sis == NULL)
            return;
    #endif

    char cpfSol[MAX_TAM_CPF];
    char tipo[MAX_TAM_TIPO_TICKET];

    scanf("%[^\n]", cpfSol);
    CleanBuffer();
    scanf("%[^\n]", tipo);
    CleanBuffer();

    //  Identificando o ator responsavel pelo chamado.
    Ator* a = getAtorPorCPFBanco(sis->usuarios, cpfSol);
    if (a == NULL)
        return;

    //  Fazendo as operacoes necessarias com o usuario.
    Usuario* u = (Usuario*)getDadoAtor(a);
    incrementaTicketsUsuario(u);

    char* setor = getSetorUsuario(u);

    if (strcmp("MANUTENCAO", tipo) == 0) {
        Manutencao* m = lerManutencao();

        setTempoEstimadoManutencao(m, setor);

        insereTicketFila(sis->tickets, cpfSol, (void*)m, getTempoEstimadoManutencao, getTipoManutencao, notificaManutencao, desalocaManutencao);
    } else if (strcmp("SOFTWARE", tipo) == 0) {
        Software* s = lerSoftware();

        setTempoEstimadoSoftware(s);

        insereTicketFila(sis->tickets, cpfSol, (void*)s, getTempoEstimadoSoftware, getTipoSoftware, notificaSoftware, desalocaSoftware);
    } else if (strcmp("OUTROS", tipo) == 0) {
        Outros* o = lerOutros();

        setTempoEstimadoOutros(o);

        insereTicketFila(sis->tickets, cpfSol, (void*)o, getTempoEstimadoOutros, getTipoOutros, notificaOutros, desalocaOutros);
    } else {
        #if DEBUG_SISTEMA
            printf("[ERRO] - Na função insereTicketSistema.\n\tTipo de ticket não definido (%s).\n", tipo);
            exit(1);
        #else
            return;
        #endif
    }
}

void insereAtorSistema(Sistema* sis, char* tipo) {
    #if DEBUG_SISTEMA
        assert(sis != NULL);
    #else
        if (sis == NULL)
            return;
    #endif

    //  Variaveis temporarias (comuns a todos atores):
    char nome[MAX_TAM_NOME];
    char cpf[MAX_TAM_CPF];
    Data* dataNascimento;
    char telefone[MAX_TAM_TELEFONE];
    char genero[MAX_TAM_GENERO];

    //  Lendo as variaveis comuns:
    scanf("%[^\n]", nome);
    CleanBuffer();
    scanf("%[^\n]", cpf);
    CleanBuffer();
    dataNascimento = lerData();
    scanf("%[^\n]", telefone);
    CleanBuffer();
    scanf("%[^\n]", genero);
    CleanBuffer();
    
    Ator* a = NULL;
    if (strcmp("USUARIO", tipo) == 0) {
        Usuario* u = lerUsuario();
        a = getAtorPorCPFBanco(sis->usuarios, cpf);

        if (a != NULL) {
            //Se o usuario ja existe no banco de usuarios ignora a leitura.
            desalocaUsuario(u);
            desalocaData(dataNascimento);
            return;
        }

        a = criaAtor(nome, cpf, dataNascimento, telefone, genero, u, desalocaUsuario, imprimeUsuario);
        insereAtorBanco(sis->usuarios, a);
    } else if (strcmp("TECNICO", tipo) == 0) {
        Tecnico* t = lerTecnico();
        a = getAtorPorCPFBanco(sis->tecnicos, cpf);

        if (a != NULL) {
            //Se o tecnico ja existe no banco de tecnico ignora a leitura.
            desalocaTecnico(t);
            desalocaData(dataNascimento);
            return;
        }

        a = criaAtor(nome, cpf, dataNascimento, telefone, genero, t, desalocaTecnico, imprimeTecnico);
        insereAtorBanco(sis->tecnicos, a);
    } else {
        #if DEBUG_SISTEMA
            printf("[ERRO] - Na funcao insereAtorSistema.\n\tTipo nao identificado (%s).\n", tipo);
            exit(1);
        #else
            return;
        #endif
    }

}

void distribuiTicketsSistema(Sistema* sis) {
    int idxTicket = 0;
    int idxAtor = 0;

    Ticket* tickAtual = NULL;
    Ator* atorAtual = NULL;
    Tecnico* tec = NULL;

    int inicioRodadaTicket = 0;

    while (idxTicket < getQtdTicketsNaFila(sis->tickets)) {
        tickAtual = getTicketNaFila(sis->tickets, idxTicket);
        
        if (getStatusTicket(tickAtual) != 'A') {
            idxTicket++;
            continue;
        }

        atorAtual = getAtorBanco(sis->tecnicos, idxAtor);
        tec = (Tecnico*)getDadoAtor(atorAtual);

        if (ehCompativelTicketTecnicoSistema(tickAtual, tec)) {
            int tempoTrabalho = getTempoEstimadoTicket(tickAtual);
            atribuiTrabalhoTecnico(tec, tempoTrabalho);
            finalizaTicket(tickAtual);

            idxTicket++;
            idxAtor++;
            if (idxAtor >= getTamanhoBanco(sis->tecnicos))
                idxAtor = 0;
            inicioRodadaTicket = idxAtor;

            continue;
        }
        
        idxAtor++;
        if (idxAtor >= getTamanhoBanco(sis->tecnicos))
            idxAtor = 0;
        
        if (idxAtor == inicioRodadaTicket) {
            idxTicket++;
            inicioRodadaTicket = idxAtor;
        }
    }
}

int ehCompativelTicketTecnicoSistema(Ticket* tic, Tecnico* tec) {
    #if DEBUG_SISTEMA
        assert(tic != NULL);
        assert(tec != NULL);
    #else
        if (tic == NULL || tec == NULL)
            return 0;
    #endif

    //  CHECANDO SE OS TIPOS SÃO COMPATIVEIS:
    char tipoTicket = getTipoTicket(tic);

    if (tipoTicket == 'S') {
        if(strcmp("TI", getAreaTecnico(tec)) != 0)
            return 0;
    } else if (tipoTicket == 'M') {
        if (strcmp("GERAL", getAreaTecnico(tec)) != 0)
            return 0; 
    } else if (tipoTicket == 'O') {
        if (strcmp("GERAL", getAreaTecnico(tec)) != 0)
            return 0; 
    } else {
        #if DEBUG_SISTEMA
            printf("[ERRO] - na funcao ehCompativelTicketTecnicoSistema.\n\tTipo do ticket nao identificado(%c).\n", tipoTicket);
            exit(1);
        #else
            return 0;
        #endif
    }

    //  CHECANDO SE O TECNICO TEM TEMPO DISPONIVEL:
    if (getTempoEstimadoTicket(tic) > getDisponibilidadeAtualTecnico(tec))
        return 0;

    return 1;
}

void imprimeBancoSistema(Sistema* sis, char* banco) {
    #if DEBUG_SISTEMA
        assert(sis != NULL);
    #else
        if (sis == NULL);
    #endif

    if (strcmp("USUARIOS", banco) == 0) {
        printf("----- BANCO DE USUARIOS -----\n");
        imprimeBanco(sis->usuarios);
        printf("----------------------------\n\n");
    } else if (strcmp("TECNICOS", banco) == 0) {
        printf("----- BANCO DE TECNICOS -----\n");
        imprimeBanco(sis->tecnicos);
        printf("----------------------------\n\n");
    } else {
        #if DEBUG_SISTEMA
            printf("[ERRO] - Na funcao imprimeBancoSistema.\n\tTipo nao identificado (%s).\n", banco);
            exit(1);
        #else
            return;
        #endif
    }
}

void notificaTicketsSistema(Sistema* sis) {
    #if DEBUG_SISTEMA
        assert(sis != NULL);
    #else
        if (sis == NULL)
            return;
    #endif

    printf("----- FILA DE TICKETS -----\n");
    notificaFila(sis->tickets);
    printf("---------------------------\n\n");
}

void imprimeRankingSistema(Sistema* sis, char* tipo) {
    #if DEBUG_SISTEMA
        assert(sis != NULL);
    #else
        if (sis == NULL)
            return;
    #endif
    
    Banco* b = NULL;

    if (strcmp("USUARIOS", tipo) == 0) {
        b = copiaBanco(sis->usuarios);
    } else if (strcmp("TECNICOS", tipo) == 0) {
        b = copiaBanco(sis->tecnicos);
    } else {
        #if DEBUG_SISTEMA
            printf("[ERRO] - na funcao imprimeRankingSistema.\n\tTipo nao identificado (%s).\n", tipo);
        #else
            return;
        #endif
    }

    ordenaBanco(b);
    printf("----- RANKING DE %s -----\n", tipo);
    imprimeBanco(b);
    printf("-------------------------------\n\n");

    desalocaCopiaBanco(b);
}

void imprimeRelatorioSistema(Sistema* sis) {
    #if DEBUG_SISTEMA
        assert(sis != NULL);
    #else
        if (sis == NULL)
            return;
    #endif

    int mediaIdadeUsuarios = 0;
    int mediaIdadeTecnicos = 0;
    int mediaTrabalhoTecnicos = 0;

    int qtdUsuarios = getTamanhoBanco(sis->usuarios);
    
    int somaIdades = 0;
    for (int i = 0; i < qtdUsuarios; i++) {
        somaIdades += getIdadeAtor(getAtorBanco(sis->usuarios, i), sis->dataAtual);
    }

    mediaIdadeUsuarios = somaIdades/qtdUsuarios;

    somaIdades = 0;
    int somaTrabalhos = 0;
    int qtdTecnicos = getTamanhoBanco(sis->tecnicos);

    for (int i = 0; i < qtdTecnicos; i++) {
        Ator* a = getAtorBanco(sis->tecnicos, i);
        somaIdades += getIdadeAtor(a, sis->dataAtual);
        somaTrabalhos += getTempoTrabalhadoTecnico(getDadoAtor(a));
    }
    mediaIdadeTecnicos = somaIdades/qtdTecnicos;
    mediaTrabalhoTecnicos = somaTrabalhos/qtdTecnicos;



    printf("----- RELATORIO GERAL -----\n");
    printf("- Qtd tickets: %d\n", getQtdTicketsNaFila(sis->tickets));
    printf("- Qtd tickets (A): %d\n", getQtdTicketsPorStatusNaFila(sis->tickets, 'A'));
    printf("- Qtd tickets (F): %d\n", getQtdTicketsPorStatusNaFila(sis->tickets, 'F'));
    printf("- Qtd usuarios: %d\n", getTamanhoBanco(sis->usuarios));
    printf("- Md idade usuarios: %d\n", mediaIdadeUsuarios);
    printf("- Qtd tecnicos: %d\n", getTamanhoBanco(sis->tecnicos));
    printf("- Md idade tecnicos: %d\n", mediaIdadeTecnicos);
    printf("- Md trabalho tecnicos: %d\n", mediaTrabalhoTecnicos);
    printf("---------------------------\n\n");
}