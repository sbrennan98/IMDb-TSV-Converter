#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROW_LIMIT 1048576 //Number of rows microsoft excel can comprehend
#define STRING_LENGTH 20
#define NUM_TITLES_BUFFER 20

//Get all the different titleTypes of every entry
char** getTitles(size_t *numTitles, FILE* fp);

int main(void){
    FILE *fp = fopen("data/data.tsv", "r");
    if(fp == NULL){
        printf("Couldn't open file.\n");
        return -1;
    }
    //Number of titles*STRING_LENGTH characters
    //size_t numTitles = titleTypes();
    //char **titles = malloc(numTitles*sizeof(char)*STRING_LENGTH);
    size_t numTitles = 0;
    char **titles = getTitles(&numTitles, fp);
    

    printf("There are %zu titles present in this dataset.\n", numTitles);
    for(size_t i = 0; i < numTitles; i++){
        printf("Title %zu: %s\n", i+1, titles[i]);
    }
    free(titles);
}

/*  This function has given us the following information:
 *      Titles for Video table:
 *          -short
 *          -movie
 *          -tvShort
 *          -tvMovie
 *          -tvSeries
 *          -tvMiniSeries
 *          -tvSpecial
 *          -video
 *      Titles for Episode table:
 *          -tvEpisode
 *          -episode
 *      Titles to be discarded as my db doesn't support:
 *          -videoGame
 *          -audiobook
 *          -radioSeries
 *  
 */
char** getTitles(size_t *numTitles, FILE* fp){
    //Make sure we're at the beginning
    rewind(fp);
    //Go to newline to skip the column titles
    //Source: https://stackoverflow.com/questions/30065675/what-does-scanf-nc-mean
    fscanf(fp, "%*[^\n]");

    char titles[NUM_TITLES_BUFFER][STRING_LENGTH];
    //char **titles = malloc(NUM_TITLES_BUFFER*STRING_LENGTH*sizeof(char));
    size_t numTitlesCounter = 0;
    bool alreadyInList = false;
    
    //Skip tconst
    char tconst[STRING_LENGTH];
    //Get titleType
    char titleType[STRING_LENGTH];
    while(!feof(fp)){
        alreadyInList = false;
        
        fscanf(fp, "%s  %s", tconst, titleType);
        
        //Compare titleType to current entries
        for(int i = 0; i < NUM_TITLES_BUFFER; i++){
            if(strcmp(titleType, titles[i]) == 0){ //Title is already in list
                //Go to newline
                //printf("Already added %s\n", titleType);
                fscanf(fp, "%*[^\n]");
                alreadyInList = true;
            }
        }
        if(alreadyInList){
            continue;
        }

        //Add title to list
        strcpy(titles[numTitlesCounter], titleType);
        numTitlesCounter++;
        printf("[%zu] Added %s\n", numTitlesCounter, titleType);
        //Go to newline
        fscanf(fp, "%*[^\n]");
    }

    *numTitles = numTitlesCounter;
    
    
    char **allTitles = malloc(numTitlesCounter*sizeof(char*));

    for(int i = 0; i < numTitlesCounter; i++){
        allTitles[i] = malloc(STRING_LENGTH*sizeof(char));
        //printf("Not dead yet. %s\n", titles[i]);
        strcpy(allTitles[i], titles[i]);
    }
    return allTitles;
    
    //return titles;
}
