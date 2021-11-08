#include "JVIDA_JJVR_Model.c"
#include "JVIDA_JJVR_View.c"

void jogoDaVida();//funcao que contem o loop principal do jogo
void geraMundo();//funcao que gera o mundo inicial
void selecionaVivos();//funcao que da ao operador a opcao de selecionar quais celulas ficarao vivas na primeira geracao
void limpaMundo();//funcao que torna todas as celulas mortas
void detectaVizinhos();//funcao que detecta os vizinhos mortos e vizinhos vivos das celulas vivas
void proximaGeracao();//funcao que determina o status (vivo ou morto) de cada celula na proxima geracao
int jaExisteM(int ii,int jj);//funcao que verifica se se a celula (ii,jj) ja esta na lista
void contaVizinhosVdeM();//conta os vizinhos vivos de celulas mortas
void proximaGeracao();//funcao que determina o status (vivo ou morto) de cada celula na proxima geracao
void detectaVizinhosMP();//funcao que detecta mortos vizinhos da proxima geracao
int jaExisteMP(int ii,int jj);//funcao que verifica se se a celula (ii,jj) ja esta na lista

void jogoDaVida()//funcao que contem o loop principal do jogo
{
    int o=1, p, i=1, q;
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
                detectaVizinhos();
                contaVizinhosVdeM();
                break;

            case 3:
                p=quantasGeracoes();
                q=quantoTempo();
                while(i<=p)
                {
                    proximaGeracao();
                    apresentaMundo();
                    sleep(q);
                    i++;
                }
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

    for(i=1;i<=tam;i++)//todas as celulas terao status de morto no inicio
    {
        for(k=1;k<=tam;k++)
            matriz[i][k]='M';
    }
    apresentaMundo();
}

void selecionaVivos()//funcao que da ao operador a opcao de selecionar quais celulas ficarao vivas na primeira geracao
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
    
	for(i=1;i<=vivasInicio;i++)
    {
        aux1=0;
        aux2=0;
        printf("Selecione a coordenada da celula viva #%d: ",i);
        scanf("%d %d",&aux1, &aux2);
        Lvivos.Celula[i].lin = aux1;//define a coordenada linha
        Lvivos.Celula[i].col = aux2;//define a coordenada coluna
        Lvivos.cont++;//enumera quantas celulas estao vivas atualmente na lista
        matriz[aux1][aux2]='V';//define a celula como viva
        printf("\n");
    }
    apresentaMundo();

    printf("Lista das celulas vivas = %d: ", Lvivos.cont);
    for(i=0;i<Lvivos.cont;i++) //apresenta as coordenadas das celulas vivas
    {
        printf("(%d,%d)", Lvivos.Celula[i+1].lin, Lvivos.Celula[i+1].col);
    }
    printf("\n");
}

void limpaMundo()//funcao que torna todas as celulas mortas
{
    int aux, i, j;

    printf("Voce quer limpar o mundo? Sim:1 / Nao:2\n");
	scanf("%d",&aux);
	if(aux==1)
    {
        for(i=1;i<=tam;i++)//corre e limpa a matriz inteira
        {
            for(j=1;j<=tam;j++)
                matriz[i][j] = 'M';
            //limpa o valor de cada elemento da lista e zera o contador
            Lvivos.Celula[i].lin = 0;
            Lvivos.Celula[i].col = 0;
            Lvivos.cont=0;
        }
        apresentaMundo();
    }
}

