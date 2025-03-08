#ifndef _ATOR_H
#define _ATOR_H

#include "data.h"

#define MAX_TAM_NOME        100
#define MAX_TAM_CPF         15
#define MAX_TAM_TELEFONE    16
#define MAX_TAM_GENERO      10

/**
 * Estrutura de um ator contendo todos os atributos comuns entre os tipos de atores e um tipo generico (usuario ou tecnico).
 */
typedef struct Ator Ator;

/**
 * @brief Função de callback para desalocar um ator.
 * @param dado Ponteiro para o ator a ser desalocado. 
 */
typedef void (*fptr_desalocaAtor)(void* dado);

/**
 * @brief Função de callback ppara imprimir um ator.
 * @param dado Ponteiro para o ator a ser impresso.
 */
typedef void (*fptr_imprimeAtor)(void* dado);

/**
 * @brief Função de callback que retorna um atributo especifico do ator
 * @param dado Ponteiro para o ator;
 * @return Um ponteiro para o atributo desejado.
 */
typedef void* (*fptr_getAtributoAtor)(void* dado);

/**
 * @brief Aloca e inicializa os parametros de um tipo Ator de acordo com os dados passados.
 * @param nome Nome do ator.
 * @param cpf CPF do ator.
 * @param dataNascimento Data de nascimento do ator.
 * @param telefone Numero de telefone do ator.
 * @param genero Genero do ator.
 * @param dado Ponteiro para a estrutura com os dados especificos do ator deste tipo (usuario ou tecnico).
 * @param desaloca Função de callback que desaloca um ator deste tipo especifico.
 * @param imprime Função de calback que imprime os dados de um ator dese tipo.
 * @return Um ponteiro para uma estrutura do tipo Ator alocada dinamicamente e com os parametros inicializados.
 */
Ator* criaAtor(char* nome, char* cpf, Data* dataNascimento, char* telefone, char* genero, void* dado, fptr_desalocaAtor desaloca, fptr_imprimeAtor imprime);

/**
 * @brief Função que desaloca um Ator.
 * @param a Ator a ser desalocado.
 */
void desalocaAtor(Ator* a);

/**
 * @brief Função que imprime um Ator.
 * @param a o Ator a ser impresso.
 */
void imprimeAtor(Ator* a);

/**
 * @brief Função que retorna a idade de um ator.
 * @param a O ator a ter sua idade retornada.
 * @param dataAtual Data a ser usada como referencia para calcular a idade do ator.
 * @return A idade do ator em anos.
 */
int getIdadeAtor(Ator* a, Data* dataAtual);

/**
 * @brief Função que retorna o cpf de um ator.
 * @param a O ator.
 * @return A string contendo o cpf do ator.
 */
char* getCPFAtor(Ator* a);

/**
 * @brief retorna o noeme de um ator.
 * @param a O ator.
 * @return A string contendo o nome do ator.
 */
char* getNomeAtor(Ator* a);

/**
 * @brief Função que retorna um atributo especifico do ator (de acordo com a função callback passada).
 * @param a O ator a ter seu atributo especifico retornado.
 * @param getAtributo Função que retorna o atributo desejado.
 * ATENÇÃO: É de responsabilidade do usuario passar como argumento uma função compatível com o tipo do ator.
 * @return Um ponteiro para o atributo desejado
 */
void* getAtributoEspecificoAtor(Ator* a, fptr_getAtributoAtor getAtributo);

/**
 * @brief Retorna o ponteiro com os dados especificos de um Ator.
 * @param a O ator a ter seus dados retornados.
 * @return Um ponteiro para os dados do ator.
 */
void* getDadoAtor(Ator* a);

#endif