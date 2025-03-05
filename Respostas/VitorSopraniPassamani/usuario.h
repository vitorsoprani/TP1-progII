#ifndef _USUARIO_H
#define _USUARIO_H

#define MAX_TAM_SETOR 15

/**
 * Estrutura de um ator do tipo USUARIO que armazena seus atributos especificos.
 */
typedef struct Usuario Usuario;

/**
 * @brief Aloca uma estrutura do tipo Usuario inicializando os atributos necessarios.
 * @param setor Uma string contendo o setor no qual o usuario trabalha;
 * @return Um ponteiro para uma estrutura do tipo USUARIO alocada e inicializada.
 */
Usuario* criaUsuario(char* setor);

/**
 * @brief Le na entrada padrão os dados necessários para criar um struct do tipo Usuario.
 * @return Um ponteiro para uma estrutura do tipo USUARIO alocada e inicializada.
 */
Usuario* lerUsuario();

/**
 * @brief Incrementa em 1 o valor da quantidade de tickets solicitados pelo usuairo.
 * @param u O usuario que tera seu valor de tickets solicitados atualizado.
 */
void incrementaTicketsUsuario(Usuario* u);

/**
 * @brief Retorna o numero de tickets solicitado pelo usuario.
 * @param u O usuario em questão
 */
int getTicketsUsuario(Usuario* u);

/**
 * @brief Desaloca um struct do tipo USUARIO.
 * @param dado O usuario a ser desalocado.
 */
void desalocaUsuario(void* dado);

/**
 * @brief Imprime os dados especificos de um tipo USUARIO.
 * @param dado Ponteiro para o usuario em questão.
 */
void imprimeUsuario(void* dado);

#endif