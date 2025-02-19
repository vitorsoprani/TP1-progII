

#ifndef _SOFTWARE_H
#define _SOFTWARE_H

#define MAX_TAM_NOME_SOFTWARE 100
#define MAX_TAM_CAT 25
#define MAX_TAM_MOTIVO 200

#define TEMPO_ESTIMADO_BUG 3
#define TEMPO_ESTIMADO_OUTROS 2
#define TEMPO_ESTIMADO_DUVIDA 1

/**
 * Estrutura de um Ticket Software contendo os parametros especificos de um ticket do tipo SOFTWARE
 */
typedef struct Software Software;

/**
 * @brief Aloca uma estrutura Software na memória e inicializa os parâmetro necessários
 * @param nome Nome do software
 * @param categoria Categoria do software
 * @param impacto Impacto do chamado
 * @param motivo Motivo da abertura do ticket
 * @return  Uma estrutura Software inicializada.
 */
Software *criaSoftware(char *nome, char *categoria, int impacto, char *motivo);

/**
 * @brief Lê da entrada padrão um  ticket do TIPO software
 * @return  Um chamado do Tipo Software
 */
Software *lerSoftware();

/**
 * @brief  Calcula o tempo estimado para resolver um ticket do tipo Software.
 * Tempo estimado depende da categoria e impacto
 * @param s  Ticket do tipo Software
 */
void setTempoEstimadoSoftware(Software *s);

/**
 * @brief  Retorna o tempo estimado para resolver um ticket do tipo Software.
 * @param dado  Ticket do tipo Software
 * @return  Tempo estimado para resolver um ticket do tipo Software
 */
int getTempoEstimadoSoftware(void *dado);

/**
 * @brief  Retorna o tipo do ticket
 * @return  'S' para Software
 */
char getTipoSoftware();

/**
 * @brief  Desaloca um ticket do tipo Software da memória
 * @param s  Ticket do tipo Software
 */
void desalocaSoftware(void *s);

/**
 * @brief  Imprime um ticket do tipo Software
 * @param dado  Ticket do tipo Software
 */
void notificaSoftware(void *dado);

#endif