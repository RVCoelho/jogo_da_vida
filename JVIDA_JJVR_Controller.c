#include "JVIDA_JJVR_Model.c"
#include "JVIDA_JJVR_View.c"

void jogoDaVida();//funcao que contem o loop principal do jogo
void geraMundo();//funcao que gera o mundo inicial
void selecionaVivos();//funcao que da ao operador a opcao de selecionar quais celulas ficarao vivas na primeira geracao
void limpaMundo();//funcao que torna todas as celulas mortas
void detectaVizinhos();//funcao que detecta os vizinhos mortos e vizinhos vivos das celulas vivas
void proximaGeracao();//funcao que determina o status (vivo ou morto) de cada celula na proxima geracao
int jaExisteM(int ii,int jj);//funcao que verifica se se a celula (ii,jj) ja esta na lista

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
                break;

            case 3:
                p=quantasGeracoes();
                q=quantoTempo();
                while(i<p)
                {
                    printf("Geracao %d\n", i+1);
                    detectaVizinhos();
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
    int aux1, aux2, i;
    Lvivos.cont=0;
    i=Lvivos.cont;
	
    printf("Digite as coordenadas das celulas que voce deseja colocar:\n");
    printf("Separe a linha e a coluna da coordenada e aperte enter para ir para a proxima celula(-1 para parar)\n");
	while(aux1 != -1 || aux2 != -1)
    {
        printf("Selecione a coordenada da celula viva #%d: ",i+1);
        scanf("%d %d", &aux1, &aux2);
        if(aux1 > 0 || aux2 >0)
        {
            Lvivos.Celula[i].lin = aux1;//define a coordenada linha
            Lvivos.Celula[i].col = aux2;//define a coordenada coluna
            Lvivos.cont++;//enumera quantas celulas estao vivas atualmente na lista
        }
        apresentaMundo();
        printf("\n");
        i++;
    }

    printf("Lista das celulas vivas = %d: ", Lvivos.cont);
    for(i=0;i<Lvivos.cont;i++) //apresenta as coordenadas das celulas vivas
    {
        printf("(%d,%d)", Lvivos.Celula[i].lin, Lvivos.Celula[i].col);
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
                matriz[i][j] = '.';
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
            vizinhosM[i][j]=0;
    }
    for(i=Lvivos.Celula[0].lin;i<=tam;i++)//detectar vizinhos mortos
    {
        for(j=Lvivos.Celula[0].col;j<=tam;j++)
        {
            for(k=0;k<=Lvivos.cont;k++)//for para correr os elementos da lista Lvivos
            {
                if(i==Lvivos.Celula[k].lin && j==Lvivos.Celula[k].col && i!=0 && j!=0)//apenas checara se houver vizinhos se a celula estiver viva
                {
                    if(matriz[i-1][j-1]=='.' && i-1!=0 && j-1!=0)// checa uma linha acima e uma coluna a esquerda
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
                    if(matriz[i-1][j]=='.' && i-1!=0)//checa uma linha acima
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
                    if(matriz[i-1][j+1]=='.' && i-1!=0)//checa uma linha acima e uma coluna a direita
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
                    if(matriz[i][j-1]=='.' && j-1!=0)//checa uma coluna a esquerda
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
                    if(matriz[i][j+1]=='.')//checa uma coluna a direita
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
                    if(matriz[i+1][j-1]=='.' && j-1!=0)//checa uma linha abaixo e uma coluna a esquerda
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
                    if(matriz[i+1][j]=='.')//checa uma linha abaixo
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
                    if(matriz[i+1][j+1]=='.')//checa uma linha abaixo e uma coluna a direita
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

void proximaGeracao()//funcao que determina o status (vivo ou morto) de cada celula na proxima geracao
{
    int i, j, cont=0, m=0;
    LvivosP.cont=0;
    for(i=0;i<Lvivos.cont;i++)
    {
        for(j=0;j<Lvivos.cont;j++)
        {
            if(Lvivos.Celula[i].lin == Lvivos.Celula[j].lin && Lvivos.Celula[i].col == Lvivos.Celula[j].col)//como esta comparando a lista com ela mesma, pula se o elemento comparado for igual, porque nao tem como ele ser vizinho dele mesmo
                continue;
            else
            {
                if(Lvivos.Celula[i].lin-1 == Lvivos.Celula[j].lin && Lvivos.Celula[i].col-1 == Lvivos.Celula[j].col)//checa se a celula j esta uma linha acima e uma coluna a esquerda da celula i
                    cont++;
                if(Lvivos.Celula[i].lin-1 == Lvivos.Celula[j].lin && Lvivos.Celula[i].col == Lvivos.Celula[j].col)//checa se a celula j esta uma linha acima  da celula i
                    cont++;
                if(Lvivos.Celula[i].lin-1 == Lvivos.Celula[j].lin && Lvivos.Celula[i].col+1 == Lvivos.Celula[j].col)//checa se a celula j esta uma linha acima e uma coluna a direita da celula i
                    cont++;
                if(Lvivos.Celula[i].lin == Lvivos.Celula[j].lin && Lvivos.Celula[i].col-1 == Lvivos.Celula[j].col)//checa se a celula j esta uma coluna a esquerda da celula i
                    cont++;
                if(Lvivos.Celula[i].lin == Lvivos.Celula[j].lin && Lvivos.Celula[i].col+1 == Lvivos.Celula[j].col)//checa se a celula j esta uma coluna a direita da celula i
                    cont++;
                if(Lvivos.Celula[i].lin+1 == Lvivos.Celula[j].lin && Lvivos.Celula[i].col-1 == Lvivos.Celula[j].col)//checa se a celula j esta uma linha abaixo e uma coluna a esquerda da celula i
                    cont++;
                if(Lvivos.Celula[i].lin+1 == Lvivos.Celula[j].lin && Lvivos.Celula[i].col == Lvivos.Celula[j].col)//checa se a celula j esta uma linha abaixo da celula i
                    cont++;
                if(Lvivos.Celula[i].lin+1 == Lvivos.Celula[j].lin && Lvivos.Celula[i].col+1 == Lvivos.Celula[j].col)//checa se a celula j esta uma linha abaixo e uma coluna a direita da celula i
                    cont++; 
                //printf("1) i= %d, j= %d contador %d\t", i, j, cont);
            }
        }
        if(cont==2 || cont==3)//passando a celula para a lista de vivos da proxima geracao caso ela tenha 2 ou 3 vizinhos
        {
            LvivosP.Celula[m].lin=Lvivos.Celula[i].lin;
            LvivosP.Celula[m].col=Lvivos.Celula[i].col;
            LvivosP.cont++;
            m++;
        }
        cont=0;
    }
    for(i=0;i<LmortosV.cont;i++)
    {
        for(j=0;j<Lvivos.cont;j++)
        {
            if(LmortosV.Celula[i].lin-1 == Lvivos.Celula[j].lin && LmortosV.Celula[i].col-1 == Lvivos.Celula[j].col)//checa se a celula vizinha na linha acima e coluna esquerda e uma celula viva 
                cont++;
            if(LmortosV.Celula[i].lin-1 == Lvivos.Celula[j].lin && LmortosV.Celula[i].col == Lvivos.Celula[j].col)//checa se a celula vizinha na linha acima e uma celula viva 
                cont++;
            if(LmortosV.Celula[i].lin-1 == Lvivos.Celula[j].lin && LmortosV.Celula[i].col+1 == Lvivos.Celula[j].col)//checa se a celula vizinha na linha acima e coluna direita e uma celula viva 
                cont++;
            if(LmortosV.Celula[i].lin == Lvivos.Celula[j].lin && LmortosV.Celula[i].col-1 == Lvivos.Celula[j].col)//checa se a celula vizinha na coluna esquerda e uma celula viva 
                cont++;
            if(LmortosV.Celula[i].lin == Lvivos.Celula[j].lin && LmortosV.Celula[i].col+1 == Lvivos.Celula[j].col)//checa se a celula vizinha na coluna direita e uma celula viva 
                cont++;
            if(LmortosV.Celula[i].lin+1 == Lvivos.Celula[j].lin && LmortosV.Celula[i].col-1 == Lvivos.Celula[j].col)//checa se a celula vizinha na linha abaixo e coluna esquerda e uma celula viva 
                cont++;
            if(LmortosV.Celula[i].lin+1 == Lvivos.Celula[j].lin && LmortosV.Celula[i].col == Lvivos.Celula[j].col)//checa se a celula vizinha na linha abaixo e uma celula viva 
                cont++;
            if(LmortosV.Celula[i].lin+1 == Lvivos.Celula[j].lin && LmortosV.Celula[i].col+1 == Lvivos.Celula[j].col)//checa se a celula vizinha na linha abaixo e coluna direita e uma celula viva 
                cont++;
            //printf("i= %d, j= %d contador %d\t", i, j, cont);
        }
        if(cont==3)//passando a celula morta vizinha para a lista de vivos da proxima geracao caso ela tenha 3 vizinhos
        {
            LvivosP.Celula[m].lin=LmortosV.Celula[i].lin;
            LvivosP.Celula[m].col=LmortosV.Celula[i].col;
            LvivosP.cont++;
            m++;
        }
        cont=0;
    }
    for(i=0;i<Lvivos.cont;i++)//limpa todos os valores da lista de vivos atuais antes de transformar a lista da proxima geracao na lista atual
    {
        Lvivos.Celula[i].lin=0;
        Lvivos.Celula[i].col=0;
    }
    for(i=0;i<LmortosV.cont;i++)//limpa todos os valores da lista de mortos vizinhos atuais
    {
        LmortosV.Celula[i].lin=0;
        LmortosV.Celula[i].col=0;
    }
    LmortosV.cont=0;

    //transforma a proxima geracao na geracao atual
    printf("Nova lista de vivos atuais: ");
    for(i=0;i<LvivosP.cont;i++)
    {
        Lvivos.Celula[i].lin=LvivosP.Celula[i].lin;
        Lvivos.Celula[i].col=LvivosP.Celula[i].col;
        printf("(%d,%d)", Lvivos.Celula[i].lin, Lvivos.Celula[i].col);
    }
    Lvivos.cont=LvivosP.cont;
    printf("\n");
}
