/**
 * @file funcoes.c
 * @brief Implementação das operações para gestão de antenas com listas ligadas
 * 
 * @details Implementação concreta das funções declaradas em funcoes.h para:
 * - Criação/inserção/remoção de nós
 * - Cálculo de efeitos nefastos entre antenas
 * - Operações auxiliares de consulta e visualização
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
 #include <math.h>
 
/**
 * @brief Implementação da criação de uma nova antena
 * 
 * @param[in] frequencia Carácter identificador da frequência
 * @param[in] x Coordenada horizontal (0-based)
 * @param[in] y Coordenada vertical (0-based)
 * @return Antena* Apontador para a nova antena
 * 
 * @warning O chamador deve gerenciar a liberação da memória
 * @note Complexidade: O(1)
 */
Antena* criarAntena(char frequencia, int x, int y) {
    Antena* nova = (Antena*)malloc(sizeof(Antena));
    if(nova == NULL) {
        fprintf(stderr, "Erro de alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    nova->frequencia = frequencia;
    nova->x = x;
    nova->y = y;
    nova->prox = NULL;
    return nova;
}
 
/**
 * @brief Implementação da inserção ordenada na lista
 * 
 * @param[in] head Cabeça da lista
 * @param[in] frequencia Carácter da frequência
 * @param[in] x Coordenada X (0-based)
 * @param[in] y Coordenada Y (0-based)
 * @return Antena* Nova cabeça da lista
 * 
 * @note Mantém a lista ordenada por (x,y) crescente
 * @note Rejeita duplicatas por coordenadas
 */
Antena* inserirAntena(Antena* head, char frequencia, int x, int y) {
    // Verificação de duplicados
    for (Antena* temp = head; temp != NULL; temp = temp->prox) {
        if (temp->x == x && temp->y == y) {
            return head;
        }
    }
    
    Antena* nova = criarAntena(frequencia, x, y);
    
    // Caso especial: lista vazia ou inserção no início
    if (head == NULL || (x < head->x) || (x == head->x && y < head->y)) {
        nova->prox = head;
        return nova;
    }
    
    // Procura a posição correta para inserção
    Antena* atual = head;
    while (atual->prox != NULL && 
           ((atual->prox->x < x) || 
            (atual->prox->x == x && atual->prox->y < y))) {
        atual = atual->prox;
    }
    
    // Insere o novo nó na posição encontrada
    nova->prox = atual->prox;
    atual->prox = nova;
    
    return head;
}
 
/**
 * @brief Implementação da remoção por coordenadas
 * 
 * @param[in] head Cabeça da lista
 * @param[in] x Coordenada X alvo (0-based)
 * @param[in] y Coordenada Y alvo (0-based)
 * @return Antena* Nova cabeça da lista
 * 
 * @note Libera a memória do nó removido
 * @note Se não encontrar, retorna lista inalterada
 */
 Antena* removerAntena(Antena* head, int x, int y) {
    Antena *temp = head, *prev = NULL;
    while (temp != NULL && (temp->x != x || temp->y != y)) {
        prev = temp;
        temp = temp->prox;
    }
    if (temp == NULL) return head;
    
    if (prev == NULL) {
        Antena* new_head = head->prox;
        free(temp);
        return new_head;
    } else {
        prev->prox = temp->prox;
        free(temp);
        return head;
    }
 }
 
/**
 * @brief Remove antenas em zonas de efeito nefasto
 * 
 * @param[in] lista Lista de antenas
 * @param[in] efeitos Lista de zonas de efeito
 * @return Antena* Lista filtrada
 * 
 * @note Mantém os nós de efeito na lista original
 */
 Antena* removerAntenasEmEfeitos(Antena* lista, Antena* efeitos) {

    if (lista == NULL) return NULL;
    if (efeitos == NULL) {
        printf("[AVISO] Lista de efeitos vazia - nenhuma remoção realizada\n");
        return lista;
    }

    Antena* ant = lista;
    while (ant != NULL) {
        if (ant->frequencia != '#' && existeNaLista(efeitos, ant->x, ant->y)) {
            printf("[REMOVIDO] Antena %c em (%d,%d) em localizacao de efeito nefasto\n", 
                   ant->frequencia, ant->x, ant->y);
            Antena* proximo = ant->prox;
            lista = removerAntena(lista, ant->x, ant->y);
            ant = proximo;
        } else {
            ant = ant->prox;
        }
    }
    return lista;
}

 /**
  * @brief Imprime todas as antenas da lista no terminal
  * 
  * @param[in] head Apontador para a cabeça da lista
  * 
  * @note Formato de saída:
  *       - "Antena: F (X,Y)" para antenas normais
  *       - "Efeito Nefasto: # (X,Y)" para efeitos nefasto
  */
 void imprimirAntenas(Antena* head) {
     while (head != NULL) {
         if (head->frequencia == '#') {
             printf("Efeito: %c (%d, %d)\n", head->frequencia, head->x, head->y);
         } else {
             printf("Antena: %c (%d, %d)\n", head->frequencia, head->x, head->y);
         }
         head = head->prox;
     }
 }
 
/**
 * @brief Verifica existência de antena em coordenadas
 * 
 * @param[in] lista Cabeça da lista
 * @param[in] x Coordenada X (0-based)
 * @param[in] y Coordenada Y (0-based)
 * @return int 1 se existe, 0 caso contrário
 * 
 */
 int existeNaLista(Antena* lista, int x, int y) {
     for (Antena* temp = lista; temp != NULL; temp = temp->prox) {
         if (temp->x == x && temp->y == y)
             return 1;
     }
     return 0;
 }
 
/**
 * @brief Implementação do cálculo de efeitos nefastos
 * 
 * @param[in] lista Lista de antenas
 * @return Antena* Lista de efeitos nefastos
 * 
 * @details Detecta interferência quando:
 * - Mesma frequência
 * - Alinhamento perfeito (H/V/Diagonal)
 * - Proporção de distância 1:2 ou 1:3
 * 
 * @note Pontos de efeito marcados com '#'
 */
 Antena* calcularEfeitoNefasto(Antena* lista) {
    Antena* efeitos = NULL;
    const int max_x = 12, max_y = 12;

    // Primeira antena para comparação
    Antena* a1 = lista;
    while (a1 != NULL) {
        // Segunda antena para comparação
        Antena* a2 = lista;
        while (a2 != NULL) {
            // Não comparar a mesma antena
            if (a1 != a2 && a1->frequencia == a2->frequencia) {
                int dx = a2->x - a1->x;
                int dy = a2->y - a1->y;
                
                // Verificar 8 tipos de alinhamento válidos
                if (dx == 0 || dy == 0 || abs(dx) == abs(dy) || 
                   (abs(dx) == 2*abs(dy)) || (2*abs(dx) == abs(dy)) ||
                   (abs(dx) == 3*abs(dy)) || (3*abs(dx) == abs(dy))) {
                    
                    // Calcular pontos de efeito
                    int x1 = a1->x - dx;
                    int y1 = a1->y - dy;
                    int x2 = a2->x + dx;
                    int y2 = a2->y + dy;
                    
                    // Verificar colisão com antenas existentes
                    int sobrescreve_antena = 0;
                    Antena* temp = lista;
                    while (temp != NULL) {
                        if ((temp->x == x1 && temp->y == y1) ||
                            (temp->x == x2 && temp->y == y2)) {
                            sobrescreve_antena = 1;
                            break;
                        }
                        temp = temp->prox;
                    }
                    
                    // Adicionar pontos válidos
                    if (!sobrescreve_antena) {
                        if (x1 >= 0 && x1 < max_x && y1 >= 0 && y1 < max_y) {
                            if (!existeNaLista(efeitos, x1, y1)) {
                                efeitos = inserirAntena(efeitos, '#', x1, y1);
                            }
                        }
                        if (x2 >= 0 && x2 < max_x && y2 >= 0 && y2 < max_y) {
                            if (!existeNaLista(efeitos, x2, y2)) {
                                efeitos = inserirAntena(efeitos, '#', x2, y2);
                            }
                        }
                    }
                }
            }
            a2 = a2->prox;
        }
        a1 = a1->prox;
    }
    
    return efeitos;
}