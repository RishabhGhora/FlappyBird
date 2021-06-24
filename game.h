#ifndef GAME_H
#define GAME_H

#include "gba.h"


typedef struct {
        int gameOver;
        int won;
        int points;
        int x;
        int y;
        int pipeIndex;
        int heightIndex;
        int currentIndex;
        int bottomHeights[100];
        int topHeights[100];
        int harderBottomHeights[100];
        int harderTopHeights[100];
        int pipeY[100];
} AppState;

//This function can initialize an unused AppState struct
void initializeAppState(AppState *appState);

int chcekIfInBetweenNextPipe(AppState appState);


// This function will be used to process which state to go to 
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);


#endif
