/*
    Nome: Renata Rona Garib

    Numero USP: 11207950

*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define NetFlixFile "netflix_all.csv" 
#define NumMaxOfRecords 999           

struct NetflixMovieRecord
{
    char title[200];
    char rating[10];
    char ratingDescription[200]; // No arquivo csv passado estas colunas estao com titulo trocados
    int ratingLevel;             // No arquivo csv passado estas colunas estao com titulo trocados
    int releaseYear;
    int userRatingScore;
    int userRatingSize;
};

struct NetflixMovieRecord NetFlixMoviesDURT[NumMaxOfRecords]; // Criando um array na memoria global para que ele seja facilmente acessado por todas as funções
struct NetflixMovieRecord NetFlixMovies[NumMaxOfRecords];     // Criando um array na memoria global para que ele seja facilmente acessado por todas as funções
int ActualNumberOfMovies = 0;

int isSomething(char cat[40], char entry[200])       // Funçaõ usada nos itens 5 e 6, para ler os ratings descriptions e os nomes dos filmes
{
    if (strstr(entry, cat) != NULL)
    {
        return 1;
    }
    return 0;
}

int TitleAlreadyInserted(char *title)          
{

    int Inserted = 0;

    for (int i = 0; i < ActualNumberOfMovies; ++i)
    {
        if (strcmp(title, NetFlixMovies[i].title) == 0)
        {
            Inserted = 1;
            break;
        }
    }
    return (Inserted);
}

void ClearRepetitions(void)                // Função usada para ler o array criado com todos os filmes e retirar os repetidos, colocando-os em um novo array
{
    for (int i = 0; i < NumMaxOfRecords; ++i)
    {
        if (strlen(NetFlixMoviesDURT[i].title) == 0 || TitleAlreadyInserted(NetFlixMoviesDURT[i].title)) 
        {
            continue; // Pula para o proximo
        }
        else
        {
            strcpy(NetFlixMovies[ActualNumberOfMovies].title, NetFlixMoviesDURT[i].title);
            strcpy(NetFlixMovies[ActualNumberOfMovies].rating, NetFlixMoviesDURT[i].rating);
            strcpy(NetFlixMovies[ActualNumberOfMovies].ratingDescription, NetFlixMoviesDURT[i].ratingDescription);
            NetFlixMovies[ActualNumberOfMovies].ratingLevel = NetFlixMoviesDURT[i].ratingLevel;
            NetFlixMovies[ActualNumberOfMovies].releaseYear = NetFlixMoviesDURT[i].releaseYear;
            NetFlixMovies[ActualNumberOfMovies].userRatingScore = NetFlixMoviesDURT[i].userRatingScore;
            NetFlixMovies[ActualNumberOfMovies].userRatingSize = NetFlixMoviesDURT[i].userRatingSize;
            ++ActualNumberOfMovies;
        }
    }
}


void BubleSortDescReleaseYearUserRatingScore()     // Ordena Array por Ano e UserRatingScore Usando algoritimo BubleSorte http://www.cprogrammingnotes.com/question/sorting-structure-array.html
{
    int i, j;
    struct NetflixMovieRecord temp;
    
    for (i = 0; i < (ActualNumberOfMovies - 1); i++)
    {
        for (j = 0; j < (ActualNumberOfMovies - 1-i); j++)
        {
            if (  (NetFlixMovies[j].releaseYear*100+NetFlixMovies[j].userRatingScore) < (NetFlixMovies[j+1].releaseYear*100+NetFlixMovies[j+1].userRatingScore))
            {
                temp = NetFlixMovies[j];
                NetFlixMovies[j] = NetFlixMovies[j + 1];
                NetFlixMovies[j+1] = temp;
            } 
        }
    }
}




int main(int argc, char **argv)
{

    FILE *NetFlixCSV;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    int linhaTitulo = 1;
    int linhavazia = 0;
    char *token;

    //___________________________________LEITURA DE ARQUIVO CSV E ARMAZENAMENTO EM UM ARRAY________________________//
    // QUESTAO 1

    if ((NetFlixCSV = fopen(NetFlixFile, "r")) == NULL)
    { //Abrir o arquivo dado

        printf("NetFlixFile could not be opened - put the file in current diretory and try again.\n");
        return (-1);
    }

    while ((read = getline(&line, &len, NetFlixCSV)) != -1)
    { // Lendo o arquivo linha por linha usando getline

        if (linhaTitulo == 1)
        { // Pula a linha de titulo
            linhaTitulo = 0;
            continue;
        }

        if (strstr(line, ";;") != NULL)
        {
            linhavazia = 1;
        }
        else
        {
            linhavazia = 0;
        }

        token = strtok(line, ";");
        strcpy(NetFlixMoviesDURT[i].title, token);

        token = strtok(NULL, ";");
        strcpy(NetFlixMoviesDURT[i].rating, token);

        if (linhavazia == 1)
        {
            strcpy(NetFlixMoviesDURT[i].ratingDescription, "NA");
        }
        else
        {
            token = strtok(NULL, ";");
            strcpy(NetFlixMoviesDURT[i].ratingDescription, token);
        }

        token = strtok(NULL, ";");
        NetFlixMoviesDURT[i].ratingLevel = atoi(token);

        token = strtok(NULL, ";");
        NetFlixMoviesDURT[i].releaseYear = atoi(token);

        token = strtok(NULL, ";");
        NetFlixMoviesDURT[i].userRatingScore = atoi(token);

        token = strtok(NULL, ";");
        NetFlixMoviesDURT[i].userRatingSize = atoi(token);


        i++;
    }
    fclose(NetFlixCSV);

    //____________________________ LIMPEZA E ORDENACAO DO ARRAY CRIADO RETIRANDO AS DUPLICIDADES __________//

    ClearRepetitions();
    BubleSortDescReleaseYearUserRatingScore();

    for (i = 0; i < ActualNumberOfMovies; ++i)
    {
        printf("Movie Index[%i] [%s] [%s] [%s] [%i] [%i] [%i] [%i] \n", i, // Printando o array sem repetição e já ordenado
               NetFlixMovies[i].title,
               NetFlixMovies[i].rating,
               NetFlixMovies[i].ratingDescription,
               NetFlixMovies[i].ratingLevel,
               NetFlixMovies[i].releaseYear,
               NetFlixMovies[i].userRatingScore,
               NetFlixMovies[i].userRatingSize);
    }
    printf("\n\n\n\n");

    //____________________________ LEITURA DO ARRAY CRIADO ____________________________________//
    
    int primeiro_ano = NetFlixMovies[0].releaseYear;  // Achando o primeiro e o ultimo ano, para achar pra quais anos seria necessario scanear
    int ultimo_ano = NetFlixMovies[0].releaseYear;
    for (int j = 0; j < ActualNumberOfMovies; j++)
    {
        if (NetFlixMovies[j].releaseYear < primeiro_ano)
        {
            primeiro_ano = NetFlixMovies[j].releaseYear;
        }
        if (NetFlixMovies[j].releaseYear > ultimo_ano)
        {
            ultimo_ano = NetFlixMovies[j].releaseYear;
        }
    }

    int TOTAL; // Contador para total de filmes

    // QUESTÃO 2 E 3

    printf("Ano; G; PG; PG-13; R; NR; UR; TV-G; TV-PG; TV-14; TV-MA; TV-Y; TV-Y7; TV-Y7-FV; TOTAL\n");
    for (int a = ultimo_ano; a >= primeiro_ano; a--)
    {

        int G = 0;                    // Criando os contadores para cada rating
        int PG = 0;
        int PG13 = 0;
        int R = 0;
        int NR = 0;
        int UR = 0;
        int TVG = 0;
        int TVPG = 0;
        int TV14 = 0;
        int TVMA = 0;
        int TVY = 0;
        int TVY7 = 0;
        int TVY7FV = 0;
        int outros = 0;
        int total = 0;        // Cotador para total de filmes por ano

        int n = 0;

        for (int b = 0; b < ActualNumberOfMovies; b++)         
        {

            if (NetFlixMovies[b].releaseYear == a)       
            {


                // Adiciona um na variavel do rating do filme em questão
                if (strcmp(NetFlixMovies[b].rating, "G") == 0)
                {
                    G++;
                }
                else if (strcmp(NetFlixMovies[b].rating, "PG") == 0)
                {
                    PG++;
                }
                else if (strcmp(NetFlixMovies[b].rating, "PG-13") == 0)
                {
                    PG13++;
                }
                else if (strcmp(NetFlixMovies[b].rating, "R") == 0)
                {
                    R++;
                }
                else if (strcmp(NetFlixMovies[b].rating, "NR") == 0)
                {
                    NR++;
                }
                else if (strcmp(NetFlixMovies[b].rating, "UR") == 0)
                {
                    UR++;
                }
                else if (strcmp(NetFlixMovies[b].rating, "TV-G") == 0)
                {
                    TVG++;
                }
                else if (strcmp(NetFlixMovies[b].rating, "TV-PG") == 0)
                {
                    TVPG++;
                }
                else if (strcmp(NetFlixMovies[b].rating, "TV-14") == 0)
                {
                    TV14++;
                }
                else if (strcmp(NetFlixMovies[b].rating, "TV-MA") == 0)
                {
                    TVMA++;
                }
                else if (strcmp(NetFlixMovies[b].rating, "TV-Y") == 0)
                {
                    TVY++;
                }
                else if (strcmp(NetFlixMovies[b].rating, "TV-Y7") == 0)
                {
                    TVY7++;
                }
                else if (strcmp(NetFlixMovies[b].rating, "TV-Y7-FV") == 0)
                {
                    TVY7FV++;
                }
                total++; // Adiciona um no total de filmes do ano em questão (QUESTÃO 3)

                
            }
        }

        if (total)
        {
            printf("%i; %i; %i; %i; %i; %i; %i; %i; %i; %i; %i; %i; %i; %i; %i; \n",
                   a, G, PG, PG13, R, NR, UR, TVG, TVPG, TV14, TVMA, TVY, TVY7, TVY7FV, total);

            printf("O total de filmes do ano %i é %i\n", a, total); // Imprimi o total (item 3)
            TOTAL+=total;
        }
    }




    FILE *UserRatingScore; // Criando o arquivo para o item 4

    UserRatingScore = fopen("UserRatingScore.txt", "w");

    for (int a = ultimo_ano; a >= primeiro_ano; a--)
    {
        int Primeiros10MelhoesFilmes = 0;

        for (int b = 0; b < ActualNumberOfMovies; b++)         
        {
            if (NetFlixMovies[b].releaseYear == a)       
            {
                // Melhores10 Filmes (QUESTÃO 4)
                if ( Primeiros10MelhoesFilmes < 10 ) {
                    if (Primeiros10MelhoesFilmes == 0){
                        printf("\n");fprintf(UserRatingScore,"\r\n");
                        }
                    printf("Melhores Filmes de [%i] %iº lugar vai para: [%s] com UserRatingScore [%i]\n", a, Primeiros10MelhoesFilmes+1,
                        NetFlixMovies[b].title,
                        NetFlixMovies[b].userRatingScore);
                    fprintf(UserRatingScore,"Melhores Filmes de [%i] %iº lugar vai para: [%s] com UserRatingScore [%i]\r\n", a, Primeiros10MelhoesFilmes+1,
                        NetFlixMovies[b].title,
                        NetFlixMovies[b].userRatingScore);
                    
                    ++Primeiros10MelhoesFilmes;
                   
                }
            }
        }

    }
    fclose(UserRatingScore);
    printf("\n\n\n\n");








    // QUESTÕ 5
    int sexual = 0;    // Cria contadores para os filmes sexuais e violentos
    int violent = 0;

    for (int l = 0; l < ActualNumberOfMovies; l++)
    {

        if (isSomething("sex", NetFlixMovies[l].ratingDescription))  // Procura "sex" nos ratings descriptions, se achado é adicionado 1 ao contador
        {
            sexual++;
        }

        if (isSomething("violence", NetFlixMovies[l].ratingDescription) || isSomething("violent", NetFlixMovies[l].ratingDescription))   // Procura "violent" nos ratings descriptions, se achado é adicionado 1 ao contador
        {
            violent++;
        }
    }
    printf("Filmes com conteúdo sexual: %i\nFilmes com conteúdo violento: %i\n", sexual, violent);

    printf("A porcentagem de filmes com conteudo sexual é %f%%\n", 100 * (double) sexual/ (double) TOTAL);

    printf("A porcentagem de filmes com conteudo violento é %f%%\n", 100* (double) violent/ (double) TOTAL);

    // QUESTÃO 6

    for (;;)
    {
        int search = 1;
        printf("Deseja fazer um busca?\n 0-Não\n 1-Sim\n");  
        scanf("%i", &search);
        if (!search)  // Looping infinito para se procurar quantas palavras desejar
        {
            break;
        }

        char palavra[40];  
        printf("Digite uma palavra chave:\n");

        scanf("%39s", palavra);      // Escaneia a palavra desejada
        for (int m = 0; m < ActualNumberOfMovies; m++)   // Procura em todos os filmes
        {
            if (isSomething(palavra, NetFlixMovies[m].title))   // Procura a palavra nos titulos
            {
                printf("\nRESULTADOS DA BUSCA: \n %s -- %s -- %s\n", NetFlixMovies[m].title, NetFlixMovies[m].rating, NetFlixMovies[m].ratingDescription); // Se achado se imprime o titulo, o rating e a rating description
            }
        }
    }
    return (0);
}

