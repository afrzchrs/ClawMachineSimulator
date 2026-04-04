#include "src/screens/menu.h"
#include "screen_type.h"
#include "raylib.h"

static int clickedProgram = 0;

Camera2D konfigurasi(void){
    Camera2D camera = { 0 };
    camera.target = (Vector2){ 115.0f, 80.0f };  
    camera.offset = (Vector2){ 550.0f, 250.0f }; 
    camera.rotation = 0.0f;
    camera.zoom = 2.0f; 
    return camera;
}

void clawMenu(void) {
    float time = GetTime();

    float menuClawY = 80.0f + sinf(time * 2.0f) * 15.0f; 

    float gelombang = (sinf(time * 2.0f) + 1.0f) / 2.0f; 
    float menuArmOffset = 12.0f + (gelombang * 13.0f);

    Camera2D camera = konfigurasi();

    BeginMode2D(camera);
        DrawClaw(-30.0f, menuClawY + 35, menuArmOffset, 0); 
    EndMode2D();
}


int GetClickedProgram(void) {
    int result = clickedProgram;
    clickedProgram = 0; 
    return result;
}

void DrawMenu(void) {
    // bg
    DrawRectangleGradientV(0, 0, SCREEN_W, SCREEN_H, (Color){251, 216, 93, 255}, (Color){26, 93, 26, 255});
    
    //efek
    efekBgMiring(); 

    Vector2 mouse = GetMousePosition();
    int mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    // judul
    int titleX = 80; 
    int titleY = 80; 
    int fontSize = 50;

    // Gambar bayangan teks 
    DrawText("SIMULATOR", titleX + 4, titleY + 4, fontSize, (Color){0, 0, 0, 150});
    DrawText("CLAW MACHINE", titleX + 4, titleY + 55 + 4, fontSize, (Color){0, 0, 0, 150});

    // Gambar teks utama
    DrawText("SIMULATOR", titleX, titleY, fontSize, LIME); // Warna hijau neon
    DrawText("CLAW MACHINE", titleX, titleY + 55, fontSize, WHITE);

    // Garis dekorasi di bawah judul
    DrawRectangle(titleX, titleY + 120, 350, 4, LIME);

    // RENDER TOMBOL
    int btnW = 220; 
    int btnH = 60;  
    int btnX = SCREEN_W - btnW - 80;
    int startY = 180; 
    int spacing = 25; 

    // Data Tombol: Label teks 
    const char* btnLabels[] = {"Simulasi", "Model", "About", "Exit"};
    int btnCodes[] = {10, 20, 99, -1};
    int numBtns = 4;

    for (int i = 0; i < numBtns; i++) {
        int yPos = startY + (i * (btnH + spacing));
        
        // Buat area deteksi tabrakan (Collision Box)
        Rectangle hitbox = {btnX, yPos, btnW, btnH};
        int isHovered = CheckCollisionPointRec(mouse, hitbox);

        // hiver efek
        int turun = isHovered ? 4 : 0;
        
        // Warna dinamis
        Color baseColor = (Color){80, 80, 80, 255};      // Abu-abu gelap 
        Color topColor  = isHovered ? LIGHTGRAY : RAYWHITE; // Putih terang/Abu muda
        Color textColor = isHovered ? (Color){30, 100, 30, 255} : BLACK; // Teks hijau gelap saat hover

        // Exit
        if (i == 3) {
            topColor = isHovered ? (Color){255, 100, 100, 255} : (Color){220, 80, 80, 255};
            baseColor = (Color){130, 30, 30, 255};
            textColor = WHITE;
        }

        // Gambar Base/Bayangan 
        DrawRectangleRounded((Rectangle){btnX, yPos + 6, btnW, btnH}, 0.3f, 10, baseColor);

        // Gambar Top/Permukaan
        DrawRectangleRounded((Rectangle){btnX, yPos + turun, btnW, btnH}, 0.3f, 10, topColor);

        // Gambar Teks di tengah tombol
        int textW = MeasureText(btnLabels[i], 22);
        DrawText(btnLabels[i], btnX + (btnW / 2) - (textW / 2), yPos + 20 + turun, 22, textColor);

        // Logika Interaksi
        if (isHovered && mousePressed) {
            clickedProgram = btnCodes[i];
        }
    }
    clawMenu();
}