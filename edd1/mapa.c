/*
Uma transportadora especializada em grãos opera nas cinco regiões do Brasil, tendo o porto de Santos como seu destino final. Você pode observar as rotas de operações a partir do grafo a seguir: 

 

O porto de Santos é o vértice indicado pelo número 5 (cinco). As demais regiões são representadas pelos demais vértices que vão de 1 (um) a 4 (quatro). 

Você foi convidado a desenvolver uma solução que ajude a empresa em uma tomada de decisão, pois devido ao aumento consecutivo do valor do diesel, a empresa quer uma estimativa de quais os menores custos para continuar operando no porto de Santos. Foi feito um levantamento histórico com o custo médio de operação em cada ponto de origem até o destino final.  

No contexto da figura, os vértices 1, 2, 3, 4 e 5 representam, respectivamente as regiões cidades em que a transportadora opera hoje. O trajeto é representado pelas ARESTAS que liga (1 a 2), (1 a 3), (2 a 4), (2 a 5), e assim por diante. O custo médio (peso) entre cada conexão está representado por X. Você deve substituir o X pelos 7 primeiros dígitos do seu RA (indo da esquerda para direita) multiplicado por 100, na sequência: (1-2), (1-3), (2-4), (2-5), (3-2), (3-5), (4-5).  

Exemplo:  

RA 2025703-5 = Será utilizado os seguintes números do seu RA 2025703  

RA 202570-5 = Em caso de 6 dígitos, acrescentar o dígito 1 ao final 2025701  

(1-2) = 2 * 100 = 200
(1-3) = 0 * 100 = 0
(2-4) = 2 * 100 = 200
......

Considerando que você precisa desenvolver a solução, utilize o algoritmo de Dijkstra e informe o caminho de menor custo saindo de 1 (que é a matriz da empresa em Mato Grosso do Sul) e chegando em 5. O resultado do seu programa deverá indicar as rotas que poderão ser utilizadas pela companhia e o seu respectivo peso.  

Passos para realizar o Mapa:  

1. Desenvolva um programa em linguagem C, salvar com a extensão (.c) que informe os caminhos saindo de 1 e chegando em 5.  

1.1. Neste código, usuário deverá excetuar as seguintes ações:
   - informar o número de vértices (ponto de rota),
   - informar as ARESTAS com suas respectivas rotas de origem e destino,
   - informar o custo correspondente ao seu RA para todas as rotas.

1.2. Cálcular rotas.  

1.3. Apresentar na tela todos os destinos com os seus respectivos pesos. 

2.   Após a impressão (item 1.3) tirar um print da sua tela de forma que pegue todos os destinos.
   - Neste print marque o(s) caminho(s) de menor custo saindo de 1 e chegando em 5 (usar qualquer programa de edição de imagem)
   - Salve com extensão (.doc), (.docx), (.pdf), (.png) e (.jpg) 

Orientações para realização da Atividade MAPA:
- Realize uma Leitura da Unidade V do Livro da Disciplina.
- Leia os materiais extras sobre análise ambiental disponíveis no Material da Disciplina.
- Assista ao Vídeo de Orientações gravado pelo professor: https://youtu.be/AtVaPUczQ6I
- Certifique-se de que está encaminhando o arquivo correto no seu Studeo antes de Finalizar, pois não haverá como editar e/ou enviar outro arquivo após a finalização.
- Enviar o código fonte (arquivo.c) nomeando o arquivo com seu nome completo. Exemplo: Erinaldo_Nascimento.c
- Enviar o print contendo todas as rotas e a demarcação da rota com menor custo
- Em casos de dúvidas, entre em contato com o seu Professor(a) Mediador(a) pelo Studeo no Fale com o Mediador.

* Indicação de IDE para desenvolver sua atividade MAPA (DEV C++, Code::Block, https://replit.com/)  

Bons estudos. Sucesso!
*/

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
Vale lembrar que a implementação do algoritmo Dijktra poderia ser simplificada
seguindo uma implementação em um array com complexidade de tempo de O(vertices²),
porém foi escolhido implementá-lo em um min-heap para alcançar uma complexidade de tempo
de O((Vertices + arestas)log(vertices)) e estudar o funcionamento deste tipo abstrato de dado.
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