#include <stdio.h>
#include <string.h>

#define ROW_LIMIT 1048576 //Number of rows microsoft excel can comprehend
#define STRING_LENGTH 20
#define NUM_TITLES_BUFFER 10

//Get all the different titleTypes of every entry
char** getTitles(size_t *numTitles, FILE* fp);

int main(void){
    FILE *fp = fopen("data.tsv", "r");
    //Number of titles*STRING_LENGTH characters
    //size_t numTitles = titleTypes();
    //char **titles = malloc(numTitles*sizeof(char)*STRING_LENGTH);
    size_t numTitles = 0;
    char **titles = getTitles(&numTitles, fp);
    

    printf("There are %zu titles present in this dataset.\n", numTitles);
    for(size_t i = 0; i < numTitles; i++){
        printf("Title %zu: %s\n", titles[i]);
    }
}

char** getTitles(size_t *numTitles, FILE* fp){
    //Make sure we're at the beginning
    rewind(fp);
    //Go to newline to skip the column titles
    //Source: https://stackoverflow.com/questions/30065675/what-does-scanf-nc-mean
    fscanf(fp, "%*[^\n]");

    char titles[NUM_TITLES_BUFFER][STRING_LENGTH];
    size_t numTitlesCounter = 0;

    while(fp != feof(fp)){
        //Skip tconst
        char tconst[STRING_LENGTH];
        //Get titleType
        char titleType[STRING_LENGTH];
        fscanf(fp, "%s  %s", tconst, titleType);

        //Compare titleType to current entries
        for(int i = 0; i < NUM_TITLES_BUFFER; i++){
            if(strcmp(titleType, titles[i]) == 0){ //Title is already in list
                //Go to newline
                fscanf(fp, "%*[^\n]");
                continue;
            }
        }

        //Go to newline
        fscanf(fp, "%*[^\n]");
    }

    return titles;
}
