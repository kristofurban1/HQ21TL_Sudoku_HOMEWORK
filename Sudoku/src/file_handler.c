#include "file_handler.h"

char *BasePath;

bool FileExists(const char *filename){
    FILE *fp = fopen(filename, "r");
    if (fp != NULL){
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

struct SaveData *GetDefaultSaveData(){
    struct SaveData *def = malloc(sizeof(SaveData));
        SetErrorIndentfyer("file_handler: GetDefaultSaveData"); malloc_verify(def);

        def->BoardSize       = 3;
        def->WindowWidth     = Default_WIDTH;
        def->WindowHeight    = Default_HEIGHT;
        def->u16Difficulty   = game_dif_EASY;
        def->u16CheatLevel   = game_chlvl_NONE;
    
    return def;
}

void WriteSaveData(struct SaveData *data){
    char *pszSaveDataPath = AppendToBasePath(PATH_SAVEDATA, BasePath);
    FILE *fp = fopen(pszSaveDataPath, "w");
    free(pszSaveDataPath);
    fwrite(data, sizeof(SaveData), 1, fp);
    fclose(fp);
}

struct SaveData *ReadSaveData(){
    char *pszSaveDataPath = AppendToBasePath(PATH_SAVEDATA, BasePath);
    FILE *fp = fopen(pszSaveDataPath, "r");
    free(pszSaveDataPath);

    if (fp == NULL) return NULL;

    int bytes;
    for(bytes = 0; getc(fp) != EOF; ++bytes);

    if (bytes != sizeof(SaveData)) {
        printf("%s corrupted. Loading defaults. (%d : %d)\n", PATH_SAVEDATA, bytes, sizeof(SaveData));
        struct SaveData *def = GetDefaultSaveData(); GC_Append(def);
        return def;
    }
    fseek(fp, 0, SEEK_SET);

    struct SaveData *data = malloc(sizeof(SaveData)); GC_Append(data);
    fread(data, sizeof(SaveData), 1, fp);
    fclose(fp);

    return data;
}

void WriteLeaderboard(struct Leaderboard_Entry *entries, int entryCount){
    char *pszLeaderboardPath = AppendToBasePath(PATH_LEADERBOARD, BasePath);
    FILE *fp = fopen(pszLeaderboardPath, "w");
    free(pszLeaderboardPath);
    fwrite(&entryCount, sizeof(int), 1, fp);
    fwrite(entries, sizeof(Leaderboard_Entry), entryCount, fp);
    fclose(fp);
}

struct Leaderboard_Entry *ReadLeaderboard(int *entryCount_out){
    char *pszLeaderboardPath = AppendToBasePath(PATH_LEADERBOARD, BasePath);
    FILE *fp = fopen(pszLeaderboardPath, "r");
    free(pszLeaderboardPath);

    int entryCount;
    fread(&entryCount, sizeof(int), 1, fp);

    struct Leaderboard_Entry *entries;
        entries = malloc(sizeof(Leaderboard_Entry) * entryCount);
        SetErrorIndentfyer("file_handler: ReadLeaderboard"); malloc_verify(entries);
        GC_Append(entries);
    
    fread(entries, sizeof(Leaderboard_Entry), entryCount, fp);
    fclose(fp);
    entryCount_out = &entryCount;
    return entries;
}

void FileHandler_Init(){
    BasePath = SDL_GetBasePath(); //GC_Append(BasePath);


    char *dataFolder = AppendToBasePath(DIR_DATA, BasePath);
    mkdir(dataFolder);
    free(dataFolder);

    char *pszSaveDataPath = AppendToBasePath(PATH_SAVEDATA, BasePath);
    if (!FileExists(pszSaveDataPath)){
        struct SaveData *def = GetDefaultSaveData();
        WriteSaveData(def);
        free(def);
    }
    free(pszSaveDataPath);

    char *pszLeaderboardPath = AppendToBasePath(PATH_LEADERBOARD, BasePath);
    if (!FileExists(pszLeaderboardPath)){
        WriteLeaderboard(NULL, 0);
    }
    free(pszLeaderboardPath);
}

char *GetAsset(char* assetName){
    char *pszAssetFolder = AppendToBasePath(DIR_ASSETS, BasePath);
    char *pszAssetPath = AppendToBasePath(assetName, pszAssetFolder); GC_Append(pszAssetPath);
    free(pszAssetFolder);

    return pszAssetPath;
}