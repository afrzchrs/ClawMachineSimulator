#include "src/ui/bodyMesin.h"

extern int wireframeMode;

void DrawWireframeRect(int x, int y, int w, int h, Color color) {
    DDALine(x, y, x + w, y, color);           // Garis atas
    DDALine(x + w, y, x + w, y + h, color);   // Garis kanan
    DDALine(x + w, y + h, x, y + h, color);   // Garis bawah
    DDALine(x, y + h, x, y, color);           // Garis kiri
}

void efekBgMiring(void){
    float currentTime = GetTime();
    Color gridColor = (Color){250, 227, 146, 60}; 
    
    int speedGrid = 30; 
    int spacing = 40; 
    
    int offset = (int)(currentTime * speedGrid) % spacing; 

    int batasAwal = -SCREEN_H;
    int batasAkhir = SCREEN_W + SCREEN_H;

    for (int i = batasAwal; i <= batasAkhir; i += spacing) {
        int x1 = i + offset;
        int y1 = 0;
        int x2 = i + offset + SCREEN_H; 
        int y2 = SCREEN_H;
        
        DDA_ThickLine(x1, y1, x2, y2, 2, gridColor); 
    }
}

void efekBgDown(void){
    float currentTime = GetTime();
    Color gridColor = (Color){250, 227, 146, 50}; 
    
    int speedGrid = 30; 
    int offset = (int)(currentTime * speedGrid) % 40; 

    for (int i = 0; i <= SCREEN_W; i += 40) {
        DDA_ThickLine(i, 0, i, SCREEN_H, 2, gridColor); 
    }
    
    for (int i = -40; i <= SCREEN_H; i += 40) {
        DDA_ThickLine(0, i + offset, SCREEN_W, i + offset, 2, gridColor); 
    }
}

void efekBg(int type){
    if(type == 1) efekBgMiring();
    else if(type == 2) efekBgDown();
}

