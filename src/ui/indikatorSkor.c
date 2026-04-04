#include "src/ui/indikatorSkor.h"

// Fungsi untuk menggambar Indikator Skor
void DrawIndikatorSkor(Prize prizes[MAX_PRIZES]) {
    int score = 0;
    for (int i = 0; i < MAX_PRIZES; i++) {
        if (prizes[i].isWon) {
            if (prizes[i].type == 1) {
                score -= 50; 
            } else if (prizes[i].type == 2) {
                score += 30; 
            } else {
                score += 10; 
            }
        }
    }

    // gambar Layar Digital / Panel untuk Skor
    Rectangle scorePanel = {220, SCREEN_H - 105, 150, 60};
    DrawRectangleRounded(scorePanel, 0.3f, 5, (Color){0, 0, 0, 150}); 
    
    // Ubah warna teks skor berdasarkan apakah nilainya minus atau tidak
    Color scoreColor = (score < 0) ? RED : (score > 0 ? GREEN : YELLOW);
    
    // Cetak border skor & teksnya
    DrawRectangleRoundedLines(scorePanel, 0.3f, 5, scoreColor);
    DrawText(TextFormat("SKOR: %d", score), (int)scorePanel.x + 30, (int)scorePanel.y + 20, 20, scoreColor);
}