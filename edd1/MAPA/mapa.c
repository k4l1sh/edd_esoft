#include <stdio.h>
#include <string.h>

// Constantes estipuladas de acordo com o problema e o RA do usuário
#define RA 961622222 // Atribuir valor do RA igual a 0 caso deseje inserir manualmente o RA após a execução do código
//#define RA 0
#define VERTICES 5
#define ARESTAS 7
#define INICIO 1
#define INFINITO 4294967295 // Valor máximo para unsigned int

// Estrutura para definição das conexões existentes entre os vértices, pois o grafo do problema é um grafo direcionado
typedef struct {
    int origem, destino;
} Direcionamento;
Direcionamento conexoes[] = {{1,2}, {1,3}, {2,4}, {2,5}, {3,2}, {3,5}, {4,5}};

// Estrutura do caminho percorrido até o vertice alvo
typedef struct {
    char caminho[255];
} Caminho;
Caminho caminho[VERTICES];

// Declarações de variáveis que serão utilizadas conforme o tamanho de vértices do grafo
unsigned int    matrizAdjacencia[VERTICES][VERTICES],
                menorDistancia[VERTICES][2],
                visitado[VERTICES],
                heap[VERTICES][2],
                tamanhoHeap = VERTICES;


// Função para verificar se o RA já foi definido ou se será definido manualmente
int verificarRA(int ra) {
    if(ra == 0) {
        printf("Digite seu RA: ");
        scanf("%d", &ra);
    } 
    return ra;
}

// Algoritmo para atribuir os pesos iniciais conforme o RA estipulado
int pesoDistancia[ARESTAS];
void atribuirDistancia(int ra) {
    int dezena = 10;
    int tempRA;
    for (short i = 0; i < ARESTAS; i++) {
        tempRA = ra;
        while(dezena < tempRA)
            tempRA /= 10;
        pesoDistancia[i] = tempRA%10*100;
        dezena *= 10;
    }
}

/*
Função para organizar o heap fazendo com que a raiz do heap seja o valor mínimo.
Vale lembrar que a implementação do algoritmo Dijkstra poderia ser simplificada
seguindo uma implementação em um array com complexidade de tempo de O(vertices²),
porém foi escolhido implementá-lo em um min-heap para alcançar uma complexidade de tempo
de O((Vertices + arestas)log(vertices)) e estudar o funcionamento deste tipo abstrato de dados.
*/
void minHeapify(unsigned int heap[][2], unsigned int ponteiro, unsigned int tamanhoHeap) {

    // Organização do heap através de um array
    unsigned int esquerda = (2*ponteiro), direita = (2*ponteiro+1), menor = 0;

    // Comparação entre os elementos para achar o menor valor
    if(esquerda <= tamanhoHeap && heap[esquerda-1][0] < heap[ponteiro-1][0])
        menor = esquerda;
    else
        menor = ponteiro;
    if(direita <= tamanhoHeap && heap[direita-1][0] < heap[menor-1][0])
        menor = direita;

    // troca dos elementos e recursividade da função para organizar o heap
    if(menor != ponteiro) {
        unsigned int trocaOrigem = heap[ponteiro-1][0], trocaDestino = heap[ponteiro-1][1];      
        heap[ponteiro-1][0] = heap[menor-1][0];
        heap[ponteiro-1][1] = heap[menor-1][1];
        heap[menor-1][0] = trocaOrigem;
        heap[menor-1][1] = trocaDestino;
        minHeapify(heap, menor, tamanhoHeap);
    }
}

// Função para criação do min-heap
void construirMinHeap(unsigned int heap[][2], unsigned int tamanhoHeap) {    
    for(short i = (tamanhoHeap/2); i > 0; i--)
        minHeapify(heap, i, tamanhoHeap);
}

