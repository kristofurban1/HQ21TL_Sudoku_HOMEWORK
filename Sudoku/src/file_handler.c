#include "file_handler.h"

bool FileExists(const char *filename){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        fclose(fp);
        return true;
    }
    return false;
}

char *AppendToBasePath(char *endOfPath, char *basePath){
    int eop_len  = strlen(endOfPath);
    int base_len = strlen(basePath);

    char *final = malloc((eop_len + base_len + 1) * sizeof(char));

    strcpy(final, basePath);
    strcat(final, endOfPath);

    return final;
}

void FileHandler_Init(){
    char *BasePath = SDL_GetBasePath();

    char *pszSaveDataPath = AppendToBasePath(PATH_SAVADATA, BasePath);
    if (!FileExists(pszSaveDataPath)){
        FILE *fp = fopen(pszSaveDataPath, "w");
        fclose(fp);
    }

    char *pszLeaderboardPath = AppendToBasePath(PATH_LEADERBOARD, BasePath);
    if (!FileExists(pszLeaderboardPath)){
        FILE *fp = fopen(pszLeaderboardPath, "w");
        fclose(fp);
    }
    


}