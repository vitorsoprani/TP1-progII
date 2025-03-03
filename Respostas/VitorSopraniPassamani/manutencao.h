#ifndef _MANUTENCAO_H
#define _MANUTENCAO_H

#define MAX_TAM_ITEM    100
#define MAX_TAM_ESTADO  10
#define MAX_TAM_LOCAL   100


/**
 * Estrutura de um ticket manutenção contendo parametros epecíficos de um ticket do tipo MANUTENÇÃO
 */
typedef struct Manutencao Manutencao;

/**
 * @brief Aloca uma estrutura MANUTENCAO na memoria e inicializa os parametros necessarios.
 * @param item Nome do item que necessita de manutenção;
 * @param estado O estado de conservação do item (RUIM, REGULAR ou BOM);
 * @param local Local exato do item.
 * @return Um ponteiro para uma estrutura do tipo MANUTENCAO incializada.
 */
Manutencao* criaManutencao(char* item, char* estado, char* local);

/**
 * @brief Le da entrada padrao uma estrutura do tipo manutencao.
 * @return Uma estrutura do tipo manutencao.
 */
Manutencao* lerManutencao();


/**
 * @brief Calcula o tempo estimado para resolver um ticket do tipo manutencao;
 * Tempo estimado depende do estado de conservação do item e do setor do usuario solicitante.
 * @param m A manutenção que tera o tempo estimado;
 * @param setor O setor do usuario solicitante.
 */
void setTempoEstimadoManutencao(Manutencao* m, char* setor);

/**
 * @brief Retorna o tempo estimado para resolver o ticket de manutencao;
 * @param dado Ticket do tipo manutencao
 * @return Tempo estimado para resolver a manutencao;
 */
int getTempoEstimadoManutencao(void* dado);

/**
 * @brief Retorna o tipo do ticket;
 * @return 'M' para manutencao.
 */
char getTipoManutencao();

/**
 * @brief Desaloca um ticket do tipo manutencao;
 * @param dado Ticket do tipo manutencao.
 */
void desalocaManutencao(void* dado);

/**
 * @brief Impime um ticket do tipo manutencao;
 * @param dado Ticket do tipo manutencao.
 */
void notificaManutencao(void* dado);

#endif