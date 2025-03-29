/**
 * @file util.c
 * @brief Implementação das funções auxiliares para manipulação de mapas e antenas
 * 
 * @author Diogo Pereira
 * @date 30/03/2025
 * @version 1.0
 * 
 * @course Licenciatura em Engenharia de Sistemas Informáticos EST-IPCA
 * 
 * Contém a implementação das operações de:
 * - Carregamento/libertação de mapas
 * - Conversão entre estruturas de dados
 * - Processamento de ficheiros
 */

#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "lista_ligada.h"

/**
 * @brief Carrega um mapa a partir de um ficheiro de texto
 * 
 * @param filename Nome do ficheiro contendo o mapa
 * @return Mapa* Estrutura alocada com o mapa carregado
 * @retval NULL Se o ficheiro não existir ou for inválido
 * 
 * @note Formato esperado do ficheiro:
 *       Linha 1: "<linhas> <colunas>"
 *       Linhas seguintes: linhas do mapa ('.' para vazio, caracteres para antenas)
 */
Mapa* carregarMapa(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;
    
    Mapa* mapa = (Mapa*)malloc(sizeof(Mapa));
    fscanf(file, "%d %d", &mapa->linhas, &mapa->colunas);
    
    mapa->matriz = (char**)malloc(mapa->linhas * sizeof(char*));
    for (int i = 0; i < mapa->linhas; i++) {
        mapa->matriz[i] = (char*)malloc((mapa->colunas + 1) * sizeof(char));
        fscanf(file, "%s", mapa->matriz[i]);
    }
    fclose(file);
    return mapa;
}

/**
 * @brief Liberta a memória alocada para um mapa
 * 
 * @param mapa Ponteiro para a estrutura Mapa a libertar
 * 
 * @note Liberta toda a memória associada à matriz
 */
void liberarMapa(Mapa* mapa) {
    if (!mapa) return;
    
    for (int i = 0; i < mapa->linhas; i++) {
        free(mapa->matriz[i]);
    }
    free(mapa->matriz);
    free(mapa);
}

/**
 * @brief Extrai antenas de um mapa e adiciona-as a uma lista ligada
 * 
 * @param filename Nome do ficheiro contendo o mapa
 * @param[out] lista Ponteiro para a lista ligada de destino
 * 
 * @note Ignora caracteres '.' (posições vazias)
 * @note Mantém as coordenadas originais (linha, coluna)
 */
void carregarAntenasDoMapa(const char* filename, Antena** lista) {
    Mapa* mapa = carregarMapa(filename);
    if (!mapa) return;

    for (int i = 0; i < mapa->linhas; i++) {
        for (int j = 0; j < mapa->colunas; j++) {
            char c = mapa->matriz[i][j];
            if (c != '.') {
                inserirAntena(lista, c, i, j);  // i=linha, j=coluna
            }
        }
    }
    liberarMapa(mapa);
}

/**
 * @brief Salva um mapa com marcações de efeitos nefastos
 * 
 * @param filename Nome do ficheiro de saída
 * @param mapa Estrutura Mapa original
 * @param efeitos Lista de posições com efeitos nefastos
 * 
 * @note Formato de saída idêntico ao de entrada
 * @note Marca posições com efeitos usando o carácter '#'
 * @note Sobrescreve o ficheiro se já existir
 */
void salvarMapaComEfeitos(const char* filename, Mapa* mapa, Antena* efeitos) {
    // Criar cópia do mapa original
    Mapa* mapaComEfeitos = (Mapa*)malloc(sizeof(Mapa));
    mapaComEfeitos->linhas = mapa->linhas;
    mapaComEfeitos->colunas = mapa->colunas;
    
    // Alocar e copiar matriz
    mapaComEfeitos->matriz = (char**)malloc(mapaComEfeitos->linhas * sizeof(char*));
    for (int i = 0; i < mapaComEfeitos->linhas; i++) {
        mapaComEfeitos->matriz[i] = (char*)malloc((mapaComEfeitos->colunas + 1) * sizeof(char));
        for (int j = 0; j < mapaComEfeitos->colunas; j++) {
            mapaComEfeitos->matriz[i][j] = mapa->matriz[i][j];
        }
        mapaComEfeitos->matriz[i][mapaComEfeitos->colunas] = '\0';
    }

     // Aplicar efeitos
    for (Antena* temp = efeitos; temp != NULL; temp = temp->prox) {
        int x = temp->x;
        int y = temp->y;
        if (x >= 0 && x < mapaComEfeitos->linhas && y >= 0 && y < mapaComEfeitos->colunas) {
            mapaComEfeitos->matriz[x][y] = '#';
        }
    }

    // Escrever no ficheiro
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao criar ficheiro %s\n", filename);
        return;
    }

    fprintf(file, "%d %d\n", mapaComEfeitos->linhas, mapaComEfeitos->colunas);
    for (int i = 0; i < mapaComEfeitos->linhas; i++) {
        fprintf(file, "%s\n", mapaComEfeitos->matriz[i]);
    }
    fclose(file);

    // Liberar memória
    for (int i = 0; i < mapaComEfeitos->linhas; i++) {
        free(mapaComEfeitos->matriz[i]);
    }
    free(mapaComEfeitos->matriz);
    free(mapaComEfeitos);
}