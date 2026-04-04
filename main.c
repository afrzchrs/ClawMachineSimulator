#include "raylib.h"
#include "screen_type.h"
#include "src/ui/back_button.h"
#include "src/screens/menu.h"
#include "src/screens/about.h"
#include "src/screens/claw.h" 
#include "src/screens/model.h"

int main(void) {
    InitWindow(SCREEN_W, SCREEN_H, "Claw Machine Simulator");

    InitGameAudio();

    SetTargetFPS(60);

    Screen current = MENU;

    PlayMenuBGM();

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_F11)) { 
            ToggleFullscreen();
        }

        UpdateGameAudio(current);

        // LOGIKA MENU
       if (current == MENU) {
            int clicked = GetClickedProgram();
            
            if (clicked == 10) {         
                current = CLAW;
                PlayClawBGM();
            } else if (clicked == 20) {
                current = MODEL;    
            } else if (clicked == 99) {
                current = ABOUT;     
            } else if (clicked == -1) {
                break;                 
            }
        }
        
        // LOGIKA TOMBOL KEMBALI
        if (current != MENU && BackButtonPressed()) {
            current = MENU;
            PlayMenuBGM(); 
        }
        
        // RENDER LAYAR
        BeginDrawing();
        switch (current) {
            case MENU:         
                DrawMenu();     
                break;
            case MODEL:        
                DrawModelScreen();
                break;
            case ABOUT:        
                DrawAbout();        
                break;
            case CLAW: 
                if (DrawProgramClaw() == 1) {
                    current = MENU; 
                }
                break;
        }

        EndDrawing();
    }

    UnloadGameAudio();
    CloseWindow();
    return 0;
}
