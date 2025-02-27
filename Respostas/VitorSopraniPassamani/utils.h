#ifndef _utils
#define _utils

//Faz o casting de um ponteiro qualquer 'b' para um ponteiro do tipo 'a'.
#define CAST(a, b) ((a*)b)

//Limpa o buffer de entrada até encontrar um \n (removendo, tambem, o \n).
void CleanBuffer();

#endif