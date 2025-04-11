/**
 * @file util.c
 * @brief Implementação das funções utilitárias para manipulação de mapas
 * 
 * @details Contém a implementação concreta das operações de:
 * - Carregamento de ficheiros para estruturas de dados
 * - Renderização gráfica do estado do sistema
 * 
 * @author Diogo Pereira
 * @date 11/04/2025
 * @version 1.1
 * 
 * @copyright Copyright (c) 2025
 * 
 * @course Licenciatura em Engenharia de Sistemas Informáticos
 * @institution EST-IPCA
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "util.h"
 #include "funcoes.h"
 
 /**
 * @brief Implementação do carregamento de mapas
 * 
 * @param[in] filename Nome do ficheiro de entrada
 * @param[out] linhas Apontador para armazenar número de linhas
 * @param[out] colunas Apontador para armazenar número de colunas
 * @return Antena* Lista de antenas carregadas
 * 
 * @note Formato do ficheiro esperado:
 *       Linha 1: "<linhas> <colunas>"
 *       Linhas seguintes: linhas do mapa
 * 
 * @note Caracteres '.' são considerados espaços vazios
 */
Antena* carregarAntenasDoMapa(const char* filename, int* linhas, int* colunas) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erro: Não foi possível abrir o ficheiro %s\n", filename);
        exit(EXIT_FAILURE);
    }

    /* Leitura das dimensões do mapa */
    if (fscanf(file, "%d %d", linhas, colunas) != 2) {
        fclose(file);
        fprintf(stderr, "Erro: Formato inválido no ficheiro %s\n", filename);
        exit(EXIT_FAILURE);
    }

    Antena* lista = NULL;
    char linha[256];
    int y = 0;
    
    /* Processamento linha a linha */
    while (fscanf(file, "%s", linha) == 1 && y < *linhas) {
        for (int x = 0; x < *colunas && x < (int)strlen(linha); x++) {
            if (linha[x] != '.') {
                lista = inserirAntena(lista, linha[x], x, y);
            }
        }
        y++;
    }
    
    fclose(file);
    return lista;
}
 
/**
 * @brief Implementação da renderização do mapa
 * 
 * @param[in] antenas Lista de antenas ativas
 * @param[in] efeitos Lista de zonas de interferência (pode ser NULL)
 * @param[in] linhas Número total de linhas do mapa
 * @param[in] colunas Número total de colunas do mapa
 * 
 * @note Prioridade de renderização:
 *       1. Antenas normais
 *       2. Zonas de interferência
 *       3. Espaços vazios ('.')
 */
void imprimirMapa(Antena* antenas, Antena* efeitos, int linhas, int colunas) {
    /* Validação de parâmetros */
    if (linhas <= 0 || colunas <= 0) {
        fprintf(stderr, "Erro: Dimensões inválidas do mapa\n");
        return;
    }

    /* Renderização do mapa */
    for (int y = 0; y < linhas; y++) {
        for (int x = 0; x < colunas; x++) {
            char c = '.';
            
            /* Verifica antenas primeiro */
            for (Antena* a = antenas; a != NULL; a = a->prox) {
                if (a->x == x && a->y == y) {
                    c = a->frequencia;
                    break;
                }
            }
            
            /* Verifica efeitos se necessário */
            if (c == '.' && efeitos != NULL) {
                for (Antena* e = efeitos; e != NULL; e = e->prox) {
                    if (e->x == x && e->y == y) {
                        c = '#';
                        break;
                    }
                }
            }
            
            printf("%c", c);
        }
        printf("\n");
    }
}