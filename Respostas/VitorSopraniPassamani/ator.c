#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ator.h"

#define DEBUG_ATOR 1

struct Ator {
    void* dado;

    char* nome;
    char* cpf;
    Data* dataNascimento;
    char* telefone;
    char* genero;

    fptr_desalocaAtor desaloca;
    fptr_imprimeAtor imprime;
};

Ator* criaAtor(char* nome, char* cpf, Data* dataNascimento, char* telefone, char* genero, void* dado, fptr_desalocaAtor desaloca, fptr_imprimeAtor imprime) {
    #if DEBUG_ATOR
        assert(dataNascimento != NULL);
        assert(dado != NULL);
    #else
        if (dataNascimento = NULL || dado == NULL)
            return NULL;
    #endif

    Ator* a = (Ator*)malloc(sizeof(Ator));

    #if DEBUG_ATOR
        assert(a != NULL);
    #else
        if (a == NULL)
            return NULL;
    #endif

    //  Alocando as strings com o taanho necessario:
    a->nome = (char*)malloc(sizeof(char) * (strlen(nome) + 1));
    a->cpf = (char*)malloc(sizeof(char) * (strlen(cpf) + 1));
    a->telefone = (char*)malloc(sizeof(char) * (strlen(telefone) + 1));
    a->genero = (char*)malloc(sizeof(char) * (strlen(genero) + 1));

    #if DEBUG_ATOR
        assert(a->nome != NULL);
        assert(a->cpf != NULL);
        assert(a->telefone != NULL);
        assert(a->genero != NULL);
    #else
        if (a->nome == NULL || a->cpf == NULL || a->telefone == NULL || a->genero == NULL)
            return NULL;
    #endif

    //  Atribuindo os valores:
    strcpy(a->nome, nome);
    strcpy(a->cpf, cpf);    
    strcpy(a->telefone, telefone);
    strcpy(a->genero, genero);
    
    a->dado = dado;
    a->dataNascimento = dataNascimento;
    a->desaloca = desaloca;
    a->imprime = imprime;

    return a;
}

void desalocaAtor(Ator* a) {
    if ( a != NULL) {
        free(a->nome);
        free(a->cpf);
        free(a->telefone);
        free(a->genero);

        desalocaData(a->dataNascimento);

        a->desaloca(a->dado);

        free(a);
    }
}

void imprimeAtor(Ator* a) {
    #if DEBUG_ATOR
        assert(a != NULL);
    #else
        if (a == NULL)
            return;
    #endif

    printf("- Nome: %s\n", a->nome);
    printf("- CPF: %s\n", a->cpf);
    printf("- Data de Nascimento: ");
    imprimeData(a->dataNascimento);
    printf("- Telefone: %s\n", a->telefone);
    printf("- Genero: %s\n", a->genero);

    a->imprime(a->dado);
}

int getIdadeAtor(Ator* a, Data* dataAtual) {
    #if DEBUG_ATOR
        assert(a != NULL);
        assert(dataAtual != NULL);
    #else
        if (a == NULL || dataAtual == NULL)
            return 0;
    #endif

    return calculaDiferencaAnosData(a->dataNascimento, dataAtual);
}

void* getAtributoEspecificoAtor(Ator* a, fptr_getAtributoAtor getAtributo) {
    #if DEBUG_ATOR
        assert(a != NULL);
    #else
        if (a == NULL)
            return NULL;
    #endif

    return getAtributo(a->dado);
}

void* getDadoAtor(Ator* a) {
    #if DEBUG_ATOR
        assert(a != NULL);
    #else
        if (a == NULL)
            return NULL
    #endif

    return a->dado;
}