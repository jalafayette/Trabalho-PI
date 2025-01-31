/******************************************************************************
                                   IPCA

Trabalho realizado por:

    Afonso Lopes n� 33226
    Carlos Lopes n� 22848
    Joao Lafayette n� 31587
    Matheus Motta n� 33227

    Curso:           Engenharia Eletrotecnica e Computadores (EEC)
    Disciplina:      Programacao Imperativa
    Ano Letivo:      2024/2025
******************************************************************************/

/**
 * @mainpage
 *
 * @brief
 * Este programa foi desenvolvido como parte do trabalho pratico da disciplina Programacao Imperativa.
 * Implementa um sistema de gestao de trabalhos industriais, permitindo a insercao de dados, consulta de dados, alteracao de dados, calculo de tempos, exportacao e
 * importacao de dados associados ao problema de Job-Shop.
 *
 * @section intro_sec Introducao
 *
 * O problema de Job-Shop envolve a gestao de recursos (maquinas) para executar operacoes em trabalhos seguindo restricoes especificas:
 * - Cada trabalho possui uma sequencia de operacoes que devem ser realizadas numa ordem especifica. 
 * - Cada maquina so pode executar uma operacao de cada vez.
 *
 * @section details_sec Detalhes
 *
 * Este sistema foi desenvolvido para otimizar a alocacao de recursos num ambiente industrial. Atraves de uma interface, o usuario pode interagir com o sistema para:
 * - Inserir novos trabalhos e suas operacoes,
 * - Consultar o estado atual dos trabalhos e das maquinas,
 * - Alterar as operacoes ou caracteristicas dos trabalhos,
 * - Calcular os tempos necessarios para a execucao de todos os trabalhos considerando as maquinas e restricoes,
 * - Exportar e importar dados relacionados a estes trabalhos.
 *
 * @author
 * | Afonso Lopes n 33226
 * | Carlos Lopes n 22848
 * | Joao Lafayette n 31587
 * | Matheus Motta n 33223
 * @date 12-2024
 */


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#include "global.h"


 /**
  * @brief Insere dados de trabalhos e de operacoes.
  *
  * Permite ao utilizador especificar o numero de trabalhos e de maquinas, bem como
  * as operacoes associadas a cada trabalho.
  *
  * @param[out] trabalhos Ponteiro para o array de trabalhos.
  * @param[out] num_trabalhos Numero total de trabalhos.
  * @param[out] num_maquinas Numero total de maquinas.
  */
void inserir_dados(Trabalho** trabalhos, int* num_trabalhos, int* num_maquinas)
{
    printf("\nQuantos trabalhos deseja inserir? ");
    scanf("%d", num_trabalhos);

    printf("Numero de operacoes por trabalho: ");
    scanf("%d", num_maquinas);

    if (*num_maquinas <= 0)
    {
        printf("O numero de maquinas deve ser maior que zero.\n");
        return;
    }

    *trabalhos = malloc(*num_trabalhos * sizeof(Trabalho));

    for (int i = 0; i < *num_trabalhos; i++)
    {
        (*trabalhos)[i].num_operacoes = *num_maquinas;
        (*trabalhos)[i].operacoes = malloc(*num_maquinas * sizeof(Operacao));

        int* maquinas_usadas = malloc(*num_maquinas * sizeof(int));
        for (int k = 0; k < *num_maquinas; k++)
        {
            maquinas_usadas[k] = 0; // Inicializa como nao usadas
        }

        printf("\nInserir dados para o trabalho %d:\n", i + 1);

        for (int j = 0; j < *num_maquinas; j++)
        {
            int maquina_valida = 0;

            while (!maquina_valida)
            {
                printf("  Operacao %d - Maquina: ", j + 1);
                int maquina_temp;
                scanf("%d", &maquina_temp);

                if (maquina_temp >= 1 && maquina_temp <= *num_maquinas && maquinas_usadas[maquina_temp - 1] == 0)
                {
                    maquinas_usadas[maquina_temp - 1] = 1;
                    (*trabalhos)[i].operacoes[j].maquina = maquina_temp;
                    maquina_valida = 1;
                }
                else if (maquinas_usadas[maquina_temp - 1] == 1)
                {
                    printf("  Esta maquina ja foi usada neste trabalho. Escolha outra.\n");
                }
                else {
                    printf("  Numero da maquina invalido. Tente novamente.\n");
                }
            }

            printf("  Operacao %d - Duracao: ", j + 1);
            scanf("%d", &((*trabalhos)[i].operacoes[j].duracao));

            printf("  Operacao %d - Inicio: ", j + 1);
            scanf("%d", &((*trabalhos)[i].operacoes[j].inicio));
        }

        free(maquinas_usadas); // Libera a memoria alocada
    }
}

