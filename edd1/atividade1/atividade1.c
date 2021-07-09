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