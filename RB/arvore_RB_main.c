#include <stdio.h>
#include <stdlib.h>
#include "arvore_RB.h"

int main(){
    arvore a;
    inicializar(&a);

    inserir_rb(10, &a);
    inserir_rb(20, &a);
    inserir_rb(5, &a);
    inserir_rb(22, &a);
    inserir_rb(15, &a);
    inserir_rb(2, &a);
    inserir_rb(9, &a);
    inserir_rb(18, &a);
    inserir_rb(30, &a);
    inserir_rb(1, &a);
    inserir_rb(40, &a);
    inserir_rb(35, &a);
    inserir_rb(25, &a);
    inserir_rb(8, &a);
    inserir_rb(4, &a);

    remover(30, &a);
    remover(10, &a);
    remover(8, &a);
    remover(22, &a);
    remover(18, &a);
    remover(15, &a);
   
    pre_order(a);




    return 0;
}