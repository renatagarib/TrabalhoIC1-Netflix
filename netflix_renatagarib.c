#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NetFlixFile "netflix_all.csv" // Futuramente receber o nome do arquivo pelos argumentos do main(argc,argv)
#define NumMaxOfRecords 1001          // Futuramente fazer leitura do tamanho do arquivo e definir dinamicamente este tamanho

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

struct NetflixMovieRecord NetFlixMoviesDURT[NumMaxOfRecords]; // Create an array in global memory to be easely acessed for all functions
struct NetflixMovieRecord NetFlixMovies[NumMaxOfRecords]; // Create an array in global memory to be easely acessed for all functions
int    ActualNumberOfMovies = 0;



int TitleAlreadyInserted( char *title ) {
    
    int Inserted = 0;

    for (int i=0; i<ActualNumberOfMovies; ++i)
    {
        if (strcmp(title,NetFlixMovies[i].title) == 0)
        {
            Inserted = 1;
            break;
        }
    }
    return(Inserted);
}


void ClearRepetitions(void)
{
    for (int i=0; i<NumMaxOfRecords; ++i) 
    {
        if ( strlen(NetFlixMoviesDURT[i].title)==0 || TitleAlreadyInserted(NetFlixMoviesDURT[i].title) ) 
        {
            continue;   // skip to the next
        } else {
            strcpy( NetFlixMovies[ActualNumberOfMovies].title, NetFlixMoviesDURT[i].title);
            strcpy( NetFlixMovies[ActualNumberOfMovies].rating, NetFlixMoviesDURT[i].rating);
            strcpy( NetFlixMovies[ActualNumberOfMovies].ratingDescription, NetFlixMoviesDURT[i].ratingDescription);
            NetFlixMovies[ActualNumberOfMovies].ratingLevel = NetFlixMoviesDURT[i].ratingLevel;
            NetFlixMovies[ActualNumberOfMovies].releaseYear = NetFlixMoviesDURT[i].releaseYear;
            NetFlixMovies[ActualNumberOfMovies].userRatingScore = NetFlixMoviesDURT[i].userRatingScore;
            NetFlixMovies[ActualNumberOfMovies].userRatingSize = NetFlixMoviesDURT[i].userRatingSize;
            ++ActualNumberOfMovies;
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
    int title_line = 1;
    int linhavazia = 0;
    char *token;

    //___________________________________LEITURA DE ARQUIVO CSV E ARMAZENAMENTO EM UM ARRAY________________________//

    if ((NetFlixCSV = fopen(NetFlixFile, "r")) == NULL)
    { //Open a NetFlix CSV file

        printf("NetFlixFile could not be opened - put the file in current diretory and try again.\n");
        return (-1);
    }

    while ((read = getline(&line, &len, NetFlixCSV)) != -1)
    { // Reading a NetFlix CSV file line by line using getline (https://linux.die.net/man/3/getline)

        if (title_line == 1)
        { // Skip the title line
            title_line = 0;
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
        //printf("token[%s]\n",token);
        strcpy(NetFlixMoviesDURT[i].title, token);

        token = strtok(NULL, ";");
        //printf("token[%s]\n",token);
        strcpy(NetFlixMoviesDURT[i].rating, token);

        if (linhavazia == 1)
        {
            strcpy(NetFlixMoviesDURT[i].ratingDescription, "NA");
        }
        else
        {
            token = strtok(NULL, ";");
            //printf("token[%s]\n",token);
            strcpy(NetFlixMoviesDURT[i].ratingDescription, token);
        }

        token = strtok(NULL, ";");
        //printf("token[%s]\n",token);
        NetFlixMoviesDURT[i].ratingLevel = atoi(token);

        token = strtok(NULL, ";");
        //printf("token[%s]\n",token);
        NetFlixMoviesDURT[i].releaseYear = atoi(token);

        token = strtok(NULL, ";");
        //printf("token[%s]\n",token);
        NetFlixMoviesDURT[i].userRatingScore = atoi(token);

        token = strtok(NULL, ";");
        //printf("token[%s]\n",token);
        NetFlixMoviesDURT[i].userRatingSize = atoi(token);

        // printf("Movie Index[%i] [%s] [%s] [%s] [%i] [%i] [%i] [%i] \n", i,
        //        NetFlixMoviesDURT[i].title,
        //        NetFlixMoviesDURT[i].rating,
        //        NetFlixMoviesDURT[i].ratingDescription,
        //        NetFlixMoviesDURT[i].ratingLevel,
        //        NetFlixMoviesDURT[i].releaseYear,
        //        NetFlixMoviesDURT[i].userRatingScore,
        //        NetFlixMoviesDURT[i].userRatingSize);

        i++;
    }
    fclose(NetFlixCSV);


    //____________________________ LIMPEZA DO ARRAY CRIADO RETIRANDO AS DUPLICIDADES __________//

    ClearRepetitions();

    for (i=0;i<ActualNumberOfMovies;++i)
    {
        printf("Movie Index[%i] [%s] [%s] [%s] [%i] [%i] [%i] [%i] \n", i,
                NetFlixMovies[i].title,
                NetFlixMovies[i].rating,
                NetFlixMovies[i].ratingDescription,
                NetFlixMovies[i].ratingLevel,
                NetFlixMovies[i].releaseYear,
                NetFlixMovies[i].userRatingScore,
                NetFlixMovies[i].userRatingSize);
    }

    //____________________________ LEITURA DO ARRAY CRIADO ____________________________________//
    int primeiro_ano = NetFlixMovies[0].releaseYear;
    int ultimo_ano = NetFlixMovies[0].releaseYear;
    for (int j = 0; j < 999; j++)
    {
        if (NetFlixMovies[j].releaseYear < primeiro_ano)
        {
            primeiro_ano = NetFlixMovies[j].releaseYear;
            //printf("%i, %i\n", primeiro_ano,j);
        }
        if (NetFlixMovies[j].releaseYear > ultimo_ano)
        {
            ultimo_ano = NetFlixMovies[j].releaseYear;
        }
    }

    FILE *UserRatingScore;

    UserRatingScore = fopen("UserRatingScore.csv", "w");

    printf("Ano; G; PG; PG-13; R; NR; UR; TV-G; TV-PG; TV-14; TV-MA; TV-Y; TV-Y7; TV-Y7-FV; total\n");
    for (int a = ultimo_ano; a >= primeiro_ano; a--)
    {

        int G = 0;
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
        int total = 0;

        int melhores[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
        int n = 0;
        for (int b = 0; b < 999; b++)
        {

            if (NetFlixMovies[b].releaseYear == a)
            {

                if (n < 10)
                {
                    if (strcmp(NetFlixMovies[b].title, NetFlixMovies[melhores[n]].title)!=0)
                    {
                        melhores[n] = b;
                        n++;
                    }
                }

                else
                {

                    int melhor = 0;
                    for (int k = 0; k < 10; k++)
                    {
                        if (NetFlixMovies[b].userRatingScore > NetFlixMovies[melhores[k]].userRatingScore)
                        {
                            if (strcmp(NetFlixMovies[b].title, NetFlixMovies[melhores[k]].title)!=0)
                            {
                                melhores[k] = b;
                            }
                        }
                    }
                }

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
                total++;
            }
        }

        if (total)
        {
            fprintf(UserRatingScore, "Melhores de %i", a);
            for (int j = 0; j < 10; j++)
            {
                if (melhores[j] != -1)
                {
                    fprintf(UserRatingScore, "; %s", NetFlixMovies[melhores[j]].title);
                }
            }
            fprintf(UserRatingScore, "\n");

            printf("%i; %i; %i; %i; %i; %i; %i; %i; %i; %i; %i; %i; %i; %i; %i; \n",
                   a, G, PG, PG13, R, NR, UR, TVG, TVPG, TV14, TVMA, TVY, TVY7, TVY7FV, total);
        }
    }

    return (0);
}

// int G
// int PG
// int PG-13
// int R
// int NR
// int UR
// int TV-G
// int TV-PG
// int TV-14
// int TV-MA
// int TV-Y
// int TV-Y7
// int TV-Y7-FV