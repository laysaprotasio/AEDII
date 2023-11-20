#include <stdio.h>
#include <stdlib.h>
#include "arvore_bst.h"

int main()
{

    arvore a = NULL;
    int opcao;
    int valor, retorno;

    while (opcao != 99)
    {
        printf("Selecione uma das opcoes a seguir:\n"
               "1 - Para inserir na arvore\n"
               "2 - Para exibir preorder\n"
               "3 - Para exibir inorder\n"
               "4 - Para exibir por_order\n"
               "5 - Para exibir reverso\n"
               "6 - Para saber a quantidade de elementos pares\n"
               "7 - Para saber o antecessor de um valor\n"
               "8 - Para saber o pai de um valor\n"
               "9 - Para remover um valor da arvore\n"
               "10 - Para saber a soma dos elementos pares\n"
               "11 - Para podar a arvore\n"
               "12 - Para dobrar os valores da arvore\n"
               "13 - Para buscar um valor na arvore\n"
               "14 - Para imprimir os descendentes de um numero\n"
               "15 - Para saber a altura da arvore\n"
               "99 - Para sair do programa\n");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o valor para ser inserido na arvore:\n");
            scanf("%d", &valor);
            a = inserir(a, valor);
            break;

        case 2:
            pre_order(a);
            printf("\n");
            break;

        case 3:
            in_order(a);
            printf("\n");
            break;

        case 4:
            pos_order(a);
            printf("\n");
            break;

        case 5:
            reverso(a);
            printf("\n");
            break;
        case 6:
            valor = qtd_par(a);
            printf("[%d]\n", valor);
            break;
        case 7:
            printf("Digite o valor para saber seu antecessor:\n");
            scanf("%d", &valor);
            imprimir_antecessor(a, valor);
            break;
        case 8:
            printf("Digite o valor saber seu pai:\n");
            scanf("%d", &valor);
            imprimir_pai(a, valor);
            break;
        case 9:
            printf("Digite o valor para ser removido da arvore:\n");
            scanf("%d", &valor);
            a = remover(a, valor);
            break;
        case 10:
            valor = soma_par(a);
            printf("[%d]\n", valor);
            break;
        case 11:
            printf("Digite o valor para podar a arvore:\n");
            scanf("%d", &valor);
            a = podar(a, valor);
            break;
        case 12:
            dobro(a);
            in_order(a);
            printf("\n");
            break;
        case 13:
            printf("Digite o valor para ser buscado na arvore:\n");
            scanf("%d", &valor);
            retorno = busca(a, valor);

            if(retorno == 1){
                printf("1 - O valor foi encontrado\n");
            } else if (retorno == 0){
                printf("0 - O valor nao foi encontrado\n");
            }

            break;
        case 14:
            printf("Digite o valor para que sejam printados seus descendentes:\n");
            scanf("%d", &valor);
            descendentes(a, valor);
            printf("\n");

            break;
        case 15:
            valor = altura(a);
            printf("A altura e [%d]\n", valor);

        case 99:
            printf("Saindo...");
            break;

        default:
            printf("valor indeterminado\n");
            break;
        }
    }

    return 0;
}