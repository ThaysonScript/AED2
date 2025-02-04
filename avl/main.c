#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(int argc, char *argv[])
{
    int opcao, valor, cresceu;
    node avl = NULL;

    while (1)
    {
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            scanf("%d", &valor);
            avl = inserir(avl, valor, &cresceu);
            break;
        case 2:
            preorder(avl);
            printf("\n");
            break;
        case 3:
            scanf("%d", &valor);
            avl = remover(avl, valor, &cresceu);
            break;
        case 99:
            exit(0);
        }
    }
}