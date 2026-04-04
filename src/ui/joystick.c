#include "src/ui/joystick.h"

void DrawJoyStick(float clawX, float dropX) {
    int joyBaseX = SCREEN_W / 2 + 25;
    int joyBaseY = 523;
    int knobX = joyBaseX;
    int knobY = joyBaseY - 55;

    if (IsKeyDown(KEY_LEFT) && clawX > dropX) {
        knobX -= 20; 
        knobY += 8;  
    } else if (IsKeyDown(KEY_RIGHT) && clawX < SCREEN_W - 50) {
        knobX += 20; 
        knobY += 8;
    }

    // Bayangan/ketebalan dudukan (di-offset sedikit ke bawah)
    DrawCircle(joyBaseX, joyBaseY + 4, 34, GRAY); 
    // Dudukan utama (abu-abu terang)
    DrawCircle(joyBaseX, joyBaseY, 32, LIGHTGRAY);
    
    // Lubang masuknya tiang (abu-abu sangat gelap/hitam)
    DrawCircle(joyBaseX, joyBaseY, 14, DARKGRAY); 

    // Slot pergerakan (dibuat gelap agar terlihat seperti rel/lubang ke dalam mesin)
    Rectangle panelRecJoyStick = {joyBaseX - 15, joyBaseY - 4, 30, 8};
    DrawRectangleRounded(panelRecJoyStick, 1.0f, 10, (Color){40, 40, 40, 255}); // Warna gelap

    // TIANG stick
    DDA_ThickLine(joyBaseX, joyBaseY, knobX, knobY, 14, (Color){100, 70, 70, 255}); 

 
    // Bayangan KNOB
    DrawCircle(knobX, knobY + 3, 22, MAROON); 
    
    // warna utama KNOB
    DrawCircle(knobX, knobY, 22, (Color){237, 50, 50, 255}); 
    
    // Pantulan cahaya di offset ke kiri atas dari titik tengah knob
    DrawCircle(knobX - 7, knobY - 7, 6, (Color){255, 255, 255, 150});
}