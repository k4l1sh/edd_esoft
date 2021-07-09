#include <stdio.h>
#define RA 987878788
#define QNTBARRACAS 8

// Inicialização dos vetores que serão utilizados no algoritmo mergesort
int vetorVendas[QNTBARRACAS], vetorVendasAuxiliar[QNTBARRACAS];

// Sugestão de estrutura para armazenar os dados das barracas
typedef struct {
    char nome[30];
    int vendas;
    short dia;
} Barraca;
Barraca barracas[QNTBARRACAS];

// Algoritmo que atribui os valores do RA da esquerda para a direita como vendas diárias de cada barraca em barracas[id].vendas
void atribuirVendas() {
    int dezena = 10;
    int tempRA;
    for (short id = 0; id < QNTBARRACAS; id++) {
        tempRA = RA;
        while(dezena < tempRA)
            tempRA /= 10;
        barracas[id].vendas = tempRA%10;
        dezena *= 10;
    }
}

// Implementação do algoritmo mergesort
int mergeSort(short inicio, short final, int vetor[], int vetorAuxiliar[]) {   

    // Utilização da recursividade para ordenar o vetor separado em diversas partes
    if(final <= inicio)
        return 0;
    mergeSort(inicio, (inicio+final)/2, vetor, vetorAuxiliar);
    mergeSort((inicio+final)/2+1, final, vetor, vetorAuxiliar);

    // Inicialização dos ponteiros que servirão para separar quais valores devem ser comparados na ordenação
    short ponteiroE = inicio;
    short ponteiroD = (inicio+final)/2+1;

    // Algoritmo mergesort para ordenar o vetor de acordo com a posição dos ponteiros
    for(short i = inicio; i <= final; i++) {
        if(ponteiroE == (inicio+final)/2+1) {
            vetorAuxiliar[i] = vetor[ponteiroD];
            ponteiroD++;  
        } else if(ponteiroD == final+1 || vetor[ponteiroE] < vetor[ponteiroD]) {
            vetorAuxiliar[i] = vetor[ponteiroE];
            ponteiroE++;   
        } else {
            vetorAuxiliar[i] = vetor[ponteiroD];
            ponteiroD++;
        }
    }

    // Atribuição dos valores do vetor auxiliar para o vetor original ordenado
    for(short i = inicio; i <= final; i++ ){
        vetor[i] = vetorAuxiliar[i];
    }
}

// Implementação extra de uma função para ranquear as barracas que mais venderam comparando com o vetor ordenado pelo mergesort
int vetorVendasRanking[QNTBARRACAS];
int rankingVendas(int vendas) {
    for (short id = 0; id < QNTBARRACAS; id++) {
        if(vetorVendasRanking[id] == vendas) {
            vetorVendasRanking[id] = 999;
            return id+1;
        }
    }  
}

void main() {

    // Impressão dos valores a serem utilizados
    printf("Vetor de vendas das %d barracas para o RA %d: ", QNTBARRACAS, RA);

    // Atribuição dos valores do RA para a estrutura da barraca e o vetor de vendas que será ordenado pelo mergesort
    atribuirVendas();
    for (short id = 0; id < QNTBARRACAS; id++) {
        vetorVendas[id] = barracas[id].vendas;
        vetorVendasRanking[id] = barracas[id].vendas;
        printf("%d", vetorVendas[id]); 
    }

    // Ordenação do vetor ve vendas através do algoritmo mergesort
    printf("\nVetor de vendas das barracas ordenado pelo mergesort: ");
    mergeSort(0, QNTBARRACAS-1, vetorVendas, vetorVendasAuxiliar);

    // Impressão do vetor ordenado
    for (short id = 0; id < QNTBARRACAS; id++) {
        printf("%d", vetorVendas[id]);
    }  

    // Impressão de um ranking para detalhar quais barracas venderam mais
    printf("\n\n****Ranking de vendas****\n");
    for (short id = 0; id < QNTBARRACAS; id++) {
        printf("%d: Barraca %d com %d vendas\n", id+1, rankingVendas(vetorVendas[QNTBARRACAS-id-1]), vetorVendas[QNTBARRACAS-id-1]);
    }  
}