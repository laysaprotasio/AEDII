#include <stdio.h>
#include <stdlib.h>
#include "arvore_RB.h"

arvore no_null;

//funcoes auxiliares

int eh_raiz(arvore elemento) {
	return (elemento->pai == NULL);
}

int eh_filho_esq(arvore elemento){
    return (elemento->pai != NULL && elemento == elemento->pai->esq);
}

int eh_filho_dir(arvore elemento){
    return (elemento->pai != NULL && elemento == elemento->pai->dir);
}

arvore irmao(arvore elemento){
    if(elemento == elemento->pai->esq){
        return elemento->pai->dir;
    } else{
        return elemento->pai->esq;
    }
}

arvore tio(arvore elemento){
    return(irmao(elemento->pai));
}

enum cor cor(arvore elemento){
    enum cor c;

    if(elemento == NULL){
        c = PRETO;
    } else{
        c = elemento->cor;
    }

    return c;
}


//funcoes

void inicializar(arvore *raiz) {
	*raiz = NULL;
	no_null = (arvore) malloc(sizeof(no));
	no_null->cor = DUPLO_PRETO;
	no_null->dado = 0;
    no_null->esq = NULL;
    no_null->dir = NULL;
}


void inserir_rb(int valor, arvore *raiz){

    arvore posicao, pai, novo;

    posicao = *raiz;
    pai = NULL;

    while(posicao != NULL){
        pai = posicao;

        if(valor > posicao->dado){
            posicao = posicao->dir;
        }else{
            posicao = posicao->esq;
        }
    }

    novo = (arvore)malloc(sizeof(no));
    novo->dado = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = pai;
    novo->cor = VERMELHO;

    if(eh_raiz(novo)){
        *raiz = novo;
    } else{
        if(valor > pai->dado){
            pai->dir = novo;
        }else{
            pai->esq = novo;
        }
    }

    ajustar(raiz, novo);

}

void ajustar (arvore *raiz, arvore elemento){

    while(cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO){
        
        //caso 1: Tio VERMELHO ok

        if(cor(tio(elemento)) == VERMELHO){
            tio(elemento)->cor = PRETO;
            elemento->pai->cor = PRETO;
            elemento->pai->pai->cor = VERMELHO;

            elemento = elemento->pai->pai;

            continue;
        }

        //caso 2a: rotação simples a direita ok
        if(eh_filho_esq(elemento) && eh_filho_esq(elemento->pai)){
            rotacao_simples_dir(raiz, elemento->pai->pai);
            elemento->pai->cor = PRETO;
            irmao(elemento)->cor = VERMELHO;
            
            continue;
        }

        //caso 2b: rotação simples a esquerda ok
        if(eh_filho_dir(elemento) && eh_filho_dir(elemento->pai)){
            rotacao_simples_esq(raiz, elemento->pai->pai);
            elemento->pai->cor = PRETO;
            irmao(elemento)->cor = VERMELHO;

            continue;
        }

        //caso 3a: rotacao dupla a direita
        if(eh_filho_dir(elemento) && eh_filho_esq(elemento->pai)){
            rotacao_simples_esq(raiz, elemento->pai);
            rotacao_simples_dir(raiz, elemento->pai);
            elemento->cor = PRETO;
            elemento->dir->cor = VERMELHO;
        }

        //caso 3b: rotacao dupla a esquerda ok
        if(eh_filho_esq(elemento) && eh_filho_dir(elemento->pai)){
            rotacao_simples_dir(raiz, elemento->pai);
            rotacao_simples_esq(raiz, elemento->pai);
            elemento->cor = PRETO;
            elemento->esq->cor = VERMELHO;
        }

    }

    (*raiz)->cor = PRETO;
}


void rotacao_simples_dir(arvore *raiz, arvore pivo){

    arvore u, t1;
    u = pivo->esq;
    t1 = u->dir;

    int posicao_pivo_esq = eh_filho_esq(pivo);

    //atualizando os ponteiros

    pivo->esq = t1;
    if(t1 != NULL){
        t1->pai = pivo;
    }

    u->dir = pivo;
    u->pai = pivo->pai;
    pivo->pai = u;

    //ligando o resto da arvore a u

    if(eh_raiz(u)){
        *raiz = u;
    }else{
       
        if(posicao_pivo_esq){
        u->pai->esq = u;
        } else{
        u->pai->dir = u;    
        }
    }

}

