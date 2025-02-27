

#ifndef _TICKET_H
#define _TICKET_H

#define MAX_TAM_ID 11
#define MAX_TAM_CPF 15

/**
 * Estrutura de um Ticket contendo os parametros comuns entre todos os tipos de Tickets e um tipo genérico.
 */
typedef struct Ticket Ticket;

/**
 * @brief Função de callback para notificar (imprimir) um ticket
 * @param dado um tipo genérico para representar os tipos de tickets.
 */
typedef void (*func_ptr_notifica)(void *dado);

/**
 * @brief Função de callback para desalocar da memória uma implementação especifica de  ticket
 * @param dado um tipo genérico para representar os tipos de tickets.
 */
typedef void (*func_ptr_desaloca)(void *dado);
/**
 * Função de callback para retornar o tempo estimado para resolver um ticket
 * @param dado um tipo genérico para representar os tipos de tickets.
 * @return tempo estimado para resolver um ticket
 *
 *  */
typedef int (*func_ptr_tempoEstimado)(void *dado);

/**
 * Função de callback para retornar o tipo de um ticket
 * @param dado um tipo genérico para representar os tipos de tickets.
 * @return tipo do Ticket
 */
typedef char (*func_ptr_tipo)();

/**
 * @brief Aloca uma estrutura Ticket na memória e inicializa os parâmetro necessários
 * @param cpfSol CPF de quem está solicitando a abertura do ticket
 * @param dado   Um ticket genérico  (considerando que existe mais de um tipo de ticket)
 * @param getTempo  Função de callback que retorna o tempo para aquele ticket ser resolvido
 * @param getTipo   Função de callback que retorna o tipo do ticket ser resolvido
 * @param notifica  Função de callback de notificação  (impressãode um ticket
 * @param desaloca  Função de callback que irá desalocar  um ticket da memória
 * @return  Uma estrutura Ticket inicializada.
 */
Ticket *criaTicket(char *cpfSol, void *dado, func_ptr_tempoEstimado getTempo,
                   func_ptr_tipo getTipo, func_ptr_notifica notifica, func_ptr_desaloca desaloca);

/**
 * @brief Atribui um ID a um ticket
 * @param d Ticket inicializado
 * @param id ID a ser atribuido ao ticket
 */
void setIDTicket(Ticket *d, char *id);

/**
 * @brief Finaliza um ticket
 * @param t Ticket inicializado
 */
void finalizaTicket(Ticket *t);

/**
 * @brief Recupera o CPF de quem solicitou a abertura do ticket
 * @param t Ticket inicializado
 * @return CPF de quem solicitou a abertura do ticket
 */
char *getCPFSolicitanteTicket(Ticket *t);

/**
 * @brief Recupera o tempo estimado para resolver um ticket
 * @param t Ticket inicializado
 * @return tempo estimado para resolver um ticket
 */
int getTempoEstimadoTicket(Ticket *t);

/**
 * @brief Recupera o tipo de um ticket
 * @param t Ticket inicializado
 * @return tipo do Ticket
 */
char getTipoTicket(Ticket *t);

/**
 * @brief Recupera o status de um ticket
 * @param t Ticket inicializado
 * @return status do Ticket
 */
char getStatusTicket(Ticket *t);

/**
 * @brief  Desaloca um ticket da memória
 * @param doc estrutura do tipo Ticket que deve ser liberada da memória
 */
void desalocaTicket(Ticket *doc);

/**
 * @brief  Notifica (imprime) um ticket
 * @param doc Ticket a ser notificado
 */
void notificaTicket(Ticket *doc);

#endif