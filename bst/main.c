#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main(int argc, char const *argv[])
{
    int escolha, num;
    node arvore = NULL;

    while (1)
    {
        scanf("%d", &escolha);
        switch (escolha)
        {
        case 1:
            scanf("%d", &num);
            arvore = inserir(num, arvore);
            break;

        case 2:
            preorder(arvore);
            printf("\n");
            break;

        case 3:
            inorder(arvore);
            printf("\n");
            break;

        case 4:
            posorder(arvore);
            printf("\n");
            break;

        case 5:
            reverso(arvore);
            break;

        case 6:
            printf("%d\n", altura(arvore));
            break;

        case 7:
            printf("%d\n", qtdFolhas(arvore));
            break;

        case 8:
            scanf("%d", &num);
            caminho(arvore, num);
            break;

        case 9:
            scanf("%d", &num);
            remover(num, arvore);
            break;

        case 99:
            return 0;
        }
    }
}