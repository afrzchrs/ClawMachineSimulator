#include "model.h"
void DrawModelScreen(void) {
    // Background biru gelap ala Blueprint
    ClearBackground((Color){10, 20, 40, 255});

    // Gambar grid ala kertas teknik
    for (int i = 0; i < SCREEN_W; i += 40) {
        DrawLine(i, 0, i, SCREEN_H, (Color){30, 60, 100, 150});
    }
    for (int i = 0; i < SCREEN_H; i += 40) {
        DrawLine(0, i, SCREEN_W, i, (Color){30, 60, 100, 150});
    }

    // Header transparan
    DrawRectangle(0, 0, SCREEN_W, 60, (Color){0, 0, 0, 180});
    DrawBackButton();
    DrawText("MODEL ARCHITECTURE - Mekanisme Capit", 135, 18, 22, (Color){100, 200, 255, 255});
    DrawLine(0, 60, SCREEN_W, 60, (Color){100, 200, 255, 255});

    // Animasi putaran/buka-tutup untuk pameran model
    float time = GetTime();
    float wave = (sinf(time * 2.0f) + 1.0f) / 2.0f; 
    float offset = 12.0f + (wave * 13.0f);

    // Render capit ukuran raksasa di tengah menggunakan Camera2D
    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0.0f, 0.0f };
    camera.offset = (Vector2){ SCREEN_W / 2.0f, SCREEN_H / 2.0f - 50 }; 
    camera.rotation = 0.0f;
    camera.zoom = 4.0f; 

    BeginMode2D(camera);
        DrawClaw(0, 0, offset,0); 
    EndMode2D();

    // Teks Informasi Teknis di Kiri dan Kanan
    DrawRectangleRounded((Rectangle){20, 100, 200, 120}, 0.1f, 10, (Color){0, 0, 0, 150});
    DrawText("LENGAN (ARM)", 35, 115, 18, SKYBLUE);
    DrawText("- Rentang: 12px - 25px", 35, 145, 14, LIGHTGRAY);
    DrawText("- Algoritma: DDA Thick", 35, 165, 14, LIGHTGRAY);
    DrawText("- Sudut Dinamis: Ya", 35, 185, 14, LIGHTGRAY);

    DrawRectangleRounded((Rectangle){SCREEN_W - 220, 100, 200, 120}, 0.1f, 10, (Color){0, 0, 0, 150});
    DrawText("ENGSEL (JOINT)", SCREEN_W - 205, 115, 18, SKYBLUE);
    DrawText("- Pusat X: Statis", SCREEN_W - 205, 145, 14, LIGHTGRAY);
    DrawText("- Pusat Y: Y + 5.0f", SCREEN_W - 205, 165, 14, LIGHTGRAY);
    DrawText("- Algoritma: Midcircle", SCREEN_W - 205, 185, 14, LIGHTGRAY);

    DrawText("[ESC/BACKSPACE] Kembali ke Menu Utama", 20, SCREEN_H - 30, 16, DARKGRAY);
}
