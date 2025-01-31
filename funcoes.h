#define _CRT_SECURE_NO_WARNINGS

#ifndef FUNCOES_H
#define FUNCOES_H

#include "global.h"

// Funcoes para manipulacao dos dados dos trabalhos
void inserir_dados(Trabalho** trabalhos, int* num_trabalhos, int* num_maquinas);
void listar_trabalhos(Trabalho* trabalhos, int num_trabalhos);
void alterar_dados(Trabalho* trabalhos, int num_trabalhos);
void calcular_tempos(Trabalho* trabalhos, int num_trabalhos);
void exportar_dados(Trabalho* trabalhos, int num_trabalhos, int num_maquinas, char* filename);
void exportar_dados_inicio(Trabalho* trabalhos, int num_trabalhos, int num_maquinas, char* filename);
void importar_dados(Trabalho** trabalhos, int* num_trabalhos, int* num_maquinas);
void liberar_memoria(Trabalho* trabalhos, int num_trabalhos);

#endif // FUNCOES_H