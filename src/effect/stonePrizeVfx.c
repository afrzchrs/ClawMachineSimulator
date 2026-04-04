#include "src/effect/stonePrizeVfx.h"

static float shakeTimer = 0.0f;

void StartStoneShake(void) {
    shakeTimer = 0.5f; 
}

Camera2D StoneVfx(float dt) {
    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ 0, 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Jika timer getaran masih ada, berikan nilai offset acak pada kamera
    if (shakeTimer > 0.0f) {
        camera.offset.x = (float)GetRandomValue(-5, 5); // Getaran horizontal
        camera.offset.y = (float)GetRandomValue(-5, 5); // Getaran vertikal
        shakeTimer -= dt; // Kurangi timer setiap frame
    }

    return camera;
}