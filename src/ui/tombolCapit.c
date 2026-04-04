#include "src/ui/tombolCapit.h"

void drawTombolCapit(Rectangle btnRec, int btnHover, int btnDown) {
    Color topColor = (Color){112, 172, 45, 255}; //warna tombol
    Color baseColor = (Color){50, 90, 20, 255}; 

    int turun = 0; 

    if (btnDown) {
        topColor = (Color){76, 125, 30, 255};   
        turun = 5; 
    } else if (btnHover) {
        topColor = (Color){140, 200, 60, 255};   
    }

    //Alas tombol
    Rectangle baseRec = { btnRec.x, btnRec.y + 5, btnRec.width, btnRec.height };
    DrawRectangleRounded(baseRec, 0.5f, 10, baseColor); 
    // Tombol atas
    Rectangle topRec = { btnRec.x, btnRec.y + turun, btnRec.width, btnRec.height };
    DrawRectangleRounded(topRec, 0.5f, 10, topColor);
    DrawText("CAPIT", (int)btnRec.x + 25, (int)btnRec.y + 12 + turun, 16, WHITE);
}