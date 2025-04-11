/**
 * @file funcoes.h
 * @brief Definição de estruturas e operações para gestão de antenas usando listas ligadas
 * 
 * @details Implementa a Fase 1 do Projeto de Estruturas de Dados Avançadas (EDA), com:
 * - Representação de antenas via lista ligada simples
 * - Operações básicas de inserção/remoção
 * - Algoritmo de detecção de interferência entre antenas
 * - Cálculo de localizações com efeito nefasto
 * - Interface textual para visualização dos dados
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

 #ifndef FUNCOES_H
 #define FUNCOES_H
 
/**
 * @brief Estrutura que representa uma antena ou localização com efeito nefasto
 * 
 * @details Cada nó contém informações sobre:
 * - Identificador de frequência (caracter alfanumérico)
 * - Posição no mapa (coordenadas x,y)
 * - Apontador para o próximo elemento na lista
 * 
 * @note Valores especiais:
 * - frequencia '#' indica zona de interferência
 * - coordenadas (x,y) são zero-based
 */
typedef struct Antena {
    char frequencia;     ///< Carácter que identifica a frequência ('A'-'Z','0'-'9') ou '#' para efeitos nefastos
    int x;               ///< Coordenada horizontal (coluna) no mapa (0-based)
    int y;               ///< Coordenada vertical (linha) no mapa (0-based)
    struct Antena *prox; ///< Apontador para o próximo elemento na lista
} Antena;
 
/**
 * @brief Cria uma nova antena alocada dinamicamente
 * 
 * @param[in] frequencia Carácter identificador da frequência
 * @param[in] x Posição horizontal no mapa (0-based)
 * @param[in] y Posição vertical no mapa (0-based)
 * @return Antena* Apontador para a nova antena criada
 * 
 */
Antena* criarAntena(char frequencia, int x, int y);
 
/**
 * @brief Insere uma nova antena na lista de forma ordenada
 * 
 * @param[in] head Apontador para o primeiro elemento da lista
 * @param[in] frequencia Carácter identificador da frequência
 * @param[in] x Coordenada X da antena (0-based)
 * @param[in] y Coordenada Y da antena (0-based)
 * @return Antena* Novo início da lista
 * 
 * @note A lista é mantida ordenada por coordenadas (x crescente, y crescente)
 * @note Não permite duplicação por coordenadas (x,y)
 */
Antena* inserirAntena(Antena* head, char frequencia, int x, int y);
 
/**
 * @brief Remove uma antena específica da lista
 * 
 * @param[in] head Apontador para o primeiro elemento da lista
 * @param[in] x Coordenada X da antena a remover (0-based)
 * @param[in] y Coordenada Y da antena a remover (0-based)
 * @return Antena* Novo início da lista
 * 
 * @note Se a antena não existir, retorna a lista inalterada
 * @note Libera a memória do nó removido
 */
Antena* removerAntena(Antena* head, int x, int y);
 
/**
 * @brief Remove antenas que estão em locais com efeito nefasto
 * 
 * @param[in] lista Apontador para a lista de antenas
 * @param[in] efeitos Lista de locais com efeito nefasto
 * @return Antena* Nova lista após remoções
 * 
 * @note Remove apenas antenas normais (não remove os próprios efeitos)
 */
Antena* removerAntenasEmEfeitos(Antena* lista, Antena* efeitos);

/**
 * @brief Imprime todas as antenas/efeitos da lista no terminal
 * 
 * @param[in] head Apontador para o primeiro elemento da lista
 * 
 * @note Formato de saída:
 * - "Antena: [F] (X,Y)" para antenas normais
 * - "Efeito: [#] (X,Y)" para localizações com efeito nefasto
 */
void imprimirAntenas(Antena* head);
 
/**
 * @brief Verifica se existe uma antena nas coordenadas especificadas
 * 
 * @param[in] lista Apontador para o primeiro elemento da lista
 * @param[in] x Coordenada X a verificar (0-based)
 * @param[in] y Coordenada Y a verificar (0-based)
 * @return int 1 se existir, 0 caso contrário
 * 
 */
int existeNaLista(Antena* lista, int x, int y);
 
/**
 * @brief Calcula as localizações com efeito nefasto entre antenas alinhadas
 * 
 * @param[in] lista Apontador para a lista de antenas
 * @return Antena* Nova lista contendo apenas os pontos com efeito nefasto
 * 
 * @details Um efeito nefasto ocorre quando:
 * - Duas antenas têm a mesma frequência
 * - Estão perfeitamente alinhadas (horizontal, vertical ou diagonal)
 * - Uma está duas vezes mais distante que a outra
 * 
 * @note Os pontos de efeito são marcados com o carácter '#'
 */
Antena* calcularEfeitoNefasto(Antena* lista);
 
#endif // FUNCOES_H