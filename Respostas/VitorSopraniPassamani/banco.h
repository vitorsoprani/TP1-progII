#ifndef _BANCO_H
#define _BANCO_H

#include "ator.h"

/**
 * @brief Função que compara os dados de 2 atores de um mesmo banco.
 * @param dado1 O ponteiro para os dados do primeiro ator.
 * @param dado2 O ponteiro para os dados do segundo ator.
 * @return Um numero positivo se o primeiro ator deve vir depois que o segundo, um numero negativo se o primeiro ator deve vir depois que o segundo e 0 se os dois atores estão "empatados".
 */
typedef int (*fptr_comparaDados)(void* dado1, void* dado2);

/**
 * Estrutura do tipo banco contendo um array de Atores e informações auxiliares.
 */
typedef struct Banco Banco;

/**
 * @brief função que aloca e inicializa os valores em um banco.
 * @param compara a função que sera usada para comparar os dados desse banco.
 * @return um banco inicializado.
 */
Banco* criaBanco(fptr_comparaDados compara);

/**
 * @brief Função que desaloca um banco junto com todos os seus dados.
 * @param b O banco a ser desalocado.
 */
void desalocaBanco(Banco* b);

/**
 * @brief Imprime o banco.
 * @param b O banco a ser impresso.
 */
void imprimeBanco(Banco* b);

/**
 * @brief Função que retorna o ator presente em um dado indice do banco.
 * @param b O banco que será acessado.
 * @param idx O indice do Ator que sera retornado.
 */
Ator* getAtorBanco(Banco* b, int idx);

/**
 * @brief Função que insere um novo ator no banco fazendo o gerenciamento necessario da memeoria.
 * @param b O banco a ser modificado.
 * @param a o Ator que será inserido.
 */
void insereAtorBanco(Banco* b, Ator* a);

/**
 * @brief função que retorna o tamanho de um banco.
 * @param b o banco a ser analizado.
 * @return O tamanho (quantidade de elementos) do banco.
 */
int getTamanhoBanco(Banco* b);

/**
 * @brief Função que ordena um banco de acordo com sua função callback de comparação.
 * @param b O banco a ser ordenado.
 */
void ordenaBanco(Banco* b);

/**
 * @brief Função que cria uma copia de um banco.
 * @param destino Estrutura do tipo banco que receberá a cópia.
 * @param origem Estrutura original que será copiada.
 */
void copiaBanco(Banco* destino, Banco* origem);

/**
 * @brief Função que compara dois atores pertencentes a um banco de acordo com sua função de callback.
 * @param b O banco ao qual os atores pertencem.
 * @param idx1 O idx do primeiro ator a ser comparado.
 * @param idx2 O idx do segundo ator a ser comparado.
 * @return Um numero positivo se o primeiro ator deve vir depois que o segundo, Um numero negativo se o primeiro ator deve vir primeiro que  segundo, O se os atores estão "empatados";
 */
int comparaAtoresBanco(Banco* b, int idx1, int idx2);

#endif