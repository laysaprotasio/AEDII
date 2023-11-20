#ifndef ARVORE_BST_H
#define ARVORE_BST_H

typedef struct no{
    int valor;
    struct no* esq;
    struct no* dir;
} no;

typedef no* arvore;

arvore inserir(arvore a, int valor);
void pre_order(arvore a);
void in_order(arvore a);
void pos_order(arvore a);
void reverso(arvore a);
int qtd_par(arvore a);
int soma_par(arvore a);
arvore dobro(arvore a);
arvore menor(arvore a);
arvore remover(arvore a, int valor);
arvore podar_descendentes(arvore a);
arvore podar(arvore a, int valor);
int busca(arvore a, int valor);
arvore buscar(arvore a, int valor);
void descendentes(arvore a, int valor);
int altura(arvore a);
arvore pai(arvore a, int valor);
void imprimir_pai(arvore a, int valor);
arvore encontrar_antecessor(arvore a, int valor);
void imprimir_antecessor(arvore a, int valor);

#endif