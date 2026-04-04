#include "src/ui/indikatorStatus.h"

void DrawIndikatorStatus(ClawState state) {
    const char* statusText = "";
    Color statusColor = WHITE;

    // Tentukan teks dan warna berdasarkan state mesin capit
    if (state == STATE_IDLE) { statusText = "STATUS: SIAP"; statusColor = GREEN; }
    else if (state == STATE_DROPPING) { statusText = "STATUS: TURUN"; statusColor = YELLOW; }
    else if (state == STATE_GRABBING) { statusText = "STATUS: MENGAMBIL"; statusColor = ORANGE; }
    else if (state == STATE_RETURNING) { statusText = "STATUS: NAIK"; statusColor = SKYBLUE; }
    else if (state == STATE_MOVING_HOME) { statusText = "STATUS: KE LUBANG"; statusColor = MAGENTA; }
    else if (state == STATE_RELEASING) { statusText = "STATUS: MELEPAS"; statusColor = RED; }

    // Gambar Layar Digital / Panel untuk Status
    Rectangle statusPanel = {SCREEN_W/2 - 75, 20, 200, 60};
    DrawRectangleRounded(statusPanel,  0.3f, 5, (Color){0, 0, 0, 120});
    DrawRectangleRoundedLines(statusPanel, 0.3f, 10, statusColor);         

    // Gambar kaca lubang hadiah
    DrawRectangleRounded((Rectangle){60, 474, 113,85}, 0.4f, 5, (Color){0, 0, 0, 150}); //kaca lubang hadiah
    DrawRectangleRoundedLines((Rectangle){60, 474, 113, 93}, 0.4f, 20, statusColor);

    // Gambar garis pembatas tengah (untuk estetika)
    DrawRectangle(60, 456, 172, 18, (Color){241, 201, 59, 255}); //hijau agak kuning
    DrawRectangle(58, 474, 120, 25, (Color){241, 201, 59, 255}); 
   
    // GAMBAR LAMPU KIRI & KANAN 
    DrawLampu((Rectangle){12, 280, 36, 156}, 0.4f, statusColor);
    DrawLampu((Rectangle){SCREEN_W - 48, 280, 36, 156}, 0.4f, statusColor);

    // GAMBAR LAMPU ATAS 
    for (int i = 0; i < 5; i++) {
        float posisiX = 110.0f + (i * 120.0f);
        DrawLampu((Rectangle){posisiX, 10, 100, 8}, 1.0f, statusColor);
    }

    // Cetak teks status di atas panel (ditengah kotak)
    DrawText(statusText, (int)statusPanel.x + 17, (int)statusPanel.y + 23, 16, statusColor);
}