/**
 * @brief Lista os dados de todos os trabalhos.
 *
 * Apresenta os detalhes de todas as operacoes associadas a cada trabalho.
 *  -maquinas;
 *  -duracao;
 *  -inicio;
 *
 * @param[in] trabalhos Array de trabalhos.
 * @param[in] num_trabalhos Numero total de trabalhos.
 */
void listar_trabalhos(Trabalho* trabalhos, int num_trabalhos) 
{
    printf("\n--- Lista de Trabalhos ---\n");
    for (int i = 0; i < num_trabalhos; i++) 
    {
        printf("Trabalho %d:\n", i + 1);
        for (int j = 0; j < trabalhos[i].num_operacoes; j++) 
        {
            printf("  Operacao %d - Maquina: %d, Duracao: %d, Inicio: %d\n",
                j + 1, trabalhos[i].operacoes[j].maquina,
                trabalhos[i].operacoes[j].duracao,
                trabalhos[i].operacoes[j].inicio);
        }
    }
}

/**
 * @brief Altera os dados de uma operacao especifica.
 *
 * Permite alterar a duracao e o instante de inicio de uma operacao associada a um trabalho.
 *
 * @param[in] trabalhos Array de trabalhos.
 * @param[in] num_trabalhos Numero total de trabalhos.
 */
void alterar_dados(Trabalho* trabalhos, int num_trabalhos)
{
    int trabalho_id, operacao_id, opcao;

    if (num_trabalhos == 0) {
        printf("\nNenhum trabalho disponivel para alteracao.\n");
        return;
    }

    printf("\n--- Alteracao de Dados ---\n");
    printf("Escolha o trabalho (1 a %d): ", num_trabalhos);
    scanf("%d", &trabalho_id);

    if (trabalho_id < 1 || trabalho_id > num_trabalhos) {
        printf("ID de trabalho invalido.\n");
        return;
    }

    trabalho_id--; // Ajuste para indice do array

    printf("Deseja alterar:\n");
    printf("1. Uma operacao especifica\n");
    printf("2. Todas as operacoes do trabalho\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        // Alterar uma operacao especifica
        printf("Escolha a operacao (1 a %d): ", trabalhos[trabalho_id].num_operacoes);
        scanf("%d", &operacao_id);

        if (operacao_id < 1 || operacao_id > trabalhos[trabalho_id].num_operacoes) {
            printf("ID de operacao invalido.\n");
            return;
        }

        operacao_id--; // Ajuste para indice do array

        printf("\n--- Dados atuais da Operacao %d ---\n", operacao_id + 1);
        printf("Maquina: %d\n", trabalhos[trabalho_id].operacoes[operacao_id].maquina);
        printf("Duracao: %d\n", trabalhos[trabalho_id].operacoes[operacao_id].duracao);
        printf("Inicio: %d\n", trabalhos[trabalho_id].operacoes[operacao_id].inicio);

        printf("\n--- Alterar Dados ---\n");

        printf("Nova duracao: ");
        scanf("%d", &trabalhos[trabalho_id].operacoes[operacao_id].duracao);

        printf("Novo inicio: ");
        scanf("%d", &trabalhos[trabalho_id].operacoes[operacao_id].inicio);

        printf("\nDados alterados com sucesso.\n");
    }
    else if (opcao == 2) {
        // Alterar todas as operacoes do trabalho
        for (int j = 0; j < trabalhos[trabalho_id].num_operacoes; j++) {
            printf("\n--- Dados atuais da Operacao %d ---\n", j + 1);
            printf("Maquina: %d\n", trabalhos[trabalho_id].operacoes[j].maquina);
            printf("Duracao: %d\n", trabalhos[trabalho_id].operacoes[j].duracao);
            printf("Inicio: %d\n", trabalhos[trabalho_id].operacoes[j].inicio);

            printf("\n--- Alterar Dados ---\n");
            printf("Nova maquina para a Operacao %d: ", j + 1);
            scanf("%d", &trabalhos[trabalho_id].operacoes[j].maquina);

            printf("Nova duracao para a Operacao %d: ", j + 1);
            scanf("%d", &trabalhos[trabalho_id].operacoes[j].duracao);

            printf("Novo inicio para a Operacao %d: ", j + 1);
            scanf("%d", &trabalhos[trabalho_id].operacoes[j].inicio);
        }
        printf("\nDados de todas as operacoes do trabalho alterados com sucesso.\n");
    }
    else {
        printf("Opcao invalida.\n");
    }
}


