#include "GameState.h"

void Gamestate_Init(){
    current_GameState   = 0;
    current_SudokuState = 0;
}

int GetGamestate() { return current_GameState; }
void SetGameState(int newState) { current_GameState = newState; }
int GetSudokustate() { return current_SudokuState; }
void SetSudokuState(int newState) {current_SudokuState = newState; }