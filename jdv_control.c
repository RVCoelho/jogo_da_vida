#include "JVIDA_JJVR_Model.c"
#include "JVIDA_JJVR_View.c"

void jogoDaVida();
void geraMundo();
void selecionaVivos();
void limpaMundo();

void jogoDaVida()
{
    int o;
    while(o!=0) //loop que faz o jogo funcionar
    {
        o=menu(); //numero da opcao selecionada que sera usada no switch
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


void geraMundo()//funcao que gera o mundo inicial
{
    int i, k;

    do
    {
        printf("Escolha o tamanho do mundo (maximo: 100): ");
        scanf("%d", &tam);
    }while(tam<1 || tam>100);//nao permite valores sem sentido ou acima do valor maximo permitido

    for(i=1;i<=tam;i++)
    {
        for(k=0;k<tam;k++)
            matriz[i][k]='M';
    }
    apresentaMundo();
}

void selecionaVivos()//
{
    int vivasInicio, aux1, aux2, i, k;
    Lvivos.cont=0;
    i=Lvivos.cont;
	do
    {
        printf("Quantas celulas vivas voce vai querer colocar no mundo?: ");
	    scanf("%d",&vivasInicio);
    }while(vivasInicio<1);//nao permite valores sem sentido
	printf("\n");
    
	for(i=0;i<vivasInicio;i++)
    {
        aux1=0;
        aux2=0;
        printf("Selecione a coordenada da celula viva #%d: ",i+1);
        scanf("%d %d",&aux1, &aux2);
        Lvivos.Celula[i+1].lin = aux1;
        Lvivos.Celula[i+1].col = aux2;
        Lvivos.cont++;
        matriz[aux1][aux2]='V';
        printf("\n");
    }
    apresentaMundo();
}

void limpaMundo()//funcao que torna todas as celulas mortas
{
    int aux, i, j;

    printf("Voce quer limpar o mundo? Sim:1 / Nao:2\n");
	scanf("%d",&aux);
	if(aux==1)
    {
        for(i=0;i<=tam;i++)
        {
            for(j=0;j<=tam;j++)
                matriz[i][j] = 'M';
            Lvivos.Celula[i+1].lin = 0;
            Lvivos.Celula[i+1].col = 0;
            Lvivos.cont=0;
        }
        apresentaMundo();
    }
}
