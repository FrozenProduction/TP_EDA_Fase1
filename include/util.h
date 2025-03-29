/**
 * @file util.h
 * @brief Funções utilitárias para manipulação de mapas e antenas (Projeto EDA - Fase 1)
 * 
 * @author Diogo Pereira
 * @date 30/03/2025
 * @version 1.0
 * 
 * @course Licenciatura em Engenharia de Sistemas Informáticos EST-IPCA
 * 
 * Contém as definições e funções para:
 * - Carregamento/libertação de mapas
 * - Processamento de ficheiros de entrada/saída
 * - Conversão entre estruturas de dados
 */

#ifndef UTIL_H
#define UTIL_H

#include "lista_ligada.h"  // Necessário para acessar Antena

/**
 * @brief Estrutura que representa um mapa bidimensional de antenas.
 * 
 * @details Armazena uma matriz de caracteres que representa:
 * - '.' para posições vazias
 * - Caracteres alfanuméricos para antenas
 * - '#' para efeitos nefastos (em mapas processados)
 */

typedef struct {
    int linhas, colunas;
    char **matriz;
} Mapa;

/**
 * @brief Carrega um mapa a partir de um ficheiro de texto.
 * 
 * @param filename Nome do ficheiro contendo o mapa
 * @return Mapa* Estrutura alocada com o mapa carregado
 * 
 * @note Formato esperado do ficheiro:
 *       Linha 1: "<linhas> <colunas>"
 *       Linhas seguintes: linhas do mapa ('.' para vazio, caracteres para antenas)
 *       Exemplo de ficheiro válido:
 *       3 3
 *       .A.
 *       ..0
 *       ...
 */
Mapa* carregarMapa(const char* filename);

/**
 * @brief Liberta a memória alocada para um mapa.
 * 
 * @param mapa Apontador para a estrutura Mapa a libertar
 */
void liberarMapa(Mapa* mapa);

/**
 * @brief Carrega antenas de um ficheiro para uma lista ligada.
 * 
 * @param filename Nome do ficheiro contendo o mapa
 * @param[out] lista Apontador para a lista ligada de destino
 */
void carregarAntenasDoMapa(const char* filename, Antena** lista);

/**
 * @brief Salva um mapa com marcações de efeitos nefastos.
 * 
 * @param filename Nome do ficheiro de saída
 * @param mapa Estrutura Mapa original
 * @param efeitos Lista de posições com efeitos nefastos
 */
void salvarMapaComEfeitos(const char* filename, Mapa* mapa, Antena* efeitos);

#endif // UTIL_H