#include <stdio.h>
#include <stdlib.h>
#include "arvore_avl.h"

int main()
{

    arvore a = NULL;
    int b = 1;
    
    a = inserir_avl(a, 10, &b);
    a = inserir_avl(a, 15, &b);
    a = inserir_avl(a, 20, &b);
    a = inserir_avl(a, 5, &b);
    a = inserir_avl(a, 8, &b);
    a = inserir_avl(a, 25, &b);
    a = inserir_avl(a, 22, &b);
    a = inserir_avl(a, 24, &b);
    a = inserir_avl(a, 26, &b);
    a = inserir_avl(a, 23, &b);
    

    pre_order_avl(a);

    return 0;
    
}