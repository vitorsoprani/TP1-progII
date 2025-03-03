#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "tecnico.h"
#include "utils.h"

#define DEBUG_TECNICO 1

struct Tecnico {
    char* area;
    
    float salario;
    int disponibilidade;
    int tempoTrabalhado;
};

Tecnico* criaTecnico(char* area, float salario, int disponibilidade) {
    Tecnico* t = (Tecnico*)malloc(sizeof(Tecnico));

    #if DEBUG_TECNICO
        assert(t != NULL);
    #else
        if (t == NULL)
            return NULL;
    #endif

    //  Alocando a memoria necessaria para as strings:
    t->area = (char*)malloc(sizeof(char) * (strlen(area) + 1));

    #if DEBUG_TECNICO
        assert(t->area != NULL);
    #else
        if (t->area == NULL)
            return NULL;
    #endif

    strcpy(t->area, area);

    t->salario = salario;
    t->disponibilidade = disponibilidade;
    t->tempoTrabalhado = 0;

    return t;
}

Tecnico* lerTecnico() {
    char area[MAX_TAM_AREA];
    int disponibilidade;
    float salario;

    scanf("%[^\n]", area);
    CleanBuffer();
    scanf("%d", &disponibilidade);
    CleanBuffer();
    scanf("%f", &salario);
    CleanBuffer();

    return criaTecnico(area, salario, disponibilidade);
}

int atribuiTrabalhoTecnico(Tecnico* t, int tempoTrabalho) {
    #if DEBUG_TECNICO
        assert(t != NULL);
        assert(tempoTrabalho > 0);
    #else
        if (t == NULL || tempoTrabalho <= 0)
            return 0;
    #endif

    if (getDisponibilidadeAtualTecnico(t) <= tempoTrabalho) {
        t->disponibilidade -= tempoTrabalho;
        t->tempoTrabalhado += tempoTrabalho;
        return 1;
    }

    return 0;
}

int getDisponibilidadeAtualTecnico(Tecnico* t) {
    #if DEBUG_TECNICO
        assert(t != NULL);
    #else
        if (t == NULL)
            return 0;
    #endif

    return t->disponibilidade;
}

int getTempoTrabalhadoTecnico(Tecnico* t) {
    #if DEBUG_TECNICO
        assert(t != NULL);
    #else
        if (t == NULL)
            return 0;
    #endif

    return t->tempoTrabalhado;
}

char* getAreaTecnico(Tecnico* t) {
    #if DEBUG_TECNICO
        assert(t != NULL);
    #else
        if (t == NULL)
            return "";
    #endif

    return t->area;
}

void desalocaTecnico(void* dado) {
    if (dado != NULL) {
        free(CAST(Tecnico, dado)->area);

        free(dado);
    }
}

void imprimeTecnico(void* dado) {
    #if DEBUG_TECNICO
        assert(dado != NULL);
    #else
        if (dado == NULL)
            return;
    #endif

    printf("- Area de Atuacao: %s\n", CAST(Tecnico, dado)->area);
    printf("- Salario: %.2f\n", CAST(Tecnico, dado)->salario);
    printf("- Disponibilidade: %dh\n", CAST(Tecnico, dado)->disponibilidade);
    printf("- Tempo Trabalhado: %dh\n", CAST(Tecnico, dado)->tempoTrabalhado);
}