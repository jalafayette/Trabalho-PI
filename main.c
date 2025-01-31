/******************************************************************************
                                   IPCA

Trabalho realizado por:

    Afonso Lopes nº 33226
    Carlos Lopes nº 22848
    Joao Lafayette nº 31587
    Matheus Motta nº 33227

    Curso:           Engenharia Eletrotecnica e Computadores (EEC)
    Disciplina:      Programacao Imperativa
    Ano Letivo:      2024/2025
******************************************************************************/

#include <locale.h> // Inclui a biblioteca para configuração de localidade
#include <stdio.h> // Inclui a biblioteca padrão de entrada e saída
#include "funcoes.h" // Inclui o cabeçalho com as declarações das funções
#include "global.h" // Inclui o cabeçalho com as definições das estruturas de dados

int main() 
{
    setlocale(LC_ALL, "Portuguese"); // Define a localidade como "Portuguese" para suportar caracteres especiais
    Trabalho* trabalhos = NULL; // Declara um ponteiro para o array de trabalhos e inicializa como NULL
    int num_trabalhos = 0, num_maquinas = 0; // Declara variáveis para armazenar o número de trabalhos e máquinas, inicializadas como 0
    int opcao; // Declara uma variável para armazenar a escolha do usuário no menu

    do 
    {
        // Exibe o menu de opções para o usuário
        printf("\n--- MENU ---\n");
        printf("1. Inserir dados\n");
        printf("2. Listar trabalhos\n");
        printf("3. Alterar dados\n");
        printf("4. Calcular tempos\n");
        printf("5. Exportar dados\n");
        printf("6. Importar dados\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: "); scanf("%d", &opcao); // Lê a escolha do usuário

        // Executa a função correspondente à escolha do usuário
        switch (opcao) 
        {
        case 1:
            inserir_dados(&trabalhos, &num_trabalhos, &num_maquinas); // Chama a função para inserir dados
            break;
        case 2:
            listar_trabalhos(trabalhos, num_trabalhos); // Chama a função para listar trabalhos
            break;
        case 3:
            alterar_dados(trabalhos, num_trabalhos); // Chama a função para alterar dados
            break;
        case 4:
            calcular_tempos(trabalhos, num_trabalhos); // Chama a função para calcular tempos
            break;
        case 5:
            exportar_dados(trabalhos, num_trabalhos, num_maquinas, "lista_dados.txt"); // Chama a função para exportar dados
            exportar_dados_inicio(trabalhos, num_trabalhos, num_maquinas, "dados_tempo_inicio.txt"); // Chama a função para exportar tempos de início
            break;
        case 6:
            importar_dados(&trabalhos, &num_trabalhos, &num_maquinas); // Chama a função para importar dados
            break;
        case 0:
            printf("A sair...\n"); // Exibe mensagem de saída
            break;
        default:
            printf("Opcao invalida!\n"); // Exibe mensagem de erro para opção inválida
            break;
        }
    } while (opcao != 0); // Continua exibindo o menu até que o usuário escolha sair (opção 0)

    liberar_memoria(trabalhos, num_trabalhos); // Libera a memória alocada para os trabalhos e operações

    return 0; // Retorna 0 para indicar que o programa terminou com sucesso
}
