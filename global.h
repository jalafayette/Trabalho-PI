#define _CRT_SECURE_NO_WARNINGS
#ifndef GLOBAL_H
#define GLOBAL_H

/**
 * @struct Operacao
 * @brief Representa uma operacao num trabalho.
 *
 * Contem informacoes sobre a maquina onde a operacao sera realizada,
 * a sua duracao e o instante de inicio.
 */
typedef struct 
{
    int maquina; //Maquina onde a operacao sera realizada.
        int duracao; //Duracao da operacao. 
        int inicio; //Tempo de inicio da operacao. 
} Operacao;

/**
 * @struct Trabalho
 * @brief Representa um trabalho composto por varias operacoes.
 *
 * Um trabalho contem um conjunto de operacoes realizadas em sequencia.
 */
typedef struct 
{
    Operacao* operacoes; //Array de operacoes do trabalho.
        int num_operacoes; //Numero de operacoes no trabalho.
} Trabalho;

#endif // GLOBAL_H
