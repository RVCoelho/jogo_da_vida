int menu();

int menu()
{
    int x;
    printf("    JOGO DA VIDA\n");
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