void rotacao_simples_esq(arvore *raiz, arvore pivo){

    arvore u, t2;
    u = pivo->dir;
    t2 = u->esq;

    int posicao_pivo_esq = eh_filho_esq(pivo);

    //atualizando os ponteiros

    pivo->dir = t2;
    if(t2 != NULL){
        t2->pai = pivo;
    }

    u->esq = pivo;
    u->pai = pivo->pai;
    pivo->pai = u;

    //ligando o resto da arvore a u

    if(eh_raiz(u)){
        *raiz = u;
    }else{
       
        if(posicao_pivo_esq){
        u->pai->esq = u;
        } else{
        u->pai->dir = u;    
        }
    }

}
void pre_order(arvore a){
    if(a != NULL){
        printf("[%d]", a->dado);
        pre_order(a->esq);
        pre_order(a->dir);
    }
}

void in_order(arvore a){
    if(a != NULL){
        in_order(a->esq);
        printf("[%d]", a->dado);
        in_order(a->dir);
    }
}

void pos_order(arvore a){
    if(a != NULL){
        pos_order(a->esq);
        pos_order(a->dir);
        printf("[%d]", a->dado);
    }
}

void remover(int valor, arvore *raiz){
    arvore posicao;
    posicao = *raiz;

     while(posicao != NULL){

        if(valor == posicao->dado){
            //elemento possui 2 filhos
            if(posicao->esq != NULL && posicao->dir != NULL){
                posicao->dado = maior_elemento(posicao->esq);
                remover(posicao->dado, &(posicao->esq));
                break;
            }

            //elemento com apenas 1 filho (direito)
            if(posicao->esq == NULL && posicao->dir != NULL){
                posicao->dir->cor = PRETO;
                posicao->dir->pai = posicao->pai;

                if(eh_raiz(posicao)){
                    *raiz = posicao->dir;
                }else{
                    if(eh_filho_esq(posicao)){
                        posicao->pai->esq = posicao->dir;
                    }else{
                        posicao->pai->dir = posicao->dir;
                    }
                }

                free(posicao);

                break;

            }

            //elemento com apenas 1 filho (esquerdo)
            if(posicao->dir == NULL && posicao->esq != NULL){
                posicao->esq->cor = PRETO;
                posicao->esq->pai = posicao->pai;

                if(eh_raiz(posicao)){
                    *raiz = posicao->esq;
                }else{
                    if(eh_filho_esq(posicao)){
                        posicao->pai->esq = posicao->esq;
                    }else{
                        posicao->pai->dir = posicao->esq;
                    }
                }

                free(posicao);

                break;

            }

            //O elemento não possui filhos
            if(posicao->esq == NULL && posicao->dir == NULL){

                //elemento sendo raiz
                if(eh_raiz(posicao)){
                    *raiz = NULL;
                    free(posicao);
                    break;
                }

                //elemento sendo vermelho
                if(posicao->cor == VERMELHO){
                    if(eh_filho_esq(posicao)){
                        posicao->pai->esq = NULL;
                    }else{
                        posicao->pai->dir = NULL;
                    }

                    free(posicao);
                    break;
                } else{
                    //elemento preto -> substituido pelo duplo preto
                    no_null->cor = DUPLO_PRETO;
                    no_null->pai = posicao->pai;

                    if(eh_filho_esq(posicao)){
                        posicao->pai->esq = no_null;
                    }else{
                        posicao->pai->dir = no_null;
                    }

                    free(posicao);

                    reajustar(raiz, no_null);

                    break;
                }
            }
        }

        if(valor > posicao->dado){
            posicao = posicao->dir;
        }else{
            posicao = posicao->esq;
        }
    }

}

