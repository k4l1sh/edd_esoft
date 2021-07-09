/*
A Pilha é uma das estruturas mais simples e mais versáteis dentre as utilizadas na computação. A pilha é uma estrutura em a entrada e a saída de dados se dão pela mesma extremidade, chamada de topo da pilha. São estruturas conhecidas como Last In, First Out (LIFO), que pode ser traduzido por Último a Entrar, Primeiro a Sair. 

OLIVEIRA, Pietro Martins de; Pereira, Rogério de Leon. Estrutura de Dados I.  Maringá-Pr.: Unicesumar, 2019. 

Você recebeu o código parcialmente implementado, conforme o código apresentado acima. Seu gerente de projetos, solicitou que você complete este código incluindo as funções: inclusão de elementos PUSH(), função de exibir o pilha DISPLAY(), função principal MAIN().

Considere que durante a execução o usuário do programa executou as seguintes ações
1 - Executou a função POP(), porém o vetor está vazio. 
2 - Foi executo 3 vezes a função PUSH();
3 - Executou 1 vez a função DISPLAY();

Neste caso específico, descreva o comportamento da pilha mediante a esta sequência de execuções. 
*/

#include<stdio.h>
#include<stdlib.h>
#define tam 10 

struct pilha { 
    int dados[tam]; 
    int ultimo; 
}; 

struct pilha p; 

void pop() { 
    printf("Elemento a ser retirado: %d", p.dados[p.ultimo]);
    p.dados[p.ultimo] = 0;
    p.ultimo--;
    printf("\nPop executado.\n");
} 

void push() {
    int e;
    printf("Escolha um elemento a ser inserido na pilha: ");
    scanf("%d", &e);
    p.ultimo++;
    p.dados[p.ultimo] = e;
    printf("Elemento inserido.");
}

void display() {
    printf("Elementos na pilha: \n");
    for(int i = p.ultimo; i > 0; --i){
        printf("%d\n", p.dados[i]);
    }
}

void main() {
    int escolha;
    while(1) {
        printf("Escolha o que fazer com a pilha\n");
        printf("1 - Display\n2 - Push\n3 - Pop\n4 - Sair\n");
        scanf("%d", &escolha);
        switch(escolha) {
            case 1: display();
            break;
            case 2: push();
            break;
            case 3: pop();
            break;
            case 4: exit(0);
            default: printf("\nEscolha uma alternativa existente");
        }
    }
}