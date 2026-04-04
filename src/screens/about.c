#include "src/screens/about.h"

void DrawAbout(void) {
    DrawRectangleGradientV(0, 0, SCREEN_W, SCREEN_H, (Color){20, 10, 35, 255}, (Color){5, 5, 10, 255});

    DrawRectangle(0, 0, SCREEN_W, 60, (Color){0, 0, 0, 200});
    DrawBackButton();
    DrawText("DEVELOPER INFO", 135, 20, 24, MAGENTA);
    DrawLine(0, 60, SCREEN_W, 60, MAGENTA);

    int cardX = SCREEN_W/2 - 280, cardY = 100, cardW = 560, cardH = 320;
    DrawRectangleRounded((Rectangle){cardX, cardY, cardW, cardH}, 0.05f, 16, (Color){30, 25, 50, 180});
    DrawRectangleRoundedLines((Rectangle){cardX, cardY, cardW, cardH}, 0.05f, 16, VIOLET);

    // Avatar Placeholder (DDA Art)
    int avX = cardX + 120, avY = cardY + 120;
    int avR = 60;
    
    // Lingkaran luar berputar (Aksen Cyberpunk)
    float time = GetTime();
    DrawRing((Vector2){avX, avY}, avR - 5, avR + 5, time * 50, (time * 50) + 280, 32, PINK);
    DrawCircle(avX, avY, avR - 10, (Color){40, 20, 60, 255});
    
    // Teks inisial di dalam avatar
    DrawText("DEV", avX - 25, avY - 10, 24, WHITE);

    // Detail Profil
    int textX = avX + 100;
    DrawText("Afriza C.S", textX, cardY + 60, 36, WHITE);
    DrawText("NIM : 241524002", textX, cardY + 105, 20, PINK);

    DrawLine(textX, cardY + 140, cardX + cardW - 40, cardY + 140, (Color){100, 50, 150, 255});

    DrawText("Mata Kuliah : Grafika Komputer", textX, cardY + 160, 18, LIGHTGRAY);
    DrawText("Topik       : DDA & Bresenham Line", textX, cardY + 190, 18, LIGHTGRAY);
    DrawText("Framework   : Raylib 5.5 (Bahasa C)", textX, cardY + 220, 18, LIGHTGRAY);

    // Daftar Program/Algoritma (Pill Badges)
    int sumY = cardY + cardH + 30;
    const char *pLabels[] = {"DDA", "Bresenham", "Midcircle", "Bezier", "Raylib UI"};
    Color pColors[] = {SKYBLUE, GREEN, ORANGE, MAGENTA, YELLOW};

    int startX = SCREEN_W/2 - 275;
    for (int i = 0; i < 5; i++) {
        int pillW = MeasureText(pLabels[i], 16) + 40;
        DrawRectangleRounded((Rectangle){startX, sumY, pillW, 35}, 0.5f, 10, (Color){20, 20, 20, 255});
        DrawRectangleRoundedLines((Rectangle){startX, sumY, pillW, 35}, 0.5f, 10, pColors[i]);
        DrawText(pLabels[i], startX + 20, sumY + 10, 16, pColors[i]);
        startX += pillW + 15;
    }

    DrawText("Tekan [ESC] atau Klik BACK untuk kembali", 20, SCREEN_H - 30, 14, GRAY);
}