/**
 * @brief Exporta os dados para um ficheiro.
 *
 * Salva os dados dos trabalhos e operacoes num ficheiro de texto.
 * Salva no ficheiro uma tabela onde cada linha corresponde a um trabalho, e cada
 * coluna a uma maquina "espaco" duracao "espaco" e assim sucessivamente.
 *
 * @param[in] trabalhos Array de trabalhos.
 * @param[in] num_trabalhos Numero total de trabalhos.
 * @param[in] num_maquinas Numero total de maquinas.
 * @param[in] filename Nome do ficheiro de saida.
 */
void exportar_dados(Trabalho* trabalhos, int num_trabalhos, int num_maquinas, char* filename) 
{
    FILE* file = fopen(filename, "w");
    if (!file) 
    {
        printf("Erro ao abrir o ficheiro para exportacao.\n");
        return;
    }

    // Escreve o numero de trabalhos e operacoes no inicio do arquivo
    fprintf(file, "%d %d\n", num_trabalhos, num_maquinas);

    // Escreve os dados de cada operacao para cada trabalho
    for (int i = 0; i < num_trabalhos; i++) 
    {
        for (int j = 0; j < num_maquinas; j++) 
        {
            fprintf(file, "%d %d ", trabalhos[i].operacoes[j].maquina, trabalhos[i].operacoes[j].duracao);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("\nDados exportados com sucesso para %s.\n", filename);
}

/**
 * @brief Importa os tempos de inicio de um ficheiro.
 *
 * Le os tempos de inicio de cada operacao em cada trabalho de um ficheiro de texto.
 * O ficheiro deve conter uma tabela onde cada linha corresponde a um trabalho, e cada
 * coluna a uma operacao, representando os tempos de inicio.
 *
 * @param[out] trabalhos Ponteiro para o array de trabalhos.
 * @param[in] num_trabalhos Numero total de trabalhos.
 * @param[in] num_maquinas Numero total de maquinas.
 * @param[in] filename Nome do ficheiro de onde os dados serao importados.
 */
void exportar_dados_inicio(Trabalho* trabalhos, int num_trabalhos, int num_maquinas, char* filename) 
{
    FILE* file = fopen(filename, "w");
    if (!file) 
    {
        printf("Erro ao abrir o ficheiro para exportacao dos tempos de inicio.\n");
        return;
    }

    // Escreve os tempos de inicio para cada operacao em cada trabalho
    for (int i = 0; i < num_trabalhos; i++) 
    {
        for (int j = 0; j < num_maquinas; j++) 
        {
            // Aqui, exportamos apenas o tempo de inicio da operacao
            fprintf(file, "%d ", trabalhos[i].operacoes[j].inicio);
        }
        fprintf(file, "\n"); // Nova linha apos cada trabalho
    }

    fclose(file);
    printf("\nDados de tempo de inicio exportados com sucesso para %s.\n", filename);
}

/**
 * @brief Importa os dados de um ficheiro.
 *
 * Carrega os dados dos trabalhos e operacoes a partir de um ficheiro de texto.
 * O ficheiro deve conter uma tabela onde cada linha corresponde a um trabalho, e cada
 * coluna a uma maquina "espaco" duracao "espaco" e assim sucessivamente.
 *
 * @param[out] trabalhos Ponteiro para o array de trabalhos.
 * @param[out] num_trabalhos Numero total de trabalhos.
 * @param[out] num_maquinas Numero total de maquinas.
 */
void importar_dados(Trabalho** trabalhos, int* num_trabalhos, int* num_maquinas) 
{
    char filename[] = "dados_jobshop.txt";
    FILE* arquivo = fopen(filename, "r");
    if (!arquivo) 
    {
        printf("Erro ao abrir o arquivo para importacao.\n");
        return;
    }

    if (fscanf(arquivo, "%d %d", num_trabalhos, num_maquinas) != 2) 
    {
        printf("Erro ao ler o numero de trabalhos e maquinas.\n");
        fclose(arquivo);
        return;
    }

    *trabalhos = malloc(*num_trabalhos * sizeof(Trabalho));
    if (*trabalhos == NULL) 
    {
        printf("Erro ao alocar memoria para trabalhos.\n");
        fclose(arquivo);
        return;
    }

    for (int i = 0; i < *num_trabalhos; i++) 
    {
        (*trabalhos)[i].num_operacoes = *num_maquinas;
        (*trabalhos)[i].operacoes = malloc(*num_maquinas * sizeof(Operacao));
        if ((*trabalhos)[i].operacoes == NULL) 
        {
            printf("Erro ao alocar memoria para operacoes do trabalho %d.\n", i + 1);
            fclose(arquivo);
            return;
        }

        for (int j = 0; j < *num_maquinas; j++) 
        {
            if (fscanf(arquivo, "%d %d", &(*trabalhos)[i].operacoes[j].maquina, &(*trabalhos)[i].operacoes[j].duracao) != 2) 
            {
                printf("Erro ao ler dados da operacao %d do trabalho %d.\n", j + 1, i + 1);
                fclose(arquivo);
                return;
            }
            (*trabalhos)[i].operacoes[j].inicio = 0; // Inicializa o inicio como 0
        }
    }

    fclose(arquivo);
    printf("\nDados importados com sucesso de %s.\n", filename);

    // Importar tempos de inicio do ficheiro tempo_inicio.txt
    char tempo_inicio_filename[] = "tempo_inicio.txt";
    FILE* arquivo_tempo_inicio = fopen(tempo_inicio_filename, "r");
    if (!arquivo_tempo_inicio) 
    {
        printf("Erro ao abrir o arquivo %s para os tempos de inicio.\n", tempo_inicio_filename);
        return;
    }

    for (int i = 0; i < *num_trabalhos; i++) 
    {
        for (int j = 0; j < (*trabalhos)[i].num_operacoes; j++) 
        {
            if (fscanf(arquivo_tempo_inicio, "%d", &(*trabalhos)[i].operacoes[j].inicio) != 1) 
            {
                printf("Erro ao ler tempo de inicio da operacao %d do trabalho %d.\n", j + 1, i + 1);
                fclose(arquivo_tempo_inicio);
                return;
            }
        }
    }

    fclose(arquivo_tempo_inicio);
    printf("\nTempos de inicio importados com sucesso de %s.\n", tempo_inicio_filename);

    // Exibir os dados importados (opcional)
    for (int i = 0; i < *num_trabalhos; i++) 
    {
        printf("\nTrabalho %d:\n", i + 1);
        for (int j = 0; j < (*trabalhos)[i].num_operacoes; j++) 
        {
            printf("  Operacao %d - Maquina: %d, Duracao: %d, Inicio: %d\n",
                j + 1,
                (*trabalhos)[i].operacoes[j].maquina,
                (*trabalhos)[i].operacoes[j].duracao,
                (*trabalhos)[i].operacoes[j].inicio);
        }
    }
}

/**
 * @brief Calcula os tempos de inicio e conclusao das operacoes.
 *
 * Determina os tempos de inicio de cada operacao, respeitando as restricoes do problema.
 *
 * @param[in] trabalhos Array de trabalhos.
 * @param[in] num_trabalhos Numero total de trabalhos.
 */
void calcular_tempos(Trabalho* trabalhos, int num_trabalhos) 
{
    if (num_trabalhos == 0) 
    {
        printf("\nNenhum trabalho para calcular.\n");
        return;
    }

    printf("\n--- Calculo de Tempos ---\n");
    for (int i = 0; i < num_trabalhos; i++) 
    {
        int tempo_final = 0;

        printf("\nTrabalho %d:\n", i + 1);
        for (int j = 0; j < trabalhos[i].num_operacoes; j++) 
        {
            int tempo_inicial = trabalhos[i].operacoes[j].inicio;
            int duracao = trabalhos[i].operacoes[j].duracao;
            int tempo_operacao = tempo_inicial + duracao;

            printf("  Operacao %d - Inicio: %d, Duracao: %d, Tempo Final: %d\n",
                j + 1, tempo_inicial, duracao, tempo_operacao);

            if (tempo_operacao > tempo_final) 
            {
                tempo_final = tempo_operacao;
            }
        }

        printf("\nTempo final do Trabalho %d: %d\n", i + 1, tempo_final);
    }
}

/**
 * @brief Libera a memoria alocada para os trabalhos.
 *
 * Remove todos os dados associados aos trabalhos, liberando a memoria utilizada.
 *
 * @param[in] trabalhos Array de trabalhos.
 * @param[in] num_trabalhos Numero total de trabalhos.
 */
void liberar_memoria(Trabalho* trabalhos, int num_trabalhos) 
{
    for (int i = 0; i < num_trabalhos; i++) 
    {
        free(trabalhos[i].operacoes);
    }
    free(trabalhos);
}