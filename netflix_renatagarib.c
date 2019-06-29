#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>       


#define NetFlixFile "netflix_all.csv"   // Futuramente receber o nome do arquivo pelos argumentos do main(argc,argv)
#define NumMaxOfRecords 1001            // Futuramente fazer leitura do tamanho do arquivo e definir dinamicamente este tamanho

struct NetflixMovieRecord
{
    char title[200];
    char rating[10];
    char ratingDescription[200];             // No arquivo csv passado estas colunas estao com titulo trocados
    int  ratingLevel;                        // No arquivo csv passado estas colunas estao com titulo trocados
    int  releaseYear;
    int  userRatingScore;
    int  userRatingSize;
};

struct NetflixMovieRecord NetFlixMovies[NumMaxOfRecords];   // Create an array in global memory to be easely acessed for all functions



int main(int argc, char **argv) {

    FILE * NetFlixCSV;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    int title_line = 1;
    int have_empty_ratingDescription = 0;
    char *token;



   if ( ( NetFlixCSV = fopen( NetFlixFile, "r" ) ) == NULL ) { //Open a NetFlix CSV file

        printf( "NetFlixFile could not be opened - put the file in current diretory and try again.\n" );
        return(-1);
    }

    while ((read = getline(&line, &len, NetFlixCSV)) != -1) { // Reading a NetFlix CSV file line by line using getline (https://linux.die.net/man/3/getline)
    
        if (title_line == 1) { // Skip the title line
            title_line = 0;
            continue;
        }

        if ( strstr(line,";;") != NULL ) {
            have_empty_ratingDescription = 1;
        } else {
            have_empty_ratingDescription = 0;
        }

        token = strtok(line, ";");
        printf("token[%s]\n",token);
        strcpy( NetFlixMovies[i].title, token );

        token = strtok(NULL, ";");
        printf("token[%s]\n",token);
        strcpy( NetFlixMovies[i].rating, token );

        if ( have_empty_ratingDescription == 1) {
            strcpy( NetFlixMovies[i].ratingDescription, "----" );
        } else {
            token = strtok(NULL, ";");
            printf("token[%s]\n",token);
            strcpy( NetFlixMovies[i].ratingDescription, token );
        }

        token = strtok(NULL, ";");
        printf("token[%s]\n",token);
        NetFlixMovies[i].ratingLevel = atoi(token);

        token = strtok(NULL, ";");
        printf("token[%s]\n",token);
        NetFlixMovies[i].releaseYear = atoi(token);

        token = strtok(NULL, ";");
        printf("token[%s]\n",token);
        NetFlixMovies[i].userRatingScore = atoi(token);

        token = strtok(NULL, ";");
        printf("token[%s]\n",token);
        NetFlixMovies[i].userRatingSize = atoi(token);

        printf("Movie Index[%i] [%s] [%s] [%s] [%i] [%i] [%i] [%i] \n", i ,   
                                                            NetFlixMovies[i].title,
                                                            NetFlixMovies[i].rating,
                                                            NetFlixMovies[i].ratingDescription,
                                                            NetFlixMovies[i].ratingLevel,
                                                            NetFlixMovies[i].releaseYear,
                                                            NetFlixMovies[i].userRatingScore,
                                                            NetFlixMovies[i].userRatingSize );
        i++;
    }

    fclose(NetFlixCSV);
    return(0);    
}



