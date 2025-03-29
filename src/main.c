/**
 * @file main.c
 * @brief Programa principal do Projeto EDA - Fase 1
 * 
 * @author Diogo Pereira
 * @date 30/03/2025
 * @version 1.0
 * 
 * @course Licenciatura em Engenharia de Sistemas Informáticos EST-IPCA
 * 
 * Demonstração das funcionalidades implementadas para:
 * - Gestão de antenas via listas ligadas
 * - Cálculo de efeitos nefastos
 * - Manipulação de mapas
 */

#include <stdio.h>
#include <stdlib.h>
#include "lista_ligada.h"
#include "util.h"

/**
 * @brief Função principal do programa
 * 
 * @note Fluxo do programa:
 *       1. Carrega mapa inicial
 *       2. Processa antenas existentes
 *       3. Calcula e mostra efeitos nefastos
 *       4. Salva/recarrega mapa com efeitos
 *       5. Demonstra operações de inserção/remoção
 */
int main() {
    // Inicialização da lista de antenas
    Antena* lista = NULL;
    
    // Fase 1: Carregamento do mapa principal
    Mapa* mapa = carregarMapa("mapa.txt");
    if (mapa) {
        printf("\nMapa carregado:\n");
        for (int i = 0; i < mapa->linhas; i++) {
            printf("%s\n", mapa->matriz[i]);
        }
    } else {
        printf("\nErro ao carregar o mapa.\n");
    }

    // Fase 2: Extração de antenas do mapa
    carregarAntenasDoMapa("mapa.txt", &lista);
    printf("\nAntenas carregadas do mapa:\n");
    imprimirAntenas(lista);

    // Fase 3: Cálculo de efeitos nefastos
    Antena* efeitos = calcularEfeitoNefasto(lista);
    printf("\nLocalizacoes com efeito nefasto:\n");
    imprimirAntenas(efeitos);

    // Fase 4: Salvar e carregar mapa com efeitos
    salvarMapaComEfeitos("mapaefeitos.txt", mapa, efeitos);

    printf("\nMapa com efeito nefasto carregado:\n");
    Mapa* mapa_com_efeitos = carregarMapa("mapaefeitos.txt");
    if (mapa_com_efeitos) {
        for (int i = 0; i < mapa_com_efeitos->linhas; i++) {
            printf("%s\n", mapa_com_efeitos->matriz[i]);
        }
        liberarMapa(mapa_com_efeitos);
    } else {
        printf("Erro ao carregar mapaefeitos.txt\n");
    }

    // Fase 5: Inserção de Antenas
    inserirAntena(&lista, 'O', 3, 2);
    inserirAntena(&lista, 'A', 5, 6);
    inserirAntena(&lista, 'O', 2, 8);
    inserirAntena(&lista, 'O', 0, 11);
    inserirAntena(&lista, 'O', 10, 10);

    printf("\nAntenas apos insercao:\n");
    imprimirAntenas(lista);

    // 5.1: Remoção automática por efeitos
    Antena* ant = lista;
    while (ant != NULL) {
        if (ant->frequencia != '#' && existeNaLista(efeitos, ant->x, ant->y)) {
            printf("[REMOVIDO] Antena %c em (%d,%d) em localizacao de efeito nefasto\n", 
               ant->frequencia, ant->x, ant->y);
            Antena* proximo = ant->prox;
            removerAntena(&lista, ant->x, ant->y);
            ant = proximo;
        } else {
            ant = ant->prox;
        }
    }

    // Fase 6: Remoção de Antenas
    removerAntena(&lista, 5, 6);
    removerAntena(&lista, 2, 8);
    printf("\nAntenas apos remocao:\n");
    imprimirAntenas(lista);

    // Liberação de recursos
    liberarMapa(mapa);

    return 0;
}