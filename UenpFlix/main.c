#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char FILENAME[] = "dados.txt";
char FILENAME_AUX[] = "auxiliar.txt";
//duas variaveis com a "url" dos arquivos

typedef struct{//cria a struct
    int id;
    char titulo[50];
    char tipo[10];
    int ano;
    char genero[50];
    int classificacao;
    int duracao;
} Filme;

void troca_dados(){//função para copiar um dado de uma lista para outra
    Filme aux;

    fclose(fopen(FILENAME, "wb"));
    FILE * arquivo = fopen(FILENAME, "ab");
    FILE * arquivo2 = fopen(FILENAME_AUX, "rb");

    if (arquivo == NULL || arquivo2 == NULL){
        printf("ERRO AO ABRIR O ARQUIVO!\n");
        exit(1);
    }
    while(fread(&aux, sizeof(Filme), 1, arquivo2)){
        fwrite(&aux, sizeof(Filme), 1, arquivo);//equanto tiver um arquivo a ser lido no aqruivo de texto 2 será gravado esse mesmo arquivo no arquivo de texto 1
    }

    fclose(arquivo2);
    fclose(arquivo);
}
int cadastrar(){
    int result;
    Filme aux;
    FILE * arquivo = fopen(FILENAME, "ab");

    if (arquivo == NULL){
        printf("ERRO AO ABRIR O ARQUIVO!\n");
        exit(1);
    }

    printf("ID: ");
    scanf("%d", &aux.id);
    getchar();

    printf("Titulo: ");
    fgets(aux.titulo, 50, stdin);
    aux.titulo[strlen(aux.titulo) - 1] = '\0';

    printf("Tipo: ");
    fgets(aux.tipo, 10, stdin);
    aux.tipo[strlen(aux.tipo) - 1] = '\0';

    printf("Ano de lancamento: ");
    scanf("%d", &aux.ano);
    getchar();

    printf("Genero: ");
    fgets(aux.genero, 50, stdin);
    aux.genero[strlen(aux.genero) - 1] = '\0';

    printf("Classificacao indicativa: ");
    scanf("%d", &aux.classificacao);

    printf("Duracao (minutos): ");
    scanf("%d", &aux.duracao);
    result = fwrite(&aux, sizeof(Filme), 1, arquivo);//caso tenha dado certo retornara true, ou seja 1
    fclose(arquivo);

    return result;
}
void listar(){
    char letra;
    Filme aux;
    FILE * arquivo = fopen(FILENAME, "rb");

    if (arquivo == NULL){
        printf("ERRO AO ABRIR O ARQUIVO!\n");
        exit(1);
    }
    while(fread(&aux, sizeof(Filme), 1, arquivo)){
        printf("Id: %d\n", aux.id);
        printf("Titulo: %s\n", aux.titulo);
        printf("Tipo: %s\n", aux.tipo);
        printf("Ano: %d\n", aux.ano);
        printf("Genero: %s\n", aux.genero);
        printf("Classificacao indicativa: +%d anos\n", aux.classificacao);
        printf("Duracao: %d minutos\n", aux.duracao);
        printf("\n");
    }
    system("pause");//apos listar todos os arquivos ele da um pause antes de limpar a tela
    system("cls");
}

void listarAux(){//função para auxiliar na exclusao ou consulta de um dado cadastrado apenas
    Filme aux;
    FILE * arquivo = fopen(FILENAME, "rb");

    if (arquivo == NULL){
        printf("ERRO AO ABRIR O ARQUIVO!\n");
        exit(1);
    }
    while(fread(&aux, sizeof(Filme), 1, arquivo)){
        printf("Id: %d\n", aux.id);
        printf("\n");
    }
}

void consultar(){
    Filme aux;
    int n, status = 0;
    FILE * arquivo = fopen(FILENAME, "rb");

    if (arquivo == NULL){
        printf("ERRO AO ABRIR O ARQUIVO!\n");
        exit(1);
    }
    system("cls");
    listarAux();//traz a função para auxiliar na escolha de qual dado deseja escolher para consultar
    printf("Digite o ID desejado: ");
    scanf("%d", &n);
    while(fread(&aux, sizeof(Filme), 1, arquivo)){//enquanto tiver um arquivo para ler no arquivo de texto 1 irá repetir até entrar no if
        if(n == aux.id){//caso ache um ID igual oa digitado o WHILE será parado e irá para outro if
            status = 1;
            break;
        }
    }
    if(status){//caso a variavel status seja TRUE, ou seja igual a 1, trara os dados do ID escolhido
        printf("\nId: %d\n", aux.id);
        printf("Titulo: %s\n", aux.titulo);
        printf("Tipo: %s\n", aux.tipo);
        printf("Ano: %d\n", aux.ano);
        printf("Genero: %s\n", aux.genero);
        printf("Classificacao indicativa: %d anos\n", aux.classificacao);
        printf("Duracao: %d minutos\n", aux.duracao);
    }else{
        printf("\nRegistro nao encontrado!\n\n");
    }
    system("pause");
}

