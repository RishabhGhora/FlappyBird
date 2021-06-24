#include "game.h"

void initializeAppState(AppState* appState) {
    // Initialize everything needed for game
    
    appState->gameOver = 0;
    appState->won = 0;
    appState->points = 0;
    appState->x = HEIGHT/2 - 25;
    appState->y = 20;
    for (int i = 0; i < 100; i++) {
        if (i == 0) {
            appState->pipeY[i] = 150; 
        } else {
            appState->pipeY[i] = appState->pipeY[i-1] + 75;
        }
    }
    appState->pipeIndex = 0;
    appState->currentIndex = 0;
    appState->heightIndex = 0;
    for (int i = 0; i < 100; i++) {
        appState->bottomHeights[i] = randint(10, 40);
        appState->topHeights[i] = randint(10, 80);
        appState->harderBottomHeights[i] = randint(20, 40);
        appState->harderTopHeights[i] = randint(30, 80);
    }

}


AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow) {

    AppState nextAppState = *currentAppState;
   
    if (KEY_JUST_PRESSED(BUTTON_A, keysPressedNow, keysPressedBefore)) {
        nextAppState.x = nextAppState.x - 15;
        nextAppState.y = nextAppState.y + 1;
    }

    if (nextAppState.y > 200) {
        nextAppState.y = 20;
    }

    if (vBlankCounter % 2 == 0) {
        if (nextAppState.x > 0 && nextAppState.x < HEIGHT - 25) {
            nextAppState.x = nextAppState.x + 1;
            if (vBlankCounter % 64 == 0) {
                nextAppState.y = nextAppState.y + 1;
            }
            for (int i = 0; i < 100; i++) {
                nextAppState.pipeY[i]--;
            }
            
        } else {
            nextAppState.gameOver = 1;
        }
    }

    if (nextAppState.y == nextAppState.pipeY[nextAppState.currentIndex]) {
        if (nextAppState.x >= nextAppState.topHeights[nextAppState.currentIndex] && nextAppState.x <= (HEIGHT - nextAppState.bottomHeights[nextAppState.currentIndex] - 25)) {
            nextAppState.points = nextAppState.points + 1;
            nextAppState.currentIndex++;
        } else {
            nextAppState.gameOver = 1;
        }
    }

    if (nextAppState.currentIndex == currentAppState->currentIndex && nextAppState.points > currentAppState->points) {
        nextAppState.currentIndex++;
    }

    if (nextAppState.y > nextAppState.pipeY[nextAppState.currentIndex] && nextAppState.gameOver != 1) {
        nextAppState.currentIndex++;
        nextAppState.points++;
    }

    
    for (int i = 0; i < 100; i++) {
        if (nextAppState.pipeY[i] < 20) {
            nextAppState.pipeY[i] = 0;
        }
    }

    if (nextAppState.points == 100) {
        nextAppState.won = 1;
    }
    
    return nextAppState;
}
