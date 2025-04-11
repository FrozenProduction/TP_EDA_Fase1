/**
 * @file util.h
 * @brief Utilitários para manipulação de mapas e antenas usando listas ligadas
 * 
 * @details Contém funções auxiliares para:
 * - Carregamento de mapas de ficheiros para estruturas de dados
 * - Visualização gráfica do estado atual do sistema
 * - Operações de I/O específicas do domínio
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

 #ifndef UTIL_H
 #define UTIL_H
 
 #include "funcoes.h"
 
/**
 * @brief Carrega antenas de um ficheiro de mapa para uma lista ligada
 * 
 * @param[in] filename Caminho do ficheiro contendo o mapa
 * @param[out] linhas Apontador para armazenar número de linhas do mapa
 * @param[out] colunas Apontador para armazenar número de colunas do mapa
 * @return Antena* Lista ligada contendo as antenas carregadas
 * 
 * @note Formato esperado do ficheiro:
 *       Linha 1: "<linhas> <colunas>"
 *       Linhas seguintes: linhas do mapa ('.' para vazio, outros chars para antenas)
 * 
 * @note Caracteres inválidos são tratados como espaços vazios
 */
Antena* carregarAntenasDoMapa(const char* filename, int* linhas, int* colunas);
 
/**
 * @brief Exibe representação visual do mapa com antenas e efeitos
 * 
 * @param[in] antenas Lista de antenas a exibir
 * @param[in] efeitos Lista de efeitos nefastos a exibir (pode ser NULL)
 * @param[in] linhas Número total de linhas do mapa
 * @param[in] colunas Número total de colunas do mapa
 * 
 * @note Prioridade de exibição:
 *       1. Antenas normais
 *       2. Efeitos nefastos
 *       3. Espaços vazios ('.')
 */
void imprimirMapa(Antena* antenas, Antena* efeitos, int linhas, int colunas);
 
 #endif // UTIL_H