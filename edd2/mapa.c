/*
A feira da madruga do Brás acontece na cidade de São Paulo há anos, atraindo diversos clientes das mais variadas regiões do pais. Um comerciante da feira, tem 8 (oito) barracas, ele quer saber qual destas barracas têm o maior volume de vendas diário. Para isso, ele armazena as quantidade de vendas em um caderno, porém ele soube por intermedio de um dos funcionários que você é um estudante de Engenharia de Software e lhe pediu para automatizar o caderninho.

De acordo com o que você já estudou de programação, preferiu utilizar a estrutura de dados de um vetor para armazenar os dados de vendas diário. Após implementado o comerciante ficou encantado com seu trabalho, entretanto como modo de melhorar a visualização das informações requisitou a você que ordenasse o vetor. Dentre as varias técnicas de ordenação, você escolheu o método Mergesort.

O método Mergesort de ordenação foi criado em 1945 pelo matemático húngaro John Von Newmann. Esta técnica de ordenação utiliza um conceito conhecido por dividir para conquistar, que consiste em dividir um problema complexo em dois problemas menores, e cada um desses sejam divididos novamente em partes menores ainda, recursivamente, até que se encontre uma parte pequena e simples suficiente para que seja resolvido.  

OLIVEIRA, Pietro Martins de; Pereira, Rogério de Leon. Estrutura de Dados I.  Maringá-Pr.: Unicesumar, 2019. 

Com base no exposto, desenvolva um programa em linguagem C que cumpra os seguintes requisitos. 

1. Criar um vetor com 8 posições, representando cada barraca. 

2. Cada posição corresponde a um dígito do seu RA (quantidade de vendas diárias da barraca). 

3. Exibir o vetor preenchido. 

4. Aplique o algoritmo de ordenação Mergesort. 

5. Exiba a quantidade de vendas de cada barraca de modo ordenado. 


​Orientações para realização da Atividade MAPA:
- Realize uma Leitura da Unidade IV do Livro da Disciplina.
- Leia os materiais extras sobre análise ambiental disponíveis no Material da Disciplina.
- Assista ao Vídeo de Orientações gravado pelo professor acessando o link: https://youtu.be/iFflDlX4EJk
- Se certifique de que está encaminhando o arquivo correto no seu Studeo antes de Finalizar, pois não haverá como editar e/ou enviar outro arquivo após a finalização.
- Enviar o código fonte (arquivo.c) nomeando o arquivo com seu nome completo. Exemplo: Erinaldo_Nascimento.c
- Em casos de dúvidas, entre em contato com o seu Professor (a) Mediador (a) pelo Studeo no Fale com o Mediador.
*/

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