#include "JVIDA_JJVR_Model.c"
#include "JVIDA_JJVR_View.c"

void jogoDaVida();
void geraMundo();
void apresentaMundo();
void selecionaVivos();
void limpaMundo();

void jogoDaVida()
{
    int o;
    while(o!=0)
    {
        o=menu();
        switch(o)
        {
            case 1:
                geraMundo();
                break;

            case 2:
                selecionaVivos();
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
                limpaMundo();
                break;

            case 0:
                break;

        }
    }
}

void apresentaMundo()
{
    int i, k;

    printf("\t");
    for(i=1;i<=mundo.tam;i++)
        printf("%d\t", i);
    printf("\n");
    
    for(i=1;i<=mundo.tam;i++)
    {
        printf("%d\t", i);
        for(k=0;k<mundo.tam;k++)
        {
            if(mundo.status[i][k]=='M') //morto
                printf(".\t");
            else if(mundo.status[i][k]=='V') //vivo
                printf("o\t");
        }
        printf("\n");
    }
}


void geraMundo()
{
    int i, k;

    do
    {
        printf("Escolha o tamanho do mundo (maximo: 100): ");
        scanf("%d", &mundo.tam);
    }while(mundo.tam<1 || mundo.tam>100);

    for(i=1;i<=mundo.tam;i++)
    {
        for(k=0;k<mundo.tam;k++)
            mundo.status[i][k]='M';
    }
    apresentaMundo();
}

void selecionaVivos()
{
    int vivasInicio, aux1, aux2, i, k;

	do
    {
        printf("Quantas celulas vivas voce vai querer colocar no mundo?: ");
	    scanf("%d",&vivasInicio);
    }while(vivasInicio<1);
	printf("\n");

	for(i=1;i<=vivasInicio;i++)
    {
        aux1=0;
        aux2=0;
        printf("Selecione a coordenada da celula viva #%d: ",i);
        scanf("%d %d",&aux1, &aux2);
        mundo.status[aux1][aux2-1]='V';
        printf("\n");
    }
    apresentaMundo();
}

void limpaMundo()
{
    int aux, i, j;

    printf("Voce quer limpar o mundo? Sim:1 / Nao:2\n");
	scanf("%d",&aux);
	if(aux==1)
    {
        for(i=0;i<=mundo.tam;i++)
        {
            for(j=0;j<=mundo.tam;j++)
                mundo.status[i][j] = 'M';
        }
        apresentaMundo();
    }
}
