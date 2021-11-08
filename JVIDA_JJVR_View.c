int menu();//menu principal
void apresentaMundo();//funcao que apresenta como o mundo esta atualmente
int quantasGeracoes();//pergunta ao usuario quantas geracoes ocorrerao
int quantoTempo();//pergunta ao usuario quanto tempo (em segundos) havera entre cada geracao

int menu()//menu principal
{
    int x;
    printf("\t  JOGO DA VIDA\n");
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

    printf("    ");
    for(i=1;i<=tam;i++)//enumera as colunas
        printf("%d  ", i);
    printf("\n");

    for(i=1;i<=tam;i++)
    {
        printf("%2.d  ", i);//enumera as linhas
        for(k=1;k<=tam;k++)
        {
            if(matriz[i][k]=='M') //morto
                printf(".  ");
            else if(matriz[i][k]=='V') //vivo
                printf("o  ");
        }
        printf("\n");
    }
}

int quantasGeracoes()//pergunta ao usuario quantas geracoes ocorrerao
{
    int x;
    printf("Quantas geracoes voce deseja que ocorram? ");
    scanf("%d", &x);
    printf("\n");
    return x;
}

int quantoTempo()//pergunta ao usuario quanto tempo (em segundos) havera entre cada geracao
{
    int x;
    printf("Quanto tempo de intervalo voce deseja entre cada geracao? ");
    scanf("%d", &x);
    return x;
}
