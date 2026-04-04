#include "src/ui/drawClaw.h"

Color mainRed = (Color){230, 0, 0, 255};      // Merah cerah
Color darkRed = (Color){150, 0, 0, 255};      // Merah gelap
Color silver = (Color){200, 200, 200, 255};   // Perak 

void DrawClaw(float clawX, float clawY, float armOffset, int type) {
    if (type == 1) {
        drawCable(clawX, clawY); 
        //Gambar roda penggerak capit (perak bordernya gelap)
        DrawCircle((int)clawX, 40, 15, (Color){58, 5, 25, 255}); 
        DrawCircle((int)clawX, 40, 12, silver);   
    }

    // Gambar mesin penggerak capit merah
    DrawRectangleRounded((Rectangle){clawX - 25, clawY - 35, 50, 40}, 0.5f, 10, mainRed); 

    // Gambar mesin penggerak capit merah gelap
    DrawRectangleRounded((Rectangle){clawX - 18, clawY - 23, 36, 15}, 0.5f, 10, darkRed);

    // 5. Konfigurasi Lengan Capit (Hanya 2 lengan)
    float openAngle = (armOffset / 25.0f) * 0.4f; 
    float armLen = 40.0f; // Panjang lengan bagian atas
    float tipLen = 40.0f; // Panjang ujung lengan 

    // TITIK ENGSEL UTAMA DI ATAS 
    float pivotX = clawX;
    float pivotY = clawY + 5.0f;

    // LENGAN KIRI
    float angle1 = PI / 2.0f + 0.5f + openAngle;

    float mid1X = pivotX + armLen * cosf(angle1);
    float mid1Y = pivotY + armLen * sinf(angle1);
    float tip1X = mid1X + tipLen * cosf(angle1 - 0.8f); // Melengkung ke arah dalam (kanan)
    float tip1Y = mid1Y + tipLen * sinf(angle1 - 0.8f);

    // Gambar batang lengan kiri
    DDA_ThickLine((int)pivotX, (int)pivotY, (int)mid1X, (int)mid1Y, 8, darkRed);
    DDA_ThickLine((int)mid1X, (int)mid1Y, (int)tip1X, (int)tip1Y, 8, darkRed);

    // LENGAN KANAN
    float angle2 = PI / 2.0f - 0.5f - openAngle; // Arahnya kebalikan dari lengan kiri

    float mid2X = pivotX + armLen * cosf(angle2);
    float mid2Y = pivotY + armLen * sinf(angle2);
    float tip2X = mid2X + tipLen * cosf(angle2 + 0.8f); // Melengkung ke arah dalam (kiri)
    float tip2Y = mid2Y + tipLen * sinf(angle2 + 0.8f);

    // Gambar batang lengan kanan
    DDA_ThickLine((int)pivotX, (int)pivotY, (int)mid2X, (int)mid2Y, 8, darkRed);
    DDA_ThickLine((int)mid2X, (int)mid2Y, (int)tip2X, (int)tip2Y, 8, darkRed);

    // 6. GAMBAR ENGSEL (Digambar terakhir)
    
    // Engsel Atas (Pusat pertemuan lengan kiri dan kanan)
    DrawCircle((int)pivotX, (int)pivotY, 6, darkRed); // Bayangan luar
    DrawCircle((int)pivotX, (int)pivotY, 4, silver);  // Pin perak di tengah

    // Engsel Tengah Kiri 
    DrawCircle((int)mid1X, (int)mid1Y, 5, darkRed);
    DrawCircle((int)mid1X, (int)mid1Y, 3, silver);

    // Engsel Tengah Kanan 
    DrawCircle((int)mid2X, (int)mid2Y, 5, darkRed);
    DrawCircle((int)mid2X, (int)mid2Y, 3, silver);
}