// FUNCOES

#include <stdio.h>
#include <stdlib.h>
#include "arvore_avl.h"

arvore rotacao_simples_direita(arvore raiz){ // testada

    //inicializando
    arvore p, u, t1, t2, t3;
    
    p = raiz;
    u = raiz->esq;
    t2 = raiz->esq->dir;
 

    //atuallizando os ponteiros

    p->esq = t2;
    u->dir = p;

    return u;
}

arvore rotacao_simples_esquerda(arvore raiz){ // testada
    
    //inicializando
    arvore p, u, t1, t2, t3;
    
    p = raiz;
    u = raiz->dir;
    t2 = raiz->dir->esq;
    

    //atuallizando os ponteiros

    p->dir = t2;
    u->esq = p;

    return u;
}

arvore rotacao_dupla_direita(arvore raiz){
    raiz->esq = rotacao_simples_esquerda(raiz->esq);
    raiz = rotacao_simples_direita(raiz);

    return raiz;
}

arvore rotacao_dupla_esquerda(arvore raiz){
    raiz->dir = rotacao_simples_direita(raiz->dir);
    raiz = rotacao_simples_esquerda(raiz);

    return raiz;
}

arvore rotacionar(arvore raiz){

    arvore aux;

    if(raiz->fb > 0){
        switch(raiz->dir->fb){
            case 0:
            case 1:
                aux = rotacao_simples_esquerda(raiz);

                //atualizacao dos fatores de balanco
                if(aux->fb == 0){
                    aux->fb = -1;
                    aux->esq->fb = 1;
                } else{
                    aux->fb = 0;
                    aux->esq->fb = 0;
                }

            return aux;
            case -1:
                aux = rotacao_dupla_esquerda(raiz);
                
                //atualizacao dos fatores de balanco
                switch(aux->fb){
                    case -1:
                        aux->fb = 0;
                        aux->dir->fb = 1;
                        aux->esq->fb = 0;
                        break;

                    case 0:
                        aux->fb = 0;
                        aux->dir->fb = 0;
                        aux->esq->fb = 0;
                        break;

                    case 1: // testada
                        aux->fb = 0;
                        aux->dir->fb = 0;
                        aux->esq->fb = -1;
                        break;
                }
                

            return aux;
        }
    } else{
        switch(raiz->esq->fb){
            case 0:
            case -1:
                aux = rotacao_simples_direita(raiz);

                //atualizacao do fator de balanco
                if(aux->fb == 0){
                    aux->fb = 1;
                    aux->dir->fb= -1;
                } else{
                    aux->fb = 0;
                    aux->dir->fb = 0;
                }

            return aux;

            case 1:
                aux = rotacao_dupla_direita(raiz);

                //atualizacao do fator de balanco
                switch(aux->fb){
                    case -1:
                    aux->fb = 0;
                    aux->dir->fb = 1;
                    aux->esq->fb = 0;
                    break;

                    case 0: // testada
                    aux->fb = 0;
                    aux->dir->fb = 0;
                    aux->esq->fb = 0;
                    break;

                    case 1:
                    aux->fb = 0;
                    aux->dir->fb = 0;
                    aux->esq->fb = -1;
                    break;
                }
            
            return aux;
        }
    }


}

arvore inserir_avl(arvore raiz, int valor, int *cresceu){
    if(raiz == NULL){
        arvore nova = (arvore)malloc(sizeof(no));
        nova->valor = valor;
        nova->dir = NULL;
        nova->esq = NULL;
        nova->fb = 0;
        *cresceu = 1;
        
        return nova;
    } else{
        if(valor > raiz->valor){
            raiz->dir = inserir_avl(raiz->dir, valor, cresceu);

            if(*cresceu == 1){
                switch(raiz->fb){
                    case 0:
                    raiz->fb = 1;
                    *cresceu = 1;
                    break;

                    case -1: 
                    raiz->fb = 0;
                    *cresceu = 0;
                    break;

                    case 1:
                    *cresceu = 0;
                    return rotacionar(raiz);
    
                }
            }
        } else{
            raiz->esq = inserir_avl(raiz->esq, valor, cresceu);

            if(*cresceu == 1){
                switch(raiz->fb){
                    case 0:
                    raiz->fb = -1;
                    *cresceu = 1;
                    break;

                    case 1:
                    raiz->fb = 0;
                    *cresceu = 0;
                    break;

                    case -1:
                    *cresceu = 0;
                    return rotacionar(raiz);
                }
            }
        }
        return raiz;
    }
}


arvore remover_avl(arvore raiz, int valor, int *diminuiu){
    if(raiz == NULL){
        *diminuiu = 0;
        return NULL;
    }

    if(raiz->valor == valor){

        *diminuiu = 1;

        if(raiz->esq == NULL && raiz->dir == NULL){
            free(raiz);
            return NULL;

        } else if(raiz->esq == NULL && raiz->dir != NULL){
            arvore aux = raiz->dir;
            free(raiz);
            return aux;
        } else if (raiz->esq != NULL && raiz->dir == NULL){
            arvore aux = raiz->esq;
            free(raiz);
            return aux;
        }else{
            arvore aux = maior_avl(raiz->esq);
            raiz->valor = aux->valor;
            raiz->esq = remover_avl(raiz->esq, aux->valor, diminuiu);
        }

    } else{
        
        if(valor > raiz->valor){
            raiz->dir = remover_avl(raiz->dir, valor, diminuiu);

            if(*diminuiu == 1){
                switch(raiz->fb){
                    case 0:
                    raiz->fb = -1;
                    *diminuiu = 0;
                    break;

                    case -1: 
                    raiz = rotacionar(raiz);

                    case 1:
                    raiz->fb = 0;
                    *diminuiu = 1;
                    break;
    
                }
            }

        } else{
            raiz->esq = remover_avl(raiz->esq, valor, diminuiu);

            if(*diminuiu == 1){
                switch(raiz->fb){
                    case 0:
                    raiz->fb = 1;
                    *diminuiu = 0;
                    break;

                    case -1: 
                    raiz->fb = 0;
                    *diminuiu = 1;
                    break;

                    case 1:
                    raiz = rotacionar(raiz);
    
                }
            }
        }
    }

    return raiz;
}

arvore maior_avl(arvore raiz){
    while(raiz && raiz->dir != NULL){
        raiz = raiz->dir;
    }
    return raiz;   
}

void pre_order_avl(arvore a){
    if(a != NULL){
        printf("[%d]", a->valor);
        pre_order_avl(a->esq);
        pre_order_avl(a->dir);
    }
}

void in_order_avl(arvore a){
    if(a != NULL){
        in_order_avl(a->esq);
        printf("[%d]", a->valor);
        in_order_avl(a->dir);
    }
}

void pos_order_avl(arvore a){
    if(a != NULL){
        pos_order_avl(a->esq);
        pos_order_avl(a->dir);
        printf("[%d]", a->valor);
    }
}
