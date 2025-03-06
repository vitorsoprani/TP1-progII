#ifndef _DATA_H
#define _DATA_H

/**
 * Estrutura que armazenara uma data (dia/mes/ano).
 */
typedef struct Data Data;

/**
 * @brief Função que aloca e incializa os parametors de um objeto do tipo data.
 * @param dia Dia;
 * @param mes Mes;
 * @param ano Ano;
 * @return O objeto do tipo Data com as variáveis inicializadas.
 */
Data* criaData(int dia, int mes, int ano);

/**
 * @brief Le da entrada padrão os dados para inicializar um objeto do tipo Data.
 * @return Um objeto do tipo Data inicializado.
 */
Data* lerData();

/**
 * @brief Imprime um objedo do tipo data de forma formatada (dd/mm/aa).
 * @param d A data a ser impressa.
 */
void imprimeData(Data* d);

/**
 * @brief Retorna a diferença em anos entre as dadas d1 (inicio) e a data d2(fim).
 * @param d1 Primeira data (inicio).
 * @param d2 Segunda data (fim).
 * @return A diferença em anos entre as duas datas.
 */
int calculaDiferencaAnosData(Data* d1, Data* d2);

/**
 * @brief Desaloca uma estrutura do tipo data;
 * @param d A data a ser desalocada.
 */
void desalocaData(Data* d);

#endif