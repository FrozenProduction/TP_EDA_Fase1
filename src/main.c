/**
 * @file main.c
 * @brief Programa principal para gestão de antenas com listas ligadas
 * 
 * @details Demonstração completa das funcionalidades implementadas para:
 * - Carregamento e processamento de mapas de antenas
 * - Cálculo e visualização de efeitos de interferência
 * - Operações CRUD (Create, Read, Update, Delete) sobre a estrutura de dados
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
 #include "funcoes.h"
 #include "util.h"
 
/**
 * @brief Ponto de entrada do programa
 * 
 * @return int Código de saída (0 para sucesso)
 * 
 * @note Fluxo de execução:
 * 1. [FASE 1] Carregamento inicial do mapa
 * 2. [FASE 2] Processamento das antenas existentes
 * 3. [FASE 3] Cálculo de zonas de interferência
 * 4. [FASE 4] Operações de inserção manual
 * 5. [FASE 5] Operações de remoção manual/automática
 * 6. [FASE 6] Visualização final do estado do sistema
 * 
 * @see funcoes.h para detalhes das operações implementadas
 * @see util.h para funções auxiliares de I/O
 */
 int main() {
     /* Estruturas de dados principais */
     Antena* lista = NULL;    ///< Lista principal de antenas
     Antena* efeitos = NULL;  ///< Lista de zonas de interferência
     int linhas, colunas;     ///< Dimensões do mapa
     
     // Fase 1: Carregamento do mapa principal
     lista = carregarAntenasDoMapa("mapa.txt", &linhas, &colunas);
     printf("\nMapa Carregado:\n");
     imprimirMapa(lista, NULL, linhas, colunas);
 
     // Fase 2: Extração de antenas do mapa
     printf("\nAntenas Carregadas do Mapa:\n");
     imprimirAntenas(lista);
 
     // Fase 3: Cálculo de efeitos nefastos
     efeitos = calcularEfeitoNefasto(lista);
     printf("\nLocalizacoes com Efeitos Nefasto:\n");
     imprimirAntenas(efeitos);
     printf("\nMapa Carregado com Efeitos Nefasto:\n");
     imprimirMapa(lista, efeitos, linhas, colunas);
 
     // Fase 4: Inserção de Antenas
     lista = inserirAntena(lista, '0', 2, 3);
     lista = inserirAntena(lista, 'A', 6, 5);
     lista = inserirAntena(lista, '0', 8, 2);
     lista = inserirAntena(lista, '0', 10, 10);
     printf("\nAntenas apos Insercao:\n");
     imprimirAntenas(lista);

     // 4.1: Remoção automática por efeitos
     lista = removerAntenasEmEfeitos(lista, efeitos);
 
     // Fase 5: Remoção de Antenas
     lista = removerAntena(lista, 6, 5);
     printf("\nAntenas apos Remocao:\n");
     imprimirAntenas(lista);

     // Fase 6: Carregamento do mapa final
     //efeitos = calcularEfeitoNefasto(lista);
     printf("\nMapa Final:\n");
     imprimirMapa(lista, efeitos, linhas, colunas);
 
     return 0;
 }