int maior_elemento(arvore raiz) {
	if(raiz == NULL)
		    return -1;
	if(raiz->dir == NULL)
		return raiz->dado;
	else
		return maior_elemento(raiz->dir);
}

void reajustar (arvore *raiz, arvore elemento){

    //caso 1:
    if(eh_raiz(elemento)){
        elemento->cor = PRETO;

        if(elemento == no_null){
            *raiz = NULL;
        }
            
        return;
    } 

    //caso 2:
    if(cor(elemento->pai) == PRETO &&
        cor(irmao(elemento)) == VERMELHO &&
        cor(irmao(elemento)->esq) == PRETO &&
        cor(irmao(elemento)->dir) == PRETO
    ){
        if(eh_filho_esq(elemento)){
            rotacao_simples_esq(raiz, elemento->pai);
        } else{
            rotacao_simples_dir(raiz, elemento->pai);
        }

        elemento->pai->pai->cor = PRETO;
        elemento->pai->cor = VERMELHO;

        reajustar(raiz, elemento);

        return;
    }

    //caso 3:   
    if(cor(elemento->pai) == PRETO &&
        cor(irmao(elemento)) == PRETO &&
        cor(irmao(elemento)->esq) == PRETO &&
        cor(irmao(elemento)->dir) == PRETO
    ){
        elemento->pai->cor = DUPLO_PRETO;
        irmao(elemento)->cor = VERMELHO;
        retira_duplo_preto(raiz, elemento);

        reajustar(raiz, elemento->pai);

        return;
    }

    //caso 4:
    if(cor(elemento->pai) == VERMELHO &&
    cor(irmao(elemento)) == PRETO &&
    cor(irmao(elemento)->esq) == PRETO &&
    cor(irmao(elemento)->dir) == PRETO){
        
        elemento->pai->cor = PRETO;
        irmao(elemento)->cor = VERMELHO;
        retira_duplo_preto(raiz, elemento);

        return;
    }

    //caso 5a:
    if(cor(irmao(elemento)) == PRETO &&
        cor(irmao(elemento)->esq) == VERMELHO &&
        cor(irmao(elemento)->dir) == PRETO &&
        eh_filho_esq(elemento)){
        
        rotacao_simples_dir(raiz, irmao(elemento));

        irmao(elemento)->cor = PRETO;
        irmao(elemento)->dir->cor = VERMELHO;

        reajustar(raiz, elemento);

        return;
    }

    //caso 5b: simetrico
    if(cor(irmao(elemento)) == PRETO &&
        cor(irmao(elemento)->dir) == VERMELHO &&
        cor(irmao(elemento)->esq) == PRETO &&
        eh_filho_dir(elemento)){
        
        rotacao_simples_esq(raiz, irmao(elemento));

        irmao(elemento)->cor = PRETO;
        irmao(elemento)->esq->cor = VERMELHO;

        reajustar(raiz, elemento);

        return;
    }

    //caso 6a:
    if(cor(irmao(elemento)) == PRETO &&
        cor(irmao(elemento)->dir) == VERMELHO &&
        eh_filho_esq(elemento)){        

        rotacao_simples_esq(raiz, elemento->pai);

        elemento->pai->pai->cor = elemento->pai->cor;
        elemento->pai->cor = PRETO;
        tio(elemento)->cor = PRETO;
        retira_duplo_preto(raiz, elemento);

        return;
    }

    //caso 6b:
    if(cor(irmao(elemento)) == PRETO &&
        cor(irmao(elemento)->esq) == VERMELHO &&
        eh_filho_dir(elemento)){        

        rotacao_simples_dir(raiz, elemento->pai);

        elemento->pai->pai->cor = elemento->pai->cor;
        elemento->pai->cor = PRETO;
        tio(elemento)->cor = PRETO;
        retira_duplo_preto(raiz, elemento);

        return;
    }
}

void retira_duplo_preto(arvore *raiz, arvore elemento) {
	if(elemento == no_null){
	    if(eh_filho_esq(elemento)){
			elemento->pai->esq = NULL;
        }else{
			elemento->pai->dir = NULL;
        }
    }else{
		elemento->cor = PRETO;
    }
}