// Implementação do algoritmo Dijkstra 
void dijkstra(unsigned int matrizAdjacencia[][VERTICES], unsigned int distancia[][2]) {
    
    // Atribuição de pesos muito grandes para conseguir executar o algoritmo Dijkstra
    for(short i = 0; i < VERTICES; i++) {
        visitado[i] = 0;
        heap[i][0] = INFINITO;
        heap[i][1] = i;
        distancia[i][0] = INFINITO;
        distancia[i][1] = INFINITO;
    }

    // Atribuição de peso 0 para o vértice de origem
    heap[INICIO-1][0] = 0;
    distancia[INICIO-1][0] = 0;
    distancia[INICIO-1][1] = 0;
    
    // Construção da estrutura do min-heap inicial
    construirMinHeap(heap, tamanhoHeap);
    
    // Começo do loop do algoritmo Dijkstra
    while(tamanhoHeap > 0) {

         // Extração da raiz do heap (valor mínimo) e atualização do seu tamanho
        unsigned int visita = heap[0][1], valorMinimo = heap[0][0];
        tamanhoHeap--;
        if(tamanhoHeap > 0) {        
            heap[0][0] = heap[tamanhoHeap][0];
            heap[0][1] = heap[tamanhoHeap][1];
            construirMinHeap(heap, tamanhoHeap);
        }

        // Controle de vértices visitados e verificação do valor mínimo
        visitado[visita] = 1;
        if(valorMinimo != INFINITO) {

            // Loop pelos vértices do grafo e inicialização do peso inicial
            for (short vertice = 0; vertice < VERTICES; vertice++) {
                unsigned int pesoInicial = matrizAdjacencia[visita][vertice];

                // Controle dos vértices que já foram visitados e exclusão dos que tem peso infinito
                if (pesoInicial != INFINITO && visitado[vertice] != 1) {
                    unsigned int peso = distancia[visita][0] + pesoInicial;

                    // Comparação de maior peso
                    if(distancia[vertice][0] > peso) {
                        distancia[vertice][0] = peso;  
                        distancia[vertice][1] = visita;

                        // Retiragem do vértice do heap
                        for(short i = 0; i < tamanhoHeap; i++) {                                                                
                            if(heap[i][1] == vertice) {

                                // Atualização do peso no heap
                                if(peso < heap[i][0]) {                                   
                                    heap[i][0] = peso;

                                    // Troca do vértice do heap com seu parente
                                    unsigned int parente = i/2; 
                                    while(heap[parente][0] > heap[i][0] && i > 0) {
                                        unsigned int trocaOrigem = heap[parente][0], trocaDestino = heap[parente][1];
                                        heap[parente][0] = heap[i][0];
                                        heap[parente][1] = heap[i][1];
                                        heap[i][0] = trocaOrigem;
                                        heap[i][1] = trocaDestino;
                                        i = parente;
                                        parente /= 2;
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
            }
        } else
            break;
    }    
}


// Função que escreve o caminho a percorrrer do vértice INICIO até o vértice final
void escreverCaminho(int ultimoVertice, int posicao) {
    if(posicao+1 != INICIO) {
        char buffer[255];
        snprintf(buffer, 12, "%d -> ", ultimoVertice+1);

        // Incremento da string do caminho e alocação dela em caminho[vértice].caminho
        strcat(buffer, caminho[posicao].caminho);
        strcpy(caminho[posicao].caminho, buffer);

        // Utilização de recursividade para escrever o caminho completo
        if(ultimoVertice >= INICIO)
            escreverCaminho(menorDistancia[ultimoVertice][1], posicao);
    }
}

// Função para visualização da matriz de adjacência
void testeVisualizarMatriz() {
    printf("Matriz de Adjacencia\n");
    for(short i = 0; i < VERTICES; i++) {
        for(short k = 0; k < VERTICES; k++)
            printf("%10u\t", matrizAdjacencia[i][k]);
        printf("\n");
    }
}

// Função para impressão dos dados utilizados
void imprimirDados(int ra) {
    printf("Dados utilizados: RA = %d, vertices = %d, arestas = %d\n", ra, VERTICES, ARESTAS);
    printf("Caminhos do grafo orientado com seus pesos: ");
    for(short i = 0; i < ARESTAS; i++)
        printf("%d -> %d (%d)\t", conexoes[i].origem, conexoes[i].destino, pesoDistancia[i]);
    printf("\n");
}

void main() {

    // Execução da função para estipular os pesos (distâncias) e verificação da necessidade de inserção manual de um RA
    int ra = verificarRA(RA);
    atribuirDistancia(ra);
    
    // Criação da matriz de adjacência e da matriz de menor peso
    memset(matrizAdjacencia, -1, sizeof(matrizAdjacencia));
    memset(menorDistancia, -1, sizeof(menorDistancia));

    // Impressão dos valores a serem utilizados
    imprimirDados(ra);    

    // Preenchimento da matriz de adjacência com os valores estipulados pelo problema
    for(short i = 0; i < ARESTAS; i++)
        if(matrizAdjacencia[conexoes[i].origem-1][conexoes[i].destino-1] > pesoDistancia[i])
            matrizAdjacencia[conexoes[i].origem-1][conexoes[i].destino-1] = pesoDistancia[i];

    // Execução do algoritmo dijkstra para a matriz de adjacência e a matriz de menor peso
    dijkstra(matrizAdjacencia, menorDistancia);
    
    // Impressão dos melhores caminhos e respectivos pesos após a execução do algoritmo de Dijkstra
    printf("Resultados:\n");
    for(short i = 0; i < VERTICES; i++) {
        escreverCaminho(menorDistancia[i][1], i);
        printf("Vertice %d para o vertice %d: peso = %d,\tcaminho = %s%d\n", INICIO, i+1, menorDistancia[i][0], caminho[i].caminho, i+1);
    }    
    // testeVisualizarMatriz(); // Visualização da matriz de adjacência para debug
}