void DrawBodyMesin(float clawX, float clawY, float dropX) {
    if (wireframeMode) {
        // Background hitam agar garis terlihat jelas
        ClearBackground(BLACK);

        // Grid background 
        efekBgDown(); 

        // Warna garis kerangka mesin capit
        Color wfColor = LIME; 

        // Area Kaca / Play Area
        DrawWireframeRect(60, 40, SCREEN_W - 120, 420, RAYWHITE);
        // Pilar Atas Full
        DrawWireframeRect(60, 0, SCREEN_W - 120, 40, wfColor);
        // Pilar Kiri & Kanan COklat bawah
        DrawWireframeRect(0, 0, 60, 456, wfColor);
        DrawWireframeRect(SCREEN_W - 60, 0, 60, 456, wfColor);
        // Pilar putih bagian dalam kiri & kanan
        DrawWireframeRect(0, 56, 60, 200, YELLOW);
        DrawWireframeRect(SCREEN_W - 60, 56, 60, 200, YELLOW);
        // Strip ijo (tengah)
        DrawWireframeRect(0, 250, 60, 15, YELLOW);
        DrawWireframeRect(SCREEN_W-60, 250, 60, 15, YELLOW);
        // Strip kecil atas
        DrawWireframeRect(0, 50, 20, 10, YELLOW);
        DrawWireframeRect(SCREEN_W-60, 50, 60, 10, YELLOW);
        // Rel kaca atas
        DrawWireframeRect(60, 35, SCREEN_W - 120, 5, RED);
        // Garis Pembatas / Lantai Mesin
        DrawWireframeRect(0, 456, SCREEN_W, 18, YELLOW);
        // Body mesin bawah 
        DrawWireframeRect(0, 474, SCREEN_W, 200, wfColor);
        // Control Panel Bawah
        DrawWireframeRect(198, 540, SCREEN_W - 270, 90, GREEN);
        // Control Panel Base
        DrawWireframeRect(198, 480, SCREEN_W - 270, 90, LIME);
        // Tembok pembatas drop area dan prize area
        DrawWireframeRect(60, 474, 113, 93, wfColor); 
        
        // Pembatas dalam (DDA_ThickLine akan menjadi tipis berkat dda.c sebelumnya)
        DDA_ThickLine(180, 380, 180, 470, 16, YELLOW);
        
        DrawText("DROP", (int)dropX - 20, 410, 16, YELLOW);
        
        return; 
    }
    
    // Background Utama (Abu-abu terang)
    ClearBackground((Color){26, 93, 26, 255});

    // Area Kaca / Play Area (Putih)
    DrawRectangleGradientV(60, 40, SCREEN_W - 120, 420, (Color){251, 216, 93, 255}, (Color){26, 93, 26, 255});
    efekBgDown(); 
    
    // Pilar Atas Full
    DrawRectangle(60, 0, SCREEN_W - 120, 40, (Color){26, 93, 26, 255});

    // Pilar Atas kiri Strip ijo
    DrawRectangle(0, 250, 60, 15, (Color){241, 201, 59, 255});
    // Pilar Atas kanan Strip ijo
    DrawRectangle(SCREEN_W-60, 250, 60, 15, (Color){241, 201, 59, 255});

    // Pilar Kiri COklat bawah
    DrawRectangle(0, 0, 60, 456, (Color){26, 93, 26, 255});
    // Kanan (Coklat) bawah
    DrawRectangle(SCREEN_W - 60, 0, 60, 456, (Color){26, 93, 26, 255}); 
    //pilar putih bagian dalam pilar kiri 
    DrawRectangleGradientV(0, 56, 60, 200, (Color){250, 227, 146, 255}, (Color){238, 147, 34, 255});  
    //pilar putih bagian dalam pilar kanan 
    DrawRectangleGradientV(SCREEN_W - 60, 56, 60, 200, (Color){250, 227, 146, 255}, (Color){238, 147, 34, 255}); 

    // Pilar bawah kiri Strip ijo
    DrawRectangle(0, 250, 60, 15, (Color){241, 201, 59, 255});
    // Pilar bawah kanan Strip ijo
    DrawRectangle(SCREEN_W-60, 250, 60, 15, (Color){241, 201, 59, 255});

    // Pilar Atas kiri
    DrawRectangle(0, 50, 20, 10, (Color){241, 201, 59, 255});
    // Pilar Atas kanan
    DrawRectangle(SCREEN_W-60, 50, 60, 10, (Color){241, 201, 59, 255});

    //rel kaca atas (Hitam)
    DrawRectangle(60, 35, SCREEN_W - 120, 5, (Color){58, 5, 25, 255}); 
    
    // Garis Pembatas / Lantai Mesin (Hijau Kekuningan)
    DrawRectangle(0, 456, SCREEN_W, 18, (Color){241, 201, 59, 255});

    //BOdy mesin bawah 
    DrawRectangleGradientV(0, 474, SCREEN_W, 200, (Color){241, 201, 59, 255}, (Color){26, 93, 26, 255});
    
    // Control Panel Bawah
    Rectangle panelRec2 = {198, 540, SCREEN_W - 270, 90};
    DrawRectangleRounded(panelRec2, 0.2f, 10, (Color){54, 115, 53, 255});

    // Control Panel Base (Panel Hijau di bawah)
    Rectangle panelRec = {198, 480, SCREEN_W - 270, 90};
    DrawRectangleRounded(panelRec, 0.2f, 10, (Color){76, 155, 67, 255});

    // Gambar Drop Area (Lubang Hadiah) pake DDA
    // TEmobvk pembatas drop area dan prize area
    DrawRectangleRounded((Rectangle){60, 474, 113, 93}, 0.4f, 10, (Color){26,93,26,255}); 
    DDA_ThickLine(180, 380, 180, 470, 16, (Color){241, 201, 59, 255});
    
    // Teks area
    DrawText("DROP", (int)dropX - 20, 410, 16, YELLOW);
}