void alterar(){
    fclose(fopen(FILENAME_AUX, "wb"));
    Filme aux, aux2;
    int n, status = 0, result;
    FILE * arquivo = fopen(FILENAME, "rb");
    FILE * arquivo2 = fopen(FILENAME_AUX, "ab");

    if (arquivo == NULL || arquivo2 == NULL){
        printf("ERRO AO ABRIR O ARQUIVO!\n");
        exit(1);
    }
    system("cls");
    listarAux();//traz a função para auxiliar na escolha de qual dado deseja escolher para editar
    printf("Digite o ID desejado: ");
    scanf("%d", &n);
    getchar();

    while(fread(&aux, sizeof(Filme), 1, arquivo)){//enquanto tiver um arquivo para ler no arquivo de texto 1 irá repetir até entrar no if
        if(n == aux.id){//todo o if ira cadastrar um novo filme no arquivo de texto 2 editado e so depois usando a função troca dados será levado para o arquivo de texto 1
            aux2.id = aux.id;
            printf("\nTitulo: ");
            fgets(aux2.titulo, 50, stdin);
            aux2.titulo[strlen(aux2.titulo) - 1] = '\0';
            printf("Tipo: ");
            fgets(aux2.tipo, 10, stdin);
            aux2.tipo[strlen(aux2.tipo) - 1] = '\0';
            printf("Ano de lancamento: ");
            scanf("%d", &aux2.ano);
            getchar();
            printf("Genero: ");
            fgets(aux2.genero, 50, stdin);
            aux2.genero[strlen(aux2.genero) - 1] = '\0';
            printf("Classificacao indicativa: ");
            scanf("%d", &aux2.classificacao);
            printf("Duracao (minutos): ");
            scanf("%d", &aux2.duracao);
            result = fwrite(&aux2, sizeof(Filme), 1, arquivo2);
            continue;
        }else{
            fwrite(&aux, sizeof(Filme), 1, arquivo2);
            result = 0;
        }
    }

    if(result){
        printf("\nRegistro alterado com sucesso!\n\n");
    } else {
        printf("\nRegistro nao encontrado!\n\n");
    }

    fclose(arquivo2);
    fclose(arquivo);
    troca_dados();//quando atualiza os dados no arquivo de texto 1

    system("pause");
}
void excluir(){//nessa função irá passar todos os dados para uma lista menos o que vc escolher
    fclose(fopen(FILENAME_AUX, "wb"));
    Filme aux, aux2;
    int n, status = 0, flag=0;
    FILE * arquivo = fopen(FILENAME, "rb");
    FILE * arquivo2 = fopen(FILENAME_AUX, "ab");
    if (arquivo == NULL || arquivo2 == NULL){
        printf("ERRO AO ABRIR O ARQUIVO!\n");
        exit(1);
    }
    system("cls");
    listarAux();//traz a função para auxiliar na escolha de qual dado deseja escolher para excluir
    printf("Digite o ID desejado: ");
    scanf("%d", &n);
    getchar();
    while(fread(&aux, sizeof(Filme), 1, arquivo)){
        if(n == aux.id){//quando o arquivo escolhido vir para esse qhile ele não será passado para o arquivo de texto 2
            flag = 1;
            continue;
        } else {
            fwrite(&aux, sizeof(Filme), 1, arquivo2);//passando todos os dados para o arquivo de texto 2
        }
    }

    if(flag){
        printf("\nRegistro excluido com sucesso!\n\n");
    } else {
        printf("\nRegistro nao encontrado!\n\n");
    }
    fclose(arquivo2);
    fclose(arquivo);
    troca_dados();//aqui será o pulo do gato, como todos os dados menos o que vc escolheu foi para o arquivo de texto 2, quando vc manda ele passar todos os arquivos de volta para o arquivo de texto 1 o arquivo que vc escolheu será deletado pois ele será apagado pelos novos textos
    system("pause");
}


int main(){
    int op, id;
    do{//faça tudo isso que está entre as chaves enquanto o parametro do whiile seja respeitado, ouseja nao seja digitado o numero 0
        system("cls");
        printf("[1] Cadastrar\n[2] Consultar\n[3] Listar\n[4] Alterar\n[5] Excluir\n[0] Sair\n ");
        scanf("%d", &op);
        getchar();
        switch (op) {
            case 1:
                if (cadastrar()){
                    system("cls");
                    printf("Item cadastrado com sucesso!\n");
                } else {
                    system("cls");
                    printf("Nao foi possivel cadastrar!\n");
                }
                break;
            case 2:
                consultar();
                break;
            case 3:
                listar();
                break;
            case 4:
                alterar();
                break;
            case 5:
                excluir();
                break;
            case 0://caso seja 0 ele irá  parar
                break;
            default:
                system("cls");//caso digite qualquer opção que não esteja no menu, irá alertar o usuario
                printf("\nOPCAO NAO EXISTE!!!\n");
                system("pause");
        }
    }while(op != 0);//continuara rodando enquanto não ser digitado 0

    return 0;
}
