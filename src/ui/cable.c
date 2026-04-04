#include "src/ui/cable.h"

// Fungsi untuk menggambar kabel melengkung yang tebal
static void DrawThickBezierCable(Vector2 start, Vector2 control, Vector2 end, int thickness, Color color) {
    const int segments = 20; // Jumlah garis kecil untuk membentuk kurva
    Vector2 previousPoint = start;

    for (int i = 1; i <= segments; i++) {
        float t = (float)i / (float)segments;
        Vector2 currentPoint = GetQuadraticBezierPoint(start, control, end, t);
        
        DDA_ThickLine((int)previousPoint.x, (int)previousPoint.y, 
                      (int)currentPoint.x, (int)currentPoint.y, 
                      thickness, color);
        
        previousPoint = currentPoint;
    }
}

// Gambar Capit (Mekanisme Red Gummy/Cartoon dengan Kabel Melengkung)
void drawCable(float clawX, float clawY){

    // 1. Tali (Wire Vertikal)
    DDA_ThickLine((int)clawX, 52, (int)clawX, (int)clawY - 35, 3, (Color){58, 5, 25, 255}); 

    // 2. Kabel Penyangga (Horizontal Melengkung)
    Vector2 cableStart = { 20.0f, 40.0f };         
    Vector2 cableEnd = { clawX, 40.0f };

    float distX = fabsf(cableEnd.x - cableStart.x);

    // Mekanisme kelenturan kabel.
    // Semakin deket capit ke kiri (distX kecil), kabel semakin melengkung ke bawah.
    // Semakin jauh ke kanan, kabel semakin lurus menegang.
    float maxSlack = 200.0f;                   // Lengkungan maksimal saat capit di paling kiri
    float slack = maxSlack - (distX * 0.15f); // Jarak X mengurangi kelenturan
    if (slack < 0.0f) slack = 0.0f;           // mencegah kabel melengkung ke atas

    // Titik kontrol Bezier (berada di tengah horizontal, ditarik ke bawah oleh slack)
    Vector2 controlPoint = {
        (cableStart.x + cableEnd.x) / 2.0f,
        (cableStart.y + cableEnd.y) / 2.0f + slack
    };

    DrawThickBezierCable(cableStart, controlPoint, cableEnd, 4, (Color){58, 5, 25, 255});
}
