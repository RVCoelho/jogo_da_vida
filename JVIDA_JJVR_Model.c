char matriz[100][100];//define se a celula esta viva ou morta ('M'=morto, 'V'=vivo)
int tam;//tamanho do mundo
int vizinhosM[100][100];//vizinhosM = quantidade de vizinhos mortos

typedef struct cell
{
    int lin, col;//propriedade linha e coluna da celula
} Tcelula; //tipo celula

typedef struct lista
{
    int cont;//indica quantos elementos existem na lista
    Tcelula Celula[500];//celula da lista
} Tlista;

Tlista Lvivos;//lista das celulas vivas na atual geracao
Tlista LmortosV;//lista dos mortos vizinhos da atual geração
Tlista LvivosP; //lista dos vivos na proxima geracao
