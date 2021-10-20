char matriz[100][100];
int tam;

typedef struct cell
{
    int lin, col;
} Tcelula; //tipo celula

typedef struct lista
{
    int cont;
    Tcelula Celula[500];
} Tlista;

Tlista Lvivos;
Tlista Lmortos;
Tlista LvivosP; //proxima geracao
Tlista LmortosP;

/*
como carregar a lista:
Lvivos.cont=0;
i=Lvivos.cont;
Lvivos.Celula[i].lin = 5;
Lvivos.Celula[i].col = 7;
Lvivos.cont++;
*/
