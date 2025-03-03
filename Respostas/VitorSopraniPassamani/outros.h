#ifndef _OUTROS_H
#define _OUTROS_H

#define MAX_TAM_DESCRICAO   500
#define MAX_TAM_LOCAL   100

/**
 * Estrutura de um ticket outros contendo parametros epecíficos de um ticket do tipo OUTROS
 */
typedef struct Outros Outros;

/**
 * @brief Aloca uma estrutura OUTROS na memoria e inicializa os parametros necessarios.
 * @param descricao Descrição do problema a ser resolvido.
 * @param local Local onde o problema ocorreu.
 * @param dificuldade Nivel de dificuldade que o usuario julgou que o problema tem.
 * @return Um ponteiro para uma estrutura do tipo OUTROS incializada.
 */
Outros* criaOutros(char* descricao, char* local, int dificuldade);

/**
 * @brief Le da entrada padrao uma estrutura do tipo outros.
 * @return Uma estrutura do tipo outros.
 */
Outros* lerOutros();


/**
 * @brief Calcula o tempo estimado para resolver um ticket do tipo outros;
 * Tempo estimado depende do nivel de dificuldade estimado pelo usuario.
 * @param m O que tera o tempo estimado;
 * @param setor O setor do usuario solicitante.
 */
void setTempoEstimadoOutros(Outros* o);

/**
 * @brief Retorna o tempo estimado para resolver o ticket de manutencao;
 * @param dado Ticket do tipo manutencao
 * @return Tempo estimado para resolver a manutencao;
 */
int getTempoEstimadoOutros(void* dado);

/**
 * @brief Retorna o tipo do ticket;
 * @return 'O' para manutencao.
 */
char getTipoOutros();

/**
 * @brief Desaloca um ticket do tipo outros;
 * @param dado Ticket do tipo outros.
 */
void desalocaOutros(void* dado);

/**
 * @brief Impime um ticket do tipo outros;
 * @param dado Ticket do tipo outros.
 */
void notificaOutros(void* dado);

#endif