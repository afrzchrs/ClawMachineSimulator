#include "src/screens/model.h"

static int currentModelIndex = 0; 
#define TOTAL_MODELS 7

void TeksInfo(int index){
    if (index == 0) {
        // Teks Informasi Teknis Capit
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
    } else {
        // Teks Informasi Teknis Hadiah di bawah layar
        DrawRectangleRounded((Rectangle){SCREEN_W/2 - 200, 460, 400, 90}, 0.1f, 10, (Color){0, 0, 0, 180});
        
        // Indeks 1 sampai 4 adalah jenis Bola Biasa (Hanya beda warna)
        if (index >= 1 && index <= 4) {
            DrawText("SPEC: BOLA", SCREEN_W/2 - 90, 475, 18, VIOLET);
            DrawText("- Algo: Midcircle / Midpoint Filled", SCREEN_W/2 - 180, 505, 16, LIGHTGRAY);
            DrawText("- Variant: Standard Plastic Capsule", SCREEN_W/2 - 180, 525, 16, LIGHTGRAY);
        } else if (index == 5) {
            DrawText("SPEC: BATU", SCREEN_W/2 - 90, 475, 18, ORANGE);
            DrawText("- Algo: Midcircle & Intersection Lines", SCREEN_W/2 - 180, 505, 16, LIGHTGRAY);
            DrawText("- Variant: High-Mass Object / Obstacle", SCREEN_W/2 - 180, 525, 16, LIGHTGRAY);
        } else if (index == 6) {
            DrawText("SPEC: BONEKA", SCREEN_W/2 - 80, 475, 18, BROWN);
            DrawText("- Algo: Composite Midcircle & DDA", SCREEN_W/2 - 180, 505, 16, LIGHTGRAY);
            DrawText("- Variant: Soft Fabric / Doll", SCREEN_W/2 - 180, 525, 16, LIGHTGRAY);
        }
    }

    // Indikator Halaman 1/7, 2/7, dst
    DrawText(TextFormat("Model %d of %d", index + 1, TOTAL_MODELS), SCREEN_W - 130, SCREEN_H - 30, 16, GRAY);
    DrawText("[ESC/BACKSPACE] Kembali ke Menu Utama", 20, SCREEN_H - 30, 16, DARKGRAY);
}

void DrawModelScreen(void) {
    // Navigasi kiri kanan
    if (IsKeyPressed(KEY_RIGHT)) {
        currentModelIndex++;
        if (currentModelIndex >= TOTAL_MODELS) currentModelIndex = 0; 
    }
    if (IsKeyPressed(KEY_LEFT)) {
        currentModelIndex--;
        if (currentModelIndex < 0) currentModelIndex = TOTAL_MODELS - 1; 
    }

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

    float time = GetTime();
    float wave = (sinf(time * 2.0f) + 1.0f) / 2.0f; 
    float offset = 12.0f + (wave * 13.0f);


    // Inisialisasi Data Objek sesuai urutan yang kamu berikan
    Prize BolaBiru   = { 0, 0, 24, SKYBLUE, 0, 0, 0 }; 
    Prize BolaMerah  = { 0, 0, 24, RED, 0, 0, 0 };   
    Prize BolaIjo    = { 0, 0, 24, GREEN, 0, 0, 0 }; 
    Prize BolaViolet = { 0, 0, 24, VIOLET, 0, 0, 0 }; 
    Prize Batu       = { 0, 0, 22, DARKGRAY, 0, 0, 1 }; 
    Prize Boneka     = { 0, 0, 24, BROWN, 0, 0, 2 };    

    // SATU KAMERA DI TENGAH
    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0.0f, 0.0f };
    camera.offset = (Vector2){ SCREEN_W / 2.0f, SCREEN_H / 2.0f }; 
    camera.rotation = 0.0f;
    camera.zoom = 4.0f; 

    BeginMode2D(camera);
        // Render objek berdasarkan currentModelIndex
        switch(currentModelIndex) {
            case 0: {
                float wave = (sinf(time * 2.0f) + 1.0f) / 2.0f; 
                float offset = 12.0f + (wave * 13.0f); 
                DrawClaw(0, -10.0f, offset, 0); 
                break;
            }
            case 1: DrawPrize(BolaBiru); break;
            case 2: DrawPrize(BolaMerah); break;
            case 3: DrawPrize(BolaIjo); break;
            case 4: DrawPrize(BolaViolet); break;
            case 5: DrawPrize(Batu); break;
            case 6: DrawPrize(Boneka); break;
        }
    EndMode2D();

    // Render Teks Judul di tengah
    const char* judulTeks = "";
    Color warnaTeks = WHITE;

    if (currentModelIndex == 0) { judulTeks = "MESIN CAPIT"; warnaTeks = SKYBLUE; }
    else if (currentModelIndex == 1) { judulTeks = "BOLA BIRU (Type 0)"; warnaTeks = SKYBLUE; }
    else if (currentModelIndex == 2) { judulTeks = "BOLA MERAH (Type 0)"; warnaTeks = RED; }
    else if (currentModelIndex == 3) { judulTeks = "BOLA HIJAU (Type 0)"; warnaTeks = GREEN; }
    else if (currentModelIndex == 4) { judulTeks = "BOLA UNGU (Type 0)"; warnaTeks = VIOLET; }
    else if (currentModelIndex == 5) { judulTeks = "BATU (Type 1)"; warnaTeks = ORANGE; }
    else if (currentModelIndex == 6) { judulTeks = "BONEKA (Type 2)"; warnaTeks = BROWN; }

    DrawText(judulTeks, 
             SCREEN_W/2 - MeasureText(judulTeks, 20)/2, 
             SCREEN_H/2 + 120, 
             20, 
             warnaTeks);

    // --- ANIMASI TEKS NAVIGASI BERKEDIP ---
    int alpha = (int)(155 + 100 * sinf(time * 5.0f)); 
    Color navColor = (Color){255, 255, 255, alpha};
    DrawText("< LEFT", 40, SCREEN_H/2 - 10, 20, navColor);
    DrawText("RIGHT >", SCREEN_W - 120, SCREEN_H/2 - 10, 20, navColor);

    // Render Box Teks Spesifikasi Teknis
    TeksInfo(currentModelIndex);
}
