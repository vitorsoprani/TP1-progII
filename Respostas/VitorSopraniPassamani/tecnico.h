#ifndef _TECNICO_H
#define _TECNICO_H

#define MAX_TAM_AREA 10
/**
 * Estrutura de um ator do tipo TECNICO contendo os parametros especificos.
 */
typedef struct Tecnico Tecnico;

/**
 * @brief Aloca uma estrutura do tipo Tecnico na memoria e inicializa os parametros necessarios.
 * @param area Area de atuação co tecnico (string "GERAL" ou "TI");
 * @param salario Salario do tecnico;
 * @param disponibilidade Valor inteiro indicando quantas horas o tecnico tem disponível para trabalhar (inicialmente);
 * @return Uma estrutura Tecnico inicializada.
 */
Tecnico* criaTecnico(char* area, float salario, int disponibilidade);

/**
 * @brief Le da entrada padrao um ator do tipo Tecnico;
 * @return Um ator do tipo tecnico;
 */
Tecnico* lerTecnico();

/**
 * @brief Caso tecnico tenha tempo disponivel, incrementa o tempo trabalhado no valor indicado.
 * Caso o tecnico NÃO consiga realizar o trbalho, o mesmo segue inalterado após a chamada da função.
 * @param t Tecnico que "tentará" realizar o trabalho;
 * @param tempoTrabalho Tempo que levará para realizar o trabalho em questão;
 * @return 1 caso o tecnico consiga realizar o trabalho e 0 caso contrario.
 */
int atribuiTrabalhoTecnico(Tecnico* t, int tempoTrabalho);

/**
 * @brief Retorna quanto tempo o técnico ainda tem disponível para trabalha.
 * @param t O técnico em questão;
 * @return quantas horas o tecnico ainda tem disponivel.
 */
int getDisponibilidadeAtualTecnico(Tecnico* t);

/**
 * @brief Retorna o tempo de trabalho acumulado pelo tecnico.
 * @param t O tecnico em questão;
 * @return O tempo de trabalho acumulado pelo tecnico.
 */
int getTempoTrabalhadoTecnico(Tecnico* t);

/**
 * @brief Retorna a área de atuação do tecnico;
 * @param t O tencio em questão;
 * @return "GERAL" ou "TI"
 */
char* getAreaTecnico(Tecnico* t);

/**
 * @brief Desaloca um ator do tipo Tecnico.
 * @param dado Um ator do tipo tecnico.
 */
void desalocaTecnico(void* dado);

/**
 * @brief Imprime as informações do tecnico na saída padrao;
 * @param dado O ator do tipo Tecnico a ser impresso.
 */
void imprimeTecnico(void* dado);

#endif