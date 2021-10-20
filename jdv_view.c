int menu();
void apresentaMundo();

int menu()
{
    int x;
    printf("    JOGO DA VIDA\n");
    printf("---------------------------------\n");
    printf("1 - Criar um novo mundo\n");
    printf("2 - Preparar e salvar um mundo inicial\n");
    printf("3 - Iniciar o mundo\n");
    printf("4 - Mostrar o mundo final apos o processo\n");
    printf("5 - Limpar o mundo\n");
    printf("0 - Sair\n");
    printf("Selecione uma opcao dos numeros acima: ");
    scanf("%d",&x);
    printf("\n");
    return x;
}

void apresentaMundo() //funcao que apresenta como o mundo esta atualmente
{
    int i, k;

    printf("\t");
    for(i=1;i<=tam;i++)//enumera as colunas
        printf("%d\t", i);
    printf("\n");

    for(i=1;i<=tam;i++)
    {
        printf("%d\t", i);//enumera as linhas
        for(k=1;k<=tam;k++)
        {
            if(matriz[i][k]=='M') //morto
                printf(" \t");
            else if(matriz[i][k]=='V') //vivo
                printf("o\t");
        }
        printf("\n");
    }
    
}
