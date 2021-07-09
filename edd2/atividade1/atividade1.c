#include <stdio.h>
#include <stdlib.h>

// Estrutura de uma árvore binária
struct no {
    int valor;
    struct no *esquerda, *direita;
};
 
// Função responsável pela inserção de novos elementos
// Na função, occore a alocação de memória para um novo nó e atribuição do valor passado por argumento, bem como o valor NULL para os nós subsequentes
struct no* novoNo(int valor) {
    struct no* no = (struct no*) malloc(sizeof(struct no));
    no->esquerda = NULL;
    no->direita = NULL;
    no->valor = valor;
    return no;
}

// Função responsável por imprimir a árvore binária
// Cada nível de nós é separado por \t's, enquanto os elementos do mesmo nível são separados por \n's
// Portanto, os elementos da direita são expressos em cima e os elementos da esquerda são expressos embaixo
void visualizar(struct no *raiz, int esp) {
    if(raiz == NULL) {
        return;
    }
    esp += 1;
    visualizar(raiz->direita, esp);
    printf("\n");
    for(size_t i = 1; i < esp; ++i) {
        printf("\t");
    }
    printf("%d\n", raiz->valor);
    visualizar(raiz->esquerda, esp);
}


// Função principal aonde a inicialização da árvore binária ocorre junto com a inserção dos nós
void main() {
    struct no* raiz = novoNo(7);
    raiz->direita = novoNo(52);
    raiz->direita->direita = novoNo(57);
    raiz->direita->direita->direita = novoNo(89);
    raiz->direita->esquerda = novoNo(54);
    raiz->esquerda = novoNo(26);
    raiz->esquerda->esquerda = novoNo(20);
    raiz->esquerda->direita = novoNo(23);
    visualizar(raiz, 0);
    getchar();
}

/*
A chamada da função visualizar() para os nós inseridos acima irá imprimir a seguinte árvore binária:

                        89

                57

        52

                54

7

                23

        26

                20
*/
