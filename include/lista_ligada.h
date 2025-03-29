/**
 * @file lista_ligada.h
 * @brief Implementação de listas ligadas para gestão de antenas (Projeto EDA - Fase 1)
 * 
 * @author Diogo Pereira
 * @date 30/03/2025
 * @version 1.0
 * 
 * @course Licenciatura em Engenharia de Sistemas Informáticos EST-IPCA
 * 
 * Implementa a Fase 1 do projeto de Estruturas de Dados Avançadas, com operações para:
 * - Criação/remoção de antenas
 * - Cálculo de efeitos nefastos
 * - Manipulação de listas ligadas
 */

 #ifndef LISTA_LIGADA_H
 #define LISTA_LIGADA_H
 
 /**
 * @brief Estrutura que representa uma antena na lista ligada.
 * 
 * @details Cada nó contém:
 * - Frequência de ressonância (carácter único)
 * - Coordenadas (x,y) no mapa da cidade
 * - Apontador para o próximo elemento
 * 
 * @var frequencia Identificador único da frequência (A-Z, 0-9)
 * @var x Coordenada horizontal (coluna) no mapa
 * @var y Coordenada vertical (linha) no mapa
 * @var prox Apontador para próxima antena na lista
 */
 typedef struct Antena {
     char frequencia;
     int x;
     int y;
     struct Antena *prox;
 } Antena;
 
 /**
 * @brief Cria e inicializa uma nova antena.
 * 
 * @param frequencia Carácter que identifica a frequência da antena
 * @param x Posição horizontal no mapa (coluna)
 * @param y Posição vertical no mapa (linha)
 */
 Antena* criarAntena(char frequencia, int x, int y);
 
 /**
 * @brief Insere uma nova antena no início da lista.
 * 
 * @param[in,out] head Apontador para o apontador da cabeça da lista
 * @param frequencia Carácter identificador da frequência
 * @param x Coordenada X no mapa
 * @param y Coordenada Y no mapa
 */
 void inserirAntena(Antena** head, char frequencia, int x, int y);
 
 /**
 * @brief Remove uma antena específica da lista.
 * 
 * @param[in,out] head Apontador para o apontador da cabeça da lista
 * @param x Coordenada X da antena a remover
 * @param y Coordenada Y da antena a remover
 */
 void removerAntena(Antena** head, int x, int y);
 
/**
 * @brief Imprime todas as antenas da lista formatadas.
 * 
 * @param head Apontador para a primeira antena da lista
 * 
 * @note Formato de saída: "Tipo: F (X,Y)" (F=frequência)
 * @note Para efeitos nefastos, mostra "Efeito: # (X,Y)"
 */
 void imprimirAntenas(Antena* head);
 
 /**
 * @brief Verifica se existe antena nas coordenadas especificadas.
 * 
 * @param lista Apontador para a cabeça da lista
 * @param x Coordenada X a verificar
 * @param y Coordenada Y a verificar
 */
 int existeNaLista(Antena* lista, int x, int y);
 
 /**
 * @brief Calcula localizações com efeito nefasto entre antenas alinhadas.
 * 
 * @param lista Apontador para a lista de antenas
 * @return Antena* Nova lista contendo os pontos de efeito nefasto
 * @note Pontos de efeito são marcados com o carácter '#'
 */
 Antena* calcularEfeitoNefasto(Antena* lista);
 
 #endif