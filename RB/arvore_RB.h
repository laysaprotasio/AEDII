#ifndef ARVORE_AVL_H
#define ARVORE_AVL_H

enum cor {
    VERMELHO,
    PRETO,
    DUPLO_PRETO,
};

typedef int tipo_dado;

typedef struct no{

    tipo_dado dado;
    struct no *esq;
    struct no *dir;
    struct no *pai;
    enum cor cor;
} no;

typedef no* arvore;

int eh_raiz(arvore elemento);
int eh_filho_esq(arvore elemento);
int eh_filho_dir(arvore elemento);
arvore irmao(arvore elemento);
arvore tio(arvore elemento);
enum cor cor(arvore elemento);
void inicializar(arvore *raiz);
void inserir_rb(int valor, arvore *raiz);
void ajustar (arvore *raiz, arvore elemento);   
void rotacao_simples_dir(arvore *raiz, arvore pivo);
void rotacao_simples_esq(arvore *raiz, arvore pivo);
void pre_order(arvore a);
void in_order(arvore a);
void pos_order(arvore a);
void retira_duplo_preto(arvore *raiz, arvore elemento);
void reajustar (arvore *raiz, arvore elemento);
int maior_elemento(arvore raiz);
void remover(int valor, arvore *raiz);
#endif
