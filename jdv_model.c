struct mundo1
{
    char status[100][100];//variavel que determina se a celula esta viva(V) ou morta(M)
    int tam;//variavel que determina o tamanho da matriz
} mundo;

struct vivos1 //vivos atuais
{
    int celula[100][100];
    int cont; //contador de celulas
} vivos;

struct mortosV1 //mortos vizinhos atuais
{
    int celula[100][100];
    int cont;
} mortosV;

struct vivosPG1 //vivos da proxima geracao
{
    int celula[100][100];
    int cont;
} vivosPG;

struct mortosVPG1 //mortos vizinhos da proxima geracao
{
    int celula[100][100];
    int cont;
} mortosVPG;