void detectaVizinhos()//funcao que detecta os vizinhos mortos e vizinhos vivos das celulas vivas
{
    int i, j, k=0, m=0, l, aux;
    
    LmortosV.cont=0;
    for(i=0;i<=tam;i++)//limpando o valor de todas as coordenadas do array
    {
        for(j=0;j<=tam;j++)
            vizinhosV[i][j]=0;
    }
    for(i=Lvivos.Celula[0].lin;i<=tam;i++)//detectar vizinhos vivos
    {
        for(j=Lvivos.Celula[0].col;j<=tam;j++)
        {
            if(matriz[i][j]=='V')//apenas checara se ha vizinhos se a celula estiver viva
            {
                if(matriz[i-1][j-1]=='V')// checa uma linha acima e uma coluna a esquerda
                    vizinhosV[i][j]++;
                if(matriz[i-1][j]=='V')//checa uma linha acima
                    vizinhosV[i][j]++;
                if(matriz[i-1][j+1]=='V')//checa uma linha acima e uma coluna a direita
                    vizinhosV[i][j]++;
                if(matriz[i][j-1]=='V')//checa uma coluna a esquerda
                    vizinhosV[i][j]++;
                if(matriz[i][j+1]=='V')//checa uma coluna a direita
                    vizinhosV[i][j]++;
                if(matriz[i+1][j-1]=='V')//checa uma linha abaixo e uma coluna a esquerda
                    vizinhosV[i][j]++;
                if(matriz[i+1][j]=='V')//checa uma linha abaixo
                    vizinhosV[i][j]++;
                if(matriz[i+1][j+1]=='V')//checa uma linha abaixo e uma coluna a direita
                    vizinhosV[i][j]++;
            }
        }
    }
    printf("\n");
    for(i=0;i<=tam;i++)//limpando o valor de todas as coordenadas do array
    {
        for(j=0;j<=tam;j++)
            vizinhosMP[i][j]=0;
    }
    for(i=Lvivos.Celula[0].lin;i<=tam;i++)//detectar vizinhos mortos
    {
        for(j=Lvivos.Celula[0].col;j<=tam;j++)
        {
            for(k=0;k<=Lvivos.cont;k++)//for para correr os elementos da lista Lvivos
            {
                if(i==Lvivos.Celula[k].lin && j==Lvivos.Celula[k].col && i!=0 && j!=0)//apenas checara se houver vizinhos se a celula estiver viva
                {
                    if(matriz[i-1][j-1]=='M' && i-1!=0 && j-1!=0)// checa uma linha acima e uma coluna a esquerda
                    {// as condições "&& i-1!=0" e "&& j-1!=0" para que não sejam checadas as coordenadas com 0 no array
                        vizinhosM[i][j]++;
                        for(l=0;l<=Lvivos.cont;l++)//corre a lista novamente para checar se a coordenada atual ja esta ou nao nessa lista
                        {
                            if(jaExisteM(i-1,j-1)==0)//so adicionara a coordenada se ela nao existir na lista
                            {
                                LmortosV.Celula[m].lin=i-1;
                                LmortosV.Celula[m].col=j-1;
                                LmortosV.cont++;
                                m++;//aumenta o valor de m para que cada atribuicao seja em uma celula diferente da lista
                                aux=m;
                                break;
                            }
                            else if(aux==m)//continua o loop caso o m esteja com o mesmo valor de antes
                                continue;
                            else//para o loop caso o m tenha aumentado o seu valor
                                break;
                        }
                    }
                    if(matriz[i-1][j]=='M' && i-1!=0)//checa uma linha acima
                    {
                        vizinhosM[i][j]++;
                        for(l=0;l<=vizinhosM[i][j];l++)//corre a lista novamente para checar se a coordenada atual ja esta ou nao nessa lista
                        {
                            if(jaExisteM(i-1,j)==0)//so adicionara coordenada se ela nao existir na lista
                            {
                                LmortosV.Celula[m].lin=i-1;
                                LmortosV.Celula[m].col=j;
                                LmortosV.cont++;
                                m++;//aumenta o valor de m para que cada atribuicao seja em uma celula diferente da lista
                                aux=m;
                                break;
                            }
                            else if(aux==m)//continua o loop caso o m esteja com o mesmo valor de antes
                                continue;
                            else//para o loop caso o m tenha aumentado o seu valor
                                break;
                        }
                    }
                    if(matriz[i-1][j+1]=='M' && i-1!=0)//checa uma linha acima e uma coluna a direita
                    {
                        vizinhosM[i][j]++;
                        for(l=0;l<=vizinhosM[i][j];l++)//corre a lista novamente para checar se a coordenada atual ja esta ou nao nessa lista
                        {
                            if(jaExisteM(i-1,j+1)==0)//so adicionara coordenada se ela nao existir na lista
                            {
                                LmortosV.Celula[m].lin=i-1;
                                LmortosV.Celula[m].col=j+1;
                                LmortosV.cont++;
                                m++;//aumenta o valor de m para que cada atribuicao seja em uma celula diferente da lista
                                aux=m;
                                break;
                            }
                            else if(aux==m)//continua o loop caso o m esteja com o mesmo valor de antes
                                continue;
                            else//para o loop caso o m tenha aumentado o seu valor
                                break;
                        }
                    }
                    if(matriz[i][j-1]=='M' && j-1!=0)//checa uma coluna a esquerda
                    {
                        vizinhosM[i][j]++;
                        for(l=0;l<=vizinhosM[i][j];l++)//corre a lista novamente para checar se a coordenada atual ja esta ou nao nessa lista
                        {
                            if(jaExisteM(i,j-1)==0)//so adicionara coordenada se ela nao existir na lista
                            {
                                LmortosV.Celula[m].lin=i;
                                LmortosV.Celula[m].col=j-1;
                                LmortosV.cont++;
                                m++;//aumenta o valor de m para que cada atribuicao seja em uma celula diferente da lista
                                aux=m;
                                break;
                            }
                            else if(aux==m)//continua o loop caso o m esteja com o mesmo valor de antes
                                continue;
                            else//para o loop caso o m tenha aumentado o seu valor
                                break;
                        }
                    }
                    if(matriz[i][j+1]=='M')//checa uma coluna a direita
                    {
                        vizinhosM[i][j]++;
                        for(l=0;l<=vizinhosM[i][j];l++)//corre a lista novamente para checar se a coordenada atual ja esta ou nao nessa lista
                        {
                            if(jaExisteM(i,j+1)==0)//so adicionara coordenada se ela nao existir na lista
                            {
                                LmortosV.Celula[m].lin=i;
                                LmortosV.Celula[m].col=j+1;
                                LmortosV.cont++;
                                m++;//aumenta o valor de m para que cada atribuicao seja em uma celula diferente da lista
                                aux=m;
                                break;
                            }
                            else if(aux==m)//continua o loop caso o m esteja com o mesmo valor de antes
                                continue;
                            else//para o loop caso o m tenha aumentado o seu valor
                                break;
                        }
                    }
                    if(matriz[i+1][j-1]=='M' && j-1!=0)//checa uma linha abaixo e uma coluna a esquerda
                    {
                        vizinhosM[i][j]++;
                        for(l=0;l<=vizinhosM[i][j];l++)//corre a lista novamente para checar se a coordenada atual ja esta ou nao nessa lista
                        {
                            if(jaExisteM(i+1,j-1)==0)//so adicionara coordenada se ela nao existir na lista
                            {
                                LmortosV.Celula[m].lin=i+1;
                                LmortosV.Celula[m].col=j-1;
                                LmortosV.cont++;
                                m++;//aumenta o valor de m para que cada atribuicao seja em uma celula diferente da lista
                                aux=m;
                                break;
                            }
                            else if(aux==m)//continua o loop caso o m esteja com o mesmo valor de antes
                                continue;
                            else//para o loop caso o m tenha aumentado o seu valor
                                break;
                        }
                    }
                    if(matriz[i+1][j]=='M')//checa uma linha abaixo
                    {
                        vizinhosM[i][j]++;
                        for(l=0;l<=vizinhosM[i][j];l++)//corre a lista novamente para checar se a coordenada atual ja esta ou nao nessa lista
                        {
                            if(jaExisteM(i+1,j)==0)//so adicionara coordenada se ela nao existir na lista
                            {
                                LmortosV.Celula[m].lin=i+1;
                                LmortosV.Celula[m].col=j;
                                LmortosV.cont++;
                                m++;//aumenta o valor de m para que cada atribuicao seja em uma celula diferente da lista
                                aux=m;
                                break;
                            }
                            else if(aux==m)//continua o loop caso o m esteja com o mesmo valor de antes
                                continue;
                            else//para o loop caso o m tenha aumentado o seu valor
                                break;
                        }
                    }
                    if(matriz[i+1][j+1]=='M')//checa uma linha abaixo e uma coluna a direita
                    {
                        vizinhosM[i][j]++;
                        for(l=0;l<=vizinhosM[i][j];l++)//corre a lista novamente para checar se a coordenada atual ja esta ou nao nessa lista
                        {
                            if(jaExisteM(i+1,j+1)==0)//so adicionara coordenada se ela nao existir na lista
                            {
                                LmortosV.Celula[m].lin=i+1;
                                LmortosV.Celula[m].col=j+1;
                                LmortosV.cont++;
                                m++;//aumenta o valor de m para que cada atribuicao seja em uma celula diferente da lista
                                aux=m;
                                break;
                            }
                            else if(aux==m)//continua o loop caso o m esteja com o mesmo valor de antes
                                continue;
                            else//para o loop caso o m tenha aumentado o seu valor
                                break;
                        }
                    }
                    //printf("Vizinhos mortos da celula (%d,%d): %d\n", i, j, vizinhosM[i][j]);
                }
            }
        }
    }
    
    printf("Lista dos mortos-vizinhos = %d:", LmortosV.cont);
    for(k=0;k<LmortosV.cont;k++)
        printf("(%d,%d)", LmortosV.Celula[k].lin, LmortosV.Celula[k].col);
    printf("\n");
}


