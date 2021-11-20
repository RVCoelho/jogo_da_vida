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
    printf("4 - Mostrar o mundo atual\n");
    printf("5 - Limpar o mundo\n");
    printf("0 - Sair\n");
    printf("Selecione uma opcao dos numeros acima: ");
    scanf("%d",&x);
    printf("\n");
    return x;
}

void apresentaMundo() //funcao que apresenta como o mundo esta atualmente
{
    int i, j, k, ii, jj;

    for(i=1;i<=tam;i++)//corre e limpa a matriz inteira
    {
        for(j=1;j<=tam;j++)
        {
            matriz[i][j]='.';
        }
    }
    for(i=0;i<=Lvivos.cont;i++)
    {
        ii=Lvivos.Celula[i].lin;
        jj=Lvivos.Celula[i].col;
        matriz[ii][jj]='O';
    }

    printf("    ");
    for(i=1;i<=tam;i++)//enumera as colunas
        if(i<10)
            printf("%d  ", i);
        else
            printf("%d ", i);
    printf("\n");

    for(i=1;i<=tam;i++)//apresenta a matriz
    {
        printf("%2.d  ", i);//enumera as linhas
        for(j=1;j<=tam;j++)
        {
            printf("%c  ", matriz[i][j]);
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
