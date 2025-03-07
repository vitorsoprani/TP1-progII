#ifndef _SISTEMA_H
#define _SISTEMA_H

#include "data.h"

//  BIBLIOTECAS QUE TRABALHAM COM TICKETS:
#include "software.h"
#include "manutencao.h"
#include "outros.h"
#include "ticket.h"
#include "fila.h"

//  BIBLIOTECAS QUE TRABALHAM COM ATORES:
#include "tecnico.h"
#include "usuario.h"
#include "ator.h"
#include "banco.h"

#define MAX_TAM_TIPO_TICKET 15

/**
 * Estrutura que armazena todas do sistema.
 */
typedef struct Sistema Sistema;

/**
 * @brief Funcao que aloca e inicializa os atributos do sistema.
 * @param dataAtual A data que será usada como referencia pelo sistema.
 * @return Uma estrutura do tipo Sistema inicializada.
 */
Sistema* criaSistema(Data* dataAtual);

/**
 * @brief Função que desaloca uma variável do tipo sistema.
 * @param sis O sistema a ser desalocado.
 */
void desalocaSistema(Sistema* sis);

/**
 * @brief Função que lê e insere um ticket qualquer no sistema;
 * @param sis O sistema.
*/
void insereTicketSistema(Sistema* sis);

/**
 * @brief Função que Le e insere um novo ator no sistema.
 * @param sis O sistema.
 * @param tipo Tipo do ator.
 */
void insereAtorSistema(Sistema* sis, char* tipo);

/**
 * @brief Função que distribui os tickets para os tecnicos.
 * @param sis O sistema que terá os tickets distribuidos.
 */
void distribuiTicketsSistema(Sistema* sis);

/**
 * @brief Função que verifica se um ticket é compativel com um ator, em outras palavras: se o tecnico pode receber o ticket.
 * @param tic o ticket.
 * @param tec tecnico.
 * @return 1 se é posível atribuir o ticket ao técnico e 0 caso contrario.
 */
int ehCompativelTicketTecnicoSistema(Ticket* tic, Tecnico* tec);

/**
 * @brief função que imprime um dado banco no sistema.
 * @param sis O sistema.
 * @param banco String contendo o banco a ser impresso
 */
void imprimeBancoSistema(Sistema* sis, char* banco);

/**
 * @brief Função que imprime a lista de tickets presentes no sistema.
 * @param sis O sistema a ter seus tickets impressos.
 */
void notificaTicketsSistema(Sistema* sis);

/**
 * @brief Função que imprime um ranking do sistema.
 * @param sis O sistema que terá o ranking impresso.
 * @param tipo O tipo de ator que terá o ranking impresso ("TECNICO" ou "USUARIO").
 */
void imprimeRankingSistema(Sistema* sis, char* tipo);

/**
 * @brief Função que imprime o relatório geral de um sistema.
 * @param sis O sistema.
 */
void imprimeRelatorioSistema(Sistema* sis);
#endif