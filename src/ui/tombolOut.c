#include "src/ui/tombolOut.h"

void drawTombolOut(Rectangle btnOutRec, int btnHoverOut, int btnDownOut) {
    Color topColor= (Color){216, 63, 49, 255}; 
    Color baseColor = (Color){50, 90, 20, 255};

    int turun = 0; 

    if (btnDownOut) {
        topColor = (Color){76, 125, 30, 255};  
        turun = 5;  
    } else if (btnHoverOut) {
        topColor = (Color){238, 147, 34, 255};   
    }

    //Alas tombol
    Rectangle baseRec = { btnOutRec.x, btnOutRec.y + 5, btnOutRec.width, btnOutRec.height };
    DrawRectangleRounded(baseRec, 0.5f, 10, baseColor); 
    // Tombol atas
    Rectangle topRec = { btnOutRec.x, btnOutRec.y + turun, btnOutRec.width, btnOutRec.height };
    DrawRectangleRounded(topRec, 0.5f, 10, topColor);
    DrawText("KELUAR", (int)btnOutRec.x + 15, (int)btnOutRec.y + 12 + turun, 16, WHITE);
}