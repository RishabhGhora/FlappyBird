#include "draw.h"
#include "gba.h"
#include <stdio.h>

#include "images/bird.h"
#include "images/pipe.h"
#include "images/pipedown.h"
#include "images/ground.h"


void drawBird(int x, int y) {
    drawImageDMA(x, y, 15, 15,(u16*) bird);
}

void undrawBird(AppState *state) {
    drawRectDMA(state->x, state->y, 15, 15, BLUE);
}

void drawBottomPipe(int height, int y) {
    drawImageDMA(135-height, y, 20, height, (u16*) pipe);
}

void undrawBottomPipe(int height, int y) {
    drawRectDMA(135-height, y, 20, height, BLUE);
}

void getRidBottomPipe(AppState *state) {
    drawRectDMA(0, 0, 50, 135, BLUE);
    char scoreBuffer[20];
    sprintf(scoreBuffer, "%d", state->points);
    drawString(50, 135, "Score: ", WHITE);
    drawString(90, 135, scoreBuffer, WHITE);
}

void drawTopPipe(int height, int y) {
    drawImageDMA(0, y, 20, height, (u16*) pipedown);
}

void undrawTopPipe(int height, int y) {
    drawRectDMA(0, y, 20, height, BLUE);
}

void undrawScore(void) {
    drawRectDMA(0, 2, 50, 20, BLUE);
}



void fullDrawAppState(AppState *state) {
    char scoreBuffer[20];
    sprintf(scoreBuffer, "%d", state->points);
    drawString(50, 135, "Score: ", WHITE);
    drawString(90, 135, scoreBuffer, WHITE);
    drawBird(state->x, state->y);
    drawBottomPipe(state->bottomHeights[state->currentIndex], state->pipeY[state->currentIndex]);
    drawTopPipe(state->topHeights[state->currentIndex], state->pipeY[state->currentIndex]);
}

// This function will be used to undraw state
void undrawAppState(AppState *state) {
    undrawBird(state);
    if (state->points > 25) {
        undrawBottomPipe(state->harderBottomHeights[state->currentIndex], state->pipeY[state->currentIndex]);
        undrawTopPipe(state->harderTopHeights[state->currentIndex], state->pipeY[state->currentIndex]);
    } else {
        undrawBottomPipe(state->bottomHeights[state->currentIndex], state->pipeY[state->currentIndex]);
        undrawTopPipe(state->topHeights[state->currentIndex], state->pipeY[state->currentIndex]);
    }
    
    drawImageDMA(135, 0, 240, 25, (u16*) ground);
    
}

// This function will be used to draw state
void drawAppState(AppState *state) {
    char scoreBuffer[20];
    drawString(50, 135, "Score: ", WHITE);
    sprintf(scoreBuffer, "%d", state->points);
    drawString(90, 135, scoreBuffer, WHITE);
    drawBird(state->x, state->y);
    if (state->points > 25) {
        drawBottomPipe(state->harderBottomHeights[state->currentIndex], state->pipeY[state->currentIndex]);
        drawTopPipe(state->harderTopHeights[state->currentIndex], state->pipeY[state->currentIndex]);
    } else {
        drawBottomPipe(state->bottomHeights[state->currentIndex], state->pipeY[state->currentIndex]);
        drawTopPipe(state->topHeights[state->currentIndex], state->pipeY[state->currentIndex]);
    }
    if (state->pipeY[state->currentIndex] < 20) {
        getRidBottomPipe(state);
        char scoreBuffer[20];
        sprintf(scoreBuffer, "%d", state->points);
        drawString(50, 135, "Score: ", WHITE);
        drawString(90, 135, scoreBuffer, WHITE);
    } 
   
    
}


