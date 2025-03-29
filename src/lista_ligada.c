/**
 * @file lista_ligada.c
 * @brief Implementação concreta das operações com listas ligadas para gestão de antenas (Projeto EDA - Fase 1)
 * 
 * @author Diogo Pereira
 * @date 30/03/2025
 * @version 1.0
 * 
 * @course Licenciatura em Engenharia de Sistemas Informáticos EST-IPCA
 * 
 * Implementação das funções declaradas em lista_ligada.h para:
 * - Criação/inserção/remoção de nós
 * - Cálculo de efeitos nefastos entre antenas
 * - Operações auxiliares de consulta
 */

#include <stdio.h>
#include <stdlib.h>
#include "lista_ligada.h"
#include <math.h>

/**
 * @brief Cria e inicializa uma nova antena na memória
 * 
 * @param frequencia Carácter identificador da frequência
 * @param x Coordenada horizontal no mapa
 * @param y Coordenada vertical no mapa
 * @return Antena* Apontador para a antena criada
 */
Antena* criarAntena(char frequencia, int x, int y) {
    Antena* nova = (Antena*)malloc(sizeof(Antena));
    nova->frequencia = frequencia;
    nova->x = x;
    nova->y = y;
    nova->prox = NULL;
    return nova;
}

/**
 * @brief Insere uma nova antena no início da lista
 * 
 * @param[in,out] head Apontador para o apontador da cabeça da lista
 * @param frequencia Carácter identificador da frequência
 * @param x Coordenada X no mapa
 * @param y Coordenada Y no mapa
 * 
 * @note Verifica e evita duplicação por coordenadas
 */
void inserirAntena(Antena** head, char frequencia, int x, int y) {
    // Verificação de duplicados
    for (Antena* temp = *head; temp != NULL; temp = temp->prox) {
        if (temp->x == x && temp->y == y) {
            return;
        }
    }
    Antena* nova = criarAntena(frequencia, x, y);
    nova->prox = *head;
    *head = nova;
}

/**
 * @brief Remove uma antena específica da lista
 * 
 * @param[in,out] head Apontador para o apontador da cabeça da lista
 * @param x Coordenada X da antena a remover
 * @param y Coordenada Y da antena a remover
 * 
 * @note Não faz nada se a antena não existir
 */
void removerAntena(Antena** head, int x, int y) {
    Antena *temp = *head, *prev = NULL;
    while (temp != NULL && (temp->x != x || temp->y != y)) {
        prev = temp;
        temp = temp->prox;
    }
    if (temp == NULL) return;
    if (prev == NULL) *head = temp->prox;
    else prev->prox = temp->prox;
    free(temp);
}

/**
 * @brief Imprime todas as antenas da lista no terminal
 * 
 * @param head Apontador para a cabeça da lista
 * 
 * @note Formato de saída:
 *       - "Antena: F (X,Y)" para antenas normais
 *       - "Efeito Nefasto: # (X,Y)" para efeitos
 */
void imprimirAntenas(Antena* head) {
    while (head != NULL) {
        if (head->frequencia == '#') {
            printf("Efeito Nefasto: %c (%d, %d)\n", head->frequencia, head->x, head->y);
        } else {
            printf("Antena: %c (%d, %d)\n", head->frequencia, head->x, head->y);
        }
        head = head->prox;
    }
}

/**
 * @brief Verifica a existência de antena em coordenadas específicas
 * 
 * @param lista Apontador para a cabeça da lista
 * @param x Coordenada X a verificar
 * @param y Coordenada Y a verificar
 * @return int 1 se existir, 0 caso contrário
 */
int existeNaLista(Antena* lista, int x, int y) {
    for (Antena* temp = lista; temp != NULL; temp = temp->prox) {
        if (temp->x == x && temp->y == y)
            return 1;
    }
    return 0;
}

/**
 * @brief Calcula pontos com efeito nefasto entre antenas alinhadas
 * 
 * @param lista Apontador para a lista de antenas
 * @return Antena* Nova lista contendo apenas efeitos nefastos
 * 
 * @note Algoritmo:
 *       1. Cria array temporário com todas antenas
 *       2. Compara todos os pares possíveis
 *       3. Para pares com mesma frequência, verifica 8 tipos de alinhamento
 *       4. Calcula pontos de efeito em ambas as direções
 *       5. Filtra posições inválidas ou ocupadas
 */
    Antena* calcularEfeitoNefasto(Antena* lista) {
    Antena* efeitos = NULL;
    const int max_x = 12, max_y = 12;
    
    // Converter lista para array para acesso indexado
    int count = 0;
    for (Antena* temp = lista; temp != NULL; temp = temp->prox) count++;
    
    Antena** array = (Antena**)malloc(count * sizeof(Antena*));
    int i = 0;
    for (Antena* temp = lista; temp != NULL; temp = temp->prox) {
        array[i++] = temp;
    }

    // Comparar todos os pares de antenas
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (i == j) continue;
            
            Antena* a1 = array[i];
            Antena* a2 = array[j];
            
            if (a1->frequencia == a2->frequencia) {
                int dx = a2->x - a1->x;
                int dy = a2->y - a1->y;
                
                // Verificar 8 tipos de alinhamento válidos
                if (dx == 0 || dy == 0 || abs(dx) == abs(dy) || 
                   (abs(dx) == 2*abs(dy)) || (2*abs(dx) == abs(dy)) ||
                   (abs(dx) == 3*abs(dy)) || (3*abs(dx) == abs(dy))) {
                    
                    // Calcular pontos de efeito em ambas as direções
                    int x1 = a1->x - dx;
                    int y1 = a1->y - dy;
                    int x2 = a2->x + dx;
                    int y2 = a2->y + dy;
                    
                    // Verificar colisão com antenas existentes
                    int sobrescreve_antena = 0;
                    for (int k = 0; k < count; k++) {
                        if ((x1 == array[k]->x && y1 == array[k]->y) ||
                            (x2 == array[k]->x && y2 == array[k]->y)) {
                            sobrescreve_antena = 1;
                            break;
                        }
                    }
                    
                    if (!sobrescreve_antena) {
                        // Adicionar pontos válidos
                        if (x1 >= 0 && x1 < max_x && y1 >= 0 && y1 < max_y) {
                            if (!existeNaLista(efeitos, x1, y1)) {
                                inserirAntena(&efeitos, '#', x1, y1);
                            }
                        }
                        if (x2 >= 0 && x2 < max_x && y2 >= 0 && y2 < max_y) {
                            if (!existeNaLista(efeitos, x2, y2)) {
                                inserirAntena(&efeitos, '#', x2, y2);
                            }
                        }
                    }
                }
            }
        }
    }
    
    free(array);
    return efeitos;
}