int jaExisteM(int ii,int jj)//funcao que verifica se se a celula (ii,jj) ja esta na lista
{
    for(int n=0;n<=LmortosV.cont;n++)//corre a lista de mortos vizinhos atual para checar se a coordenada atual ja existe na lista
    {
        if(LmortosV.Celula[n].lin==ii && LmortosV.Celula[n].col==jj)
            return 1;// (ii,jj) ja existe
    }
    return 0;//(ii,jj) nao existe na lista
}

void contaVizinhosVdeM()//conta os vizinhos vivos de celulas mortas
{
    int i, j, k;

    for(i=0;i<=tam;i++)//limpando o valor de todas as coordenadas do array
    {
        for(j=0;j<=tam;j++)
            vizinhosVdeM[i][j]=0;
    }
    for(i=LmortosV.Celula[0].lin;i<=tam;i++)//detectar vizinhos mortos
    {
        for(j=LmortosV.Celula[0].col;j<=tam;j++)
        {
            for(k=0;k<=LmortosV.cont;k++)//for para correr os elementos da lista LmortosV
            {
                if(i==LmortosV.Celula[k].lin && j==LmortosV.Celula[k].col && i!=0 && j!=0)//apenas checara se houver vizinhos se a celula na lista de mortos vizinhos
                {
                    if(matriz[i-1][j-1]=='V' && i-1!=0 && j-1!=0)// checa uma linha acima e uma coluna a esquerda
                        vizinhosVdeM[i][j]++;
                    if(matriz[i-1][j]=='V' && i-1!=0)//checa uma linha acima
                        vizinhosVdeM[i][j]++;
                    if(matriz[i-1][j+1]=='V' && i-1!=0)//checa uma linha acima e uma coluna a direita
                        vizinhosVdeM[i][j]++;
                    if(matriz[i][j-1]=='V' && j-1!=0)//checa uma coluna a esquerda
                        vizinhosVdeM[i][j]++;
                    if(matriz[i][j+1]=='V')//checa uma coluna a direita
                        vizinhosVdeM[i][j]++;
                    if(matriz[i+1][j-1]=='V' && j-1!=0)//checa uma linha abaixo e uma coluna a esquerda
                        vizinhosVdeM[i][j]++;
                    if(matriz[i+1][j]=='V')//checa uma linha abaixo
                        vizinhosVdeM[i][j]++;
                    if(matriz[i+1][j+1]=='V')//checa uma linha abaixo e uma coluna a direita
                        vizinhosVdeM[i][j]++;
                }
            }
        }
    }
}

void proximaGeracao()//funcao que determina o status (vivo ou morto) de cada celula na proxima geracao
{
    int i, j, k, l, m=0;
    LvivosP.cont=0;
    for(i=0;i<=tam;i++)
    {
        for(j=0;j<=tam;j++)
        {
            for(k=0;k<=Lvivos.cont;k++)//corre a lista Lvivos
            {
                if(i==Lvivos.Celula[k].lin && j==Lvivos.Celula[k].col && i!=0 && j!=0)//so checa o status futuro da coordenada se ela estiver na lista dos vivos atuais
                {
                    //printf("A2 %d %d ", i, j);
                    if(vizinhosV[i][j]==2 || vizinhosV[i][j]==3)//se a celula viva possui 2 ou 3 vizinhos vivos, ela continua viva
                    {
                        //adicionando a coordenada para a lista de vivos da proxima geracao
                        LvivosP.Celula[m].lin=i;
                        LvivosP.Celula[m].col=j;
                        LvivosP.cont++;
                        m++;
                        //printf("A3 %d %d ", i, j);
                    }
                    else if(vizinhosV[i][j]== 0 || vizinhosV[i][j]== 1 || vizinhosV[i][j]>= 4)//se a celula viva possui 0, 1 ou mais que 4 vizinhos, ela morre na proxima geracao
                    {
                        //printf("A4 %d %d ", i, j);
                        matriz[i][j]='M';
                    }
                }
            }
            for(k=0;k<=LmortosV.cont;k++)//corre a lista LmortosV
            {
                if(i==LmortosV.Celula[k].lin && j==LmortosV.Celula[k].col)//so checa o futuro da coordenada atual se a celula estiver na lista dos mortos vizinhos
                {
                    if(vizinhosVdeM[i][j]==3)//a celula morta nasce caso ela tenha exatamente 3 vizinhos
                    {
                        //adicionando a coordenada para a lista de vivos da proxima geracao
                        LvivosP.Celula[m].lin=i;
                        LvivosP.Celula[m].col=j;
                        LvivosP.cont++;
                        m++;
                        matriz[i][j]='V';
                        //printf("B %d %d ", i, j);
                    }
                } 
            }
        }
    }

    detectaVizinhosMP();//faz a lista dos mortos vizinhos de celulas vivas da proxima geracao
    
    for(i=0;i<Lvivos.cont;i++)//limpa todos os valores da lista de vivos atuais antes de transformar a lista da proxima geracao na lista atual
    {
        Lvivos.Celula[i].lin=0;
        Lvivos.Celula[i].col=0;
    }
    for(i=0;i<LmortosV.cont;i++)//limpa todos os valores da lista de mortos vizinhos atuais antes de transformar a lista da proxima geracao na lista atual
    {
        LmortosV.Celula[i].lin=0;
        LmortosV.Celula[i].col=0;
    }

    //transforma a proxima geracao na geracao atual
    //printf("Nova lista de vivos atuais: ");
    for(i=0;i<LvivosP.cont;i++)
    {
        Lvivos.Celula[i].lin=LvivosP.Celula[i].lin;
        Lvivos.Celula[i].col=LvivosP.Celula[i].col;
        matriz[i][j]='V';
        //printf("(%d,%d)", Lvivos.Celula[i].lin, Lvivos.Celula[i].col);
    }
    Lvivos.cont=LvivosP.cont;
    //printf("\n");
    //printf("Nova lista de mortos vizinhos atuais: ");
    for(i=0;i<LmortosVP.cont;i++)
    {
        LmortosV.Celula[i].lin=LmortosVP.Celula[i].lin;
        LmortosV.Celula[i].col=LmortosVP.Celula[i].col;
        matriz[i][j]='M';
        //printf("(%d,%d)", LmortosV.Celula[i].lin, LmortosV.Celula[i].col);
    }
    LmortosV.cont=LmortosVP.cont;
    printf("\n");
}

