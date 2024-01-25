#include <stdio.h>
#include <stdlib.h>
#include "arvore_avl.h"

int main()
{

    arvore a = NULL;
    int b = 1;
    
    a = inserir_avl(a, 20, &b);
    a = inserir_avl(a, 10, &b);
    a = inserir_avl(a, 15, &b);
    a = inserir_avl(a, 9, &b);
    a = inserir_avl(a, 18, &b);
    a = inserir_avl(a, 30, &b);
    a = inserir_avl(a, 40, &b);
    a = inserir_avl(a, 7, &b);
    a = inserir_avl(a, 26, &b);
    a = inserir_avl(a, 28, &b);
    a = inserir_avl(a, 50, &b);
    a = inserir_avl(a, 12, &b);

    a = remover_avl(a, 28, &b);
    
    

    pre_order_avl(a);

    return 0;
    
}
