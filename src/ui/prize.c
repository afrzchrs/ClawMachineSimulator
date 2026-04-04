#include "src/ui/prize.h"

void DrawPrize(Prize p) {
    if (p.isWon) return; 

    // JIKA OBJEK ADALAH BOLA HADIAH NORMAL tupe 0
    if (p.type == 0) {
    MidcircleFilled((int)p.x, (int)p.y, p.radius, p.color);

    if (p.color.r == RED.r && p.color.g == RED.g && p.color.b == RED.b) {
        DDA_ThickLine((int)p.x - p.radius + 2, (int)p.y, 
                      (int)p.x + p.radius - 2, (int)p.y, 3, WHITE);
        MidcircleFilled((int)p.x, (int)p.y, p.radius / 3, RAYWHITE);
        MidcircleThick((int)p.x, (int)p.y, p.radius / 3, 2, BLACK);
    } 
    else if (p.color.r == GREEN.r && p.color.g == GREEN.g && p.color.b == GREEN.b) {
        MidcircleThick((int)p.x, (int)p.y, (int)(p.radius * 0.6f), 2, RAYWHITE);
        MidcircleThick((int)p.x, (int)p.y, (int)(p.radius * 0.2f), 2, RAYWHITE);
    }
    else if (p.color.r == SKYBLUE.r && p.color.g == SKYBLUE.g && p.color.b == SKYBLUE.b) {
        MidcircleFilled((int)p.x, (int)p.y, (int)(p.radius * 0.55f), WHITE);
        MidcircleFilled((int)p.x, (int)p.y, (int)(p.radius * 0.25f), BLACK);
        MidcircleFilled((int)p.x + 3, (int)p.y - 3, 2, WHITE);
    }
    else {
        int offset = (int)(p.radius * 0.707f); 
        DDA_ThickLine((int)p.x - offset, (int)p.y - offset, 
                      (int)p.x + offset, (int)p.y + offset, 4, WHITE);
        DDA_ThickLine((int)p.x - offset, (int)p.y + offset, 
                      (int)p.x + offset, (int)p.y - offset, 4, WHITE);
    }
    MidcircleThick((int)p.x, (int)p.y, p.radius, 2, BLACK);
    }
    
    // JIKA OBJEK ADALAH BATU tipe 1
    if (p.type == 1) {
        int x = (int)p.x;
        int y = (int)p.y;
        int r = p.radius;
        
        // Buat warna isi batu agar tidak transparan (pakai lingkaran dasar)
        MidcircleFilled(x, y, r - 2, p.color);
        
        // Titik-titik sudut tak beraturan untuk membuat bentuk batu
        int p1x = x - r + 4, p1y = y - r + 8;
        int p2x = x + r - 8, p2y = y - r + 2;
        int p3x = x + r + 2, p3y = y + 4;
        int p4x = x + r - 6, p4y = y + r - 2;
        int p5x = x - r + 8, p5y = y + r;
        int p6x = x - r - 2, p6y = y + 2;
        
        // Menggambar garis pinggir batu agar terlihat kasar dan bersudut
        DDA_ThickLine(p1x, p1y, p2x, p2y, 4, BLACK);
        DDA_ThickLine(p2x, p2y, p3x, p3y, 4, BLACK);
        DDA_ThickLine(p3x, p3y, p4x, p4y, 4, BLACK);
        DDA_ThickLine(p4x, p4y, p5x, p5y, 4, BLACK);
        DDA_ThickLine(p5x, p5y, p6x, p6y, 4, BLACK);
        DDA_ThickLine(p6x, p6y, p1x, p1y, 4, BLACK);
        
        // Garis retakan di tengah batu
        DDA_ThickLine(p6x + 4, p6y + 2, p3x - 6, p3y - 4, 2, BLACK);
        DDA_ThickLine(x, y, p5x + 4, p5y - 4, 2, BLACK);
        
        return; 
    }

    // JIKA OBJEK ADALAH BONEKA BERUANG tipe 2
    if (p.type == 2) {
        int x = (int)p.x;
        int y = (int)p.y;
        
        // Warna Dinamis
        Color baseColor = p.color; 
        Color darkColor = BLACK; // Warna bayangan
        Color stitchColor = BLACK;

        // 1. Telinga (Kiri & Kanan)
        MidcircleFilled(x - 12, y - 14, 8, darkColor);
        MidcircleFilled(x - 12, y - 14, 6, baseColor); 
        MidcircleFilled(x + 12, y - 14, 8, darkColor);
        MidcircleFilled(x + 12, y - 14, 6, baseColor);

        // 2. Tangan & Kaki 
        DDA_ThickLine(x - 12, y, x - 22, y + 8, 10, darkColor); // Tangan kiri
        DDA_ThickLine(x + 12, y, x + 22, y + 8, 10, darkColor); // Tangan kanan
        DDA_ThickLine(x - 8, y + 10, x - 14, y + 24, 12, baseColor); // Kaki kiri
        DDA_ThickLine(x + 8, y + 10, x + 14, y + 24, 12, baseColor); // Kaki kanan

        // 3. Badan & Kepala (Abstraksi Gabungan Lingkaran)
        MidcircleFilled(x, y + 6, 16, baseColor); // Badan
        MidcircleFilled(x, y - 6, 14, baseColor); // Kepala
        
        // 4. Detail Wajah (Moncong & Mata)
        MidcircleFilled(x, y - 2, 7, RAYWHITE); // Moncong putih
        DrawPixel(x - 2, y - 3, BLACK); // Hidung
        DrawPixel(x + 2, y - 3, BLACK);
        DrawPixel(x, y - 4, BLACK);
        DDA_ThickLine(x - 6, y - 8, x - 4, y - 10, 2, BLACK); // Mata merem (garis miring)
        DDA_ThickLine(x + 4, y - 10, x + 6, y - 8, 2, BLACK);

        // 5. TEKSTUR JAHITAN MANUAL (Poin Penting untuk Akurasi Koordinat)
        // Membuktikan penggunaan loop dan koordinat presisi untuk tekstur
        for (int i = -8; i <= 8; i += 4) {
            // Jahitan melintang di perut
            DDA_ThickLine(x + i - 2, y + 10, x + i + 2, y + 10, 2, stitchColor); 
            DDA_ThickLine(x + i, y + 8, x + i, y + 12, 2, stitchColor);     
        }
        // Jahitan vertikal di dahi
        DDA_ThickLine(x, y - 18, x, y - 12, 2, stitchColor);
        DDA_ThickLine(x - 2, y - 16, x + 2, y - 16, 2, stitchColor);
        DDA_ThickLine(x - 2, y - 14, x + 2, y - 14, 2, stitchColor);

        return; 
    }

}