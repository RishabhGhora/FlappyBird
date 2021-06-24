#include "gba.h"
#include "game.h"
#include "draw.h"
#include <stdio.h>
#include <stdlib.h>
                    /* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"
#include "images/startScreen.h"
#include "images/ground.h"
#include "images/end.h"

                    /* TODO: */
// Add any additional states you need for your app.
typedef enum {
    START,
    START_NODRAW,
    APP_INIT,
    APP,
    APP_EXIT,
    WON,
    APP_EXIT_NODRAW,
} GBAState;



int main(void) {
                    /* TODO: */
    // Manipulate REG_DISPCNT here to set Mode 3. //
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    // Save current and previous state of button input.
    u32 previousButtons = BUTTONS;
    u32 currentButtons = BUTTONS;

    // Load initial game state
    GBAState state = START;
    AppState currentAppState, nextAppState;

    while (1) {
        currentButtons = BUTTONS; // Load the current state of the buttons


                    /* TODO: */
        // Manipulate the state machine below as needed //
        // NOTE: Call waitForVBlank() before you draw

        switch(state) {
            case START:
                waitForVBlank();
                
                //Start
                drawFullScreenImageDMA((u16*) startScreen);
                state = START_NODRAW;
                break;
            case START_NODRAW:
                if (KEY_DOWN(BUTTON_START, BUTTONS)) {
                    fillScreenDMA(BLUE);
                    drawImageDMA(135, 0, 240, 25, (u16*) ground);
                    state = APP_INIT;
                }   
                break;
            case APP_INIT:
                initializeAppState(&currentAppState);

                fullDrawAppState(&currentAppState);

                state = APP;
                break;
            case APP: 
                if (KEY_DOWN(BUTTON_SELECT, BUTTONS)) {
                    state = START;
                    break;
                }

                // Process the app at current state and store the next state
                nextAppState = processAppState(&currentAppState, previousButtons, currentButtons);

                 // Wait for VBlank before drawing
                waitForVBlank();

                // Undraw the previous state
                undrawAppState(&currentAppState);

                // Draw the current state
                drawAppState(&nextAppState);

                // Sets the current state as the next state for the next iteration.
                currentAppState = nextAppState;

                // Check if user lost, if so then go to the exit state.
                if (nextAppState.gameOver == 1) {
                    state = APP_EXIT;
                }

                if (nextAppState.won == 1) {
                    state = WON;
                }

                break;
            case WON: 
                if (KEY_DOWN(BUTTON_SELECT, BUTTONS)) {
                    state = START;
                    break;
                }

                // Wait for VBlank
                waitForVBlank();

                // TA-TODO: Draw the exit / gameover screen
                drawFullScreenImageDMA((u16*) end);
                drawString(25, 100, "Congratulations You Won! ", WHITE);
                char scoreBuffer2[20];
                sprintf(scoreBuffer2, "%d", currentAppState.points);
                drawString(65, 140, scoreBuffer2, WHITE);
                state = APP_EXIT_NODRAW;
                break;

                break;
            case APP_EXIT:
                if (KEY_DOWN(BUTTON_SELECT, BUTTONS)) {
                    state = START;
                    break;
                }

                // Wait for VBlank
                waitForVBlank();

                // TA-TODO: Draw the exit / gameover screen
                drawFullScreenImageDMA((u16*) end);
                drawString(25, 100, "Score: ", WHITE);
                char scoreBuffer[20];
                sprintf(scoreBuffer, "%d", currentAppState.points);
                drawString(65, 100, scoreBuffer, WHITE);
                state = APP_EXIT_NODRAW;
                break;
            case APP_EXIT_NODRAW:
                // TA-TODO: Check for a button press here to go back to the start screen
                if (KEY_JUST_PRESSED(1023, currentButtons, previousButtons)) {
                    state = START;
                }
                break;
        }



        previousButtons = currentButtons; // Store the current state of the buttons
    }

    return 0;
}