void detectaVizinhosMP()//funcao que detecta mortos vizinhos da proxima geracao
{
    int i, j, k, l, m=0, aux;
    LmortosVP.cont=0;

    for(i=0;i<=tam;i++)//limpando o valor de todas as coordenadas do array
    {
        for(j=0;j<=tam;j++)
            vizinhosMP[i][j]=0;
    }
    for(i=LvivosP.Celula[0].lin;i<=tam;i++)//detectar vizinhos mortos
    {
        for(j=LvivosP.Celula[0].col;j<=tam;j++)
        {
            for(k=0;k<=LvivosP.cont;k++)
            {
                if(i==LvivosP.Celula[k].lin && j==LvivosP.Celula[k].col && i!=0 && j!=0)//apenas checara se houver vizinhos se a celula estiver viva
                {
                    if(matriz[i-1][j-1]=='M' && i-1!=0 && j-1!=0)// checa uma linha acima e uma coluna a esquerda
                    {
                        vizinhosMP[i][j]++;                      // as condições "&& i-1!=0" e "&& j-1!=0" para que não sejam checadas as coordenadas com 0 no array
                        for(l=0;l<=LvivosP.cont;l++)//corre a lista novamente para checar se a coordenada atual ja esta ou nao nessa lista
                        {
                            if(jaExisteMP(i-1,j-1)==0)//so adicionara a coordenada se ela nao existir na lista
                            {
                                LmortosVP.Celula[m].lin=i-1;
                                LmortosVP.Celula[m].col=j-1;
                                LmortosVP.cont++;
                                m++;//aumenta o valor de m para que cada atribuicao seja em uma celula diferente da lista
                                aux=m;
                                break;
                            }
                            else if(aux==m)//continua o loop caso o m esteja com o mesmo valor de antes
                                continue;
                            else//para o loop caso o m tenha aumentado o seu valor
                                break;
                        }
                    }
                    if(matriz[i-1][j]=='M' && i-1!=0)//checa uma linha acima
                    {
                        vizinhosMP[i][j]++;
                        for(l=0;l<=vizinhosMP[i][j];l++)//corre a lista novamente para checar se a coordenada atual ja esta ou nao nessa lista
                        {
                            if(jaExisteMP(i-1,j)==0)//so adicionara a coordenada se ela nao existir na lista
                            {
                                LmortosVP.Celula[m].lin=i-1;
                                LmortosVP.Celula[m].col=j;
                                LmortosVP.cont++;
                                m++;//aumenta o valor de m para que cada atribuicao seja em uma celula diferente da lista
                                aux=m;
                                break;
                            }
                            else if(aux==m)//continua o loop caso o m esteja com o mesmo valor de antes
                                continue;
                            else//para o loop caso o m tenha aumentado o seu valor
                                break;
                        }
                    }
                    if(matriz[i-1][j+1]=='M' && i-1!=0)//checa uma linha acima e uma coluna a direita
                    {
                        vizinhosMP[i][j]++;
                        for(l=0;l<=vizinhosMP[i][j];l++)//corre a lista novamente para checar se a coordenada atual ja esta ou nao nessa lista
                        {
                            if(jaExisteMP(i-1,j+1)==0)//so adicionara a coordenada se ela nao existir na lista
                            {
                                LmortosVP.Celula[m].lin=i-1;
                                LmortosVP.Celula[m].col=j+1;
                                LmortosVP.cont++;
                                m++;//aumenta o valor de m para que cada atribuicao seja em uma celula diferente da lista
                                aux=m;
                                break;
                            }
                            else if(aux==m)//continua o loop caso o m esteja com o mesmo valor de antes
                                continue;
                            else//para o loop caso o m tenha aumentado o seu valor
                                break;
                        }
                    }
                    if(matriz[i][j-1]=='M' && j-1!=0)//checa uma coluna a esquerda
                    {
                        vizinhosMP[i][j]++;
                        for(l=0;l<=vizinhosMP[i][j];l++)//corre a lista novamente para checar se a coordenada atual ja esta ou nao nessa lista
                        {
                            if(jaExisteMP(i,j-1)==0)//so adicionara a coordenada se ela nao existir na lista
                            {
                                LmortosVP.Celula[m].lin=i;
                                LmortosVP.Celula[m].col=j-1;
                                LmortosVP.cont++;
                                m++;//aumenta o valor de m para que cada atribuicao seja em uma celula diferente da lista
                                aux=m;
                                break;
                            }
                            else if(aux==m)//continua o loop caso o m esteja com o mesmo valor de antes
                                continue;
                            else//para o loop caso o m tenha aumentado o seu valor
                                break;
                        }
                    }
                    if(matriz[i][j+1]=='M')//checa uma coluna a direita
                    {
                        vizinhosMP[i][j]++;
                        for(l=0;l<=vizinhosMP[i][j];l++)//corre a lista novamente para checar se a coordenada atual ja esta ou nao nessa lista
                        {
                            if(jaExisteMP(i,j+1)==0)//so adicionara a coordenada se ela nao existir na lista
                            {
                                LmortosVP.Celula[m].lin=i;
                                LmortosVP.Celula[m].col=j+1;
                                LmortosVP.cont++;
                                m++;//aumenta o valor de m para que cada atribuicao seja em uma celula diferente da lista
                                aux=m;
                                break;
                            }
                            else if(aux==m)//continua o loop caso o m esteja com o mesmo valor de antes
                                continue;
                            else//para o loop caso o m tenha aumentado o seu valor
                                break;
                        }
                    }
                    if(matriz[i+1][j-1]=='M' && j-1!=0)//checa uma linha abaixo e uma coluna a esquerda
                    {
                        vizinhosMP[i][j]++;
                        for(l=0;l<=vizinhosMP[i][j];l++)//corre a lista novamente para checar se a coordenada atual ja esta ou nao nessa lista
                        {
                            if(jaExisteMP(i+1,j-1)==0)//so adicionara a coordenada se ela nao existir na lista
                            {
                                LmortosVP.Celula[m].lin=i+1;
                                LmortosVP.Celula[m].col=j-1;
                                LmortosVP.cont++;
                                m++;//aumenta o valor de m para que cada atribuicao seja em uma celula diferente da lista
                                aux=m;
                                break;
                            }
                            else if(aux==m)//continua o loop caso o m esteja com o mesmo valor de antes
                                continue;
                            else//para o loop caso o m tenha aumentado o seu valor
                                break;
                        }
                    }
                    if(matriz[i+1][j]=='M')//checa uma linha abaixo
                    {
                        vizinhosMP[i][j]++;
                        for(l=0;l<=vizinhosMP[i][j];l++)//corre a lista novamente para checar se a coordenada atual ja esta ou nao nessa lista
                        {
                            if(jaExisteMP(i+1,j)==0)//so adicionara a coordenada se ela nao existir na lista
                            {
                                LmortosVP.Celula[m].lin=i+1;
                                LmortosVP.Celula[m].col=j;
                                LmortosVP.cont++;
                                m++;//aumenta o valor de m para que cada atribuicao seja em uma celula diferente da lista
                                aux=m;
                                break;
                            }
                            else if(aux==m)//continua o loop caso o m esteja com o mesmo valor de antes
                                continue;
                            else//para o loop caso o m tenha aumentado o seu valor
                                break;
                        }
                    }
                    if(matriz[i+1][j+1]=='M')//checa uma linha abaixo e uma coluna a direita
                    {
                        vizinhosMP[i][j]++;
                        for(l=0;l<=vizinhosMP[i][j];l++)//corre a lista novamente para checar se a coordenada atual ja esta ou nao nessa lista
                        {
                            if(jaExisteMP(i+1,j+1)==0)//so adicionara a coordenada se ela nao existir na lista
                            {
                                LmortosVP.Celula[m].lin=i+1;
                                LmortosVP.Celula[m].col=j+1;
                                LmortosVP.cont++;
                                m++;//aumenta o valor de m para que cada atribuicao seja em uma celula diferente da lista
                                aux=m;
                                break;
                            }
                            else if(aux==m)//continua o loop caso o m esteja com o mesmo valor de antes
                                continue;
                            else//para o loop caso o m tenha aumentado o seu valor
                                break;
                        }
                    }
                    //teste
                    //printf("Vizinhos mortos da celula (%d,%d): %d\n", i, j, vizinhosMP[i][j]);        
                }
            }
        }
    }
    
    /*
    teste
    printf("\n");
    printf("Lista dos mortos-vizinhos da proxima geracao = %d:", LmortosVP.cont);
    for(k=0;k<LmortosVP.cont;k++)
        printf("(%d,%d)", LmortosVP.Celula[k].lin, LmortosVP.Celula[k].col);
    printf("\n");*/
}

int jaExisteMP(int ii,int jj)//funcao que verifica se se a celula (ii,jj) ja esta na lista
{
    for(int x=0;x<=LmortosVP.cont;x++)//corre a lista LmortosVP inteira
    {
        if(LmortosVP.Celula[x].lin==ii && LmortosVP.Celula[x].col==jj)//checa se a coordenada faz parte da lista LmortosVP
            return 1;// (ii,jj) ja existe
    }
    return 0;//(ii,jj) nao existe na lista
}
