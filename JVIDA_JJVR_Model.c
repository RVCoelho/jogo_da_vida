char matriz[100][100];//define se a celula esta viva ou morta ('M'=morto, 'V'=vivo)
int tam;//tamanho do mundo
int vizinhosV[100][100], vizinhosM[100][100];//vizinhosV = quantidade de vizinhos vivos, vizinhosM = quantidade de vizinhos mortos
int vizinhosVdeM[100][100];//quantidade de vizinhos vivos de celula morta(que esta na lista de mortos vizinhos)
int vizinhosMP[100][100], vizinhosVdeMP[100][100];//quantidade de vizinhos vivos de celula morta da proxima geracao

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
Tlista LmortosVP;//lista dos mortos vizinhos na proxima geracao
