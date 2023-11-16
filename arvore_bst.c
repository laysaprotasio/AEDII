// FUNCOES

#include <stdio.h>
#include <stdlib.h>
#include "arvore_bst.h"

arvore inserir(arvore a, int valor){
    if(a == NULL){
        arvore nova = (arvore)malloc(sizeof(no));
        nova->valor = valor;
        nova->dir = NULL;
        nova->esq = NULL;
        a = nova;

        return a;
    } else{
        if(valor > a->valor){
            a->dir = inserir(a->dir, valor);
            return a;
        } else{
            a->esq = inserir(a->esq, valor);
            return a;
        }
    }
  
}

void pre_order(arvore a){
    if(a != NULL){
        printf("[%d]", a->valor);
        pre_order(a->esq);
        pre_order(a->dir);
    }
}

void in_order(arvore a){
    if(a != NULL){
        in_order(a->esq);
        printf("[%d]", a->valor);
        in_order(a->dir);
    }
}

void pos_order(arvore a){
    if(a != NULL){
        pos_order(a->esq);
        pos_order(a->dir);
        printf("[%d]", a->valor);
    }
}

void reverso(arvore a){
    if(a != NULL){
        reverso(a->dir);
        printf("[%d]", a->valor);
        reverso(a->esq);
    }
}

int qtd_par(arvore a){
    int qtd;
    if(a == NULL){
        return 0;
    } else {
        qtd = qtd_par(a->esq);
        qtd = qtd + qtd_par(a->dir);

        if(a->valor %2 == 0){
            qtd = qtd +1;
        }

        return qtd;

    }
}

arvore menor(arvore a){
    while(a && a->esq != NULL){
        a = a->esq;
    }
    return a;   
}

arvore remover(arvore a, int valor){
    if(a == NULL){
        return a;
    }

    if(valor < a->valor){
        a->esq = remover(a->esq, valor);
    } else if(valor > a->valor){
        a->dir = remover(a->dir, valor);
    } else{
        if(a->esq == NULL){
            arvore aux = a->dir;
            free(a);
            return aux;
        } else if (a->esq != NULL){
            arvore aux = a->esq;
            free(a);
            return aux;
        } 
        arvore aux = menor(a->dir);
        a->valor = aux->valor;
        a->dir = remover(a->dir, aux->valor);
    }

    return a;
}

int soma_par(arvore a){
    int soma;
    if(a == NULL){
        return 0;
    } else {
        soma = soma_par(a->esq);
        soma = soma + soma_par(a->dir);

        if(a->valor %2 == 0){
            soma = soma + a->valor;
        }

        return soma;

    }
}
arvore podar_descendentes(arvore a){
    if(a == NULL){
        return NULL;
    }

    podar_descendentes(a->esq);
    podar_descendentes(a->dir);

    free(a);

}

arvore podar(arvore a, int valor){
    if(a == NULL){
        return 0;
    }

    if(valor < a->valor){
        a->esq = podar(a->esq, valor);
    } else if(valor > a->valor){
        a->dir = podar(a->dir, valor);
    } else{


        podar_descendentes(a);
        free(a);

        a = NULL;
    }

    return a;
}

arvore dobro(arvore a){
    if(a != NULL){
        a->valor = (2*a->valor);
        a->esq = dobro(a->esq);
        a->dir = dobro(a->dir);

        return a;
    }
}

int busca(arvore a, int valor){
    if(a == NULL){
        return 0;
    }

    if(valor < a->valor){
        busca(a->esq, valor);
    } else if(valor > a->valor){
        busca(a->dir, valor);
    } else if(valor == a->valor){
        return 1;
    } 
}

void descendentes(arvore a, int valor){
     if(valor < a->valor){
        descendentes(a->esq, valor);
    } else if(valor > a->valor){
        descendentes(a->dir, valor);
    } else if(valor == a->valor){
       in_order(a);
    } 
}


