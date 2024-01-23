#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

typedef struct no{
    int valor;
    int fb;
    struct no* esq;
    struct no* dir;
} no;

typedef no* arvore;

arvore inserir_avl(arvore a, int valor, int *cresceu);
arvore rotacao_simples_direita(arvore raiz);
arvore rotacao_simples_esquerda(arvore raiz);
arvore rotacao_dupla_direita(arvore raiz);
arvore rotacao_dupla_esquerda(arvore raiz);
arvore rotacionar(arvore raiz);
void pre_order_avl(arvore a);
void in_order_avl(arvore a);
void pos_order_avl(arvore a);

#endif