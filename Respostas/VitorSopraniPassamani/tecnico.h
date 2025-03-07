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
 * @brief Altera o tempo trabalhado e a disponibilidade no valor indicado.
 * @param t Tecnico que "tentará" realizar o trabalho;
 * @param tempoTrabalho Tempo que levará para realizar o trabalho em questão;
 */
void atribuiTrabalhoTecnico(Tecnico* t, int tempoTrabalho);

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

/**
 * @brief Comprara os dados de 2 tecnicos.
 * @param dado1 O prmeiro tecnico da comparação.
 * @param dado2 O segund tecnico da comparação.
 * @return Um numero positivo se o primeiro tecnico deve vir depois que o segundo, Um numero negativo se o primeiro tecnico deve vir antes do segundo, 0 se os dois tecnicos estão "empatados".
 */
int comparaTecnicos(void* dado1, void* dado2);

#endif