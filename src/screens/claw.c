#include "src/screens/claw.h"
#include "src/ui/indikatorStatus.h"

// Variabel Statis 
static int initialized = 0;
static ClawState state = STATE_IDLE;
static float clawX = 0.0f;
static float clawY = 0.0f;
static float clawSpeed = 180.0f;
static float startY = 80.0f;
static float bottomY = 430.0f;
static float dropWallX = 180.0f;
static float dropWallTopY = 357.0f;
static float clawRadius = 40.0f;

static Prize prizes[MAX_PRIZES];
static int heldPrize = -1; 
static float armOffset = 25.0f; 

// Posisi lubang hadiah (Drop Area)
static float dropX = 115.0f;

void InitClaw(void) {
    // 1. INISIALISASI AWAL
    if (!initialized) {
        clawX = dropX; 
        clawY = startY;
        state = STATE_IDLE;
        heldPrize = -1;
        armOffset = 25.0f;
        
        // BARIS BAWAH (Y = 430)
        prizes[0] = (Prize){ SCREEN_W/2 - 40,  430, 24, RED, 0, 0, 0 };
        prizes[1] = (Prize){ SCREEN_W/2 + 10,  430, 24, GREEN, 0, 0, 0 };
        prizes[2] = (Prize){ SCREEN_W/2 + 60, 430, 24, BROWN, 0, 0, 2 }; 
        prizes[3] = (Prize){ SCREEN_W/2 + 110, 430, 22, DARKGRAY, 0, 0, 1 }; 
        prizes[4] = (Prize){ SCREEN_W/2 + 160, 430, 24, VIOLET, 0, 0, 0 };
        prizes[5] = (Prize){ SCREEN_W/2 + 210, 430, 24, RED, 0, 0, 2 };
        prizes[11] = (Prize){ SCREEN_W/2 - 90, 430, 24, SKYBLUE, 0, 0, 0 };
        prizes[12] = (Prize){ SCREEN_W/2 - 140, 430, 22, DARKGRAY, 0, 0, 1 };
        prizes[13] = (Prize){ SCREEN_W/2 - 190, 430, 24, GREEN, 0, 0, 2 };
        prizes[14] = (Prize){ SCREEN_W/2 + 260, 430, 22, DARKGRAY, 0, 0, 1 };
        prizes[15] = (Prize){ SCREEN_W/2 + 310, 430, 24, VIOLET, 0, 0, 2 };

        // BARIS TENGAH ( Y = 385)
        prizes[6] = (Prize){ SCREEN_W/2 + 25,   385, 24, GREEN, 0, 0, 0 };
        prizes[7] = (Prize){ SCREEN_W/2 + 75,  385, 22, GRAY, 0, 0, 1 };     
        prizes[8] = (Prize){ SCREEN_W/2 + 125, 385, 24, ORANGE, 0, 0, 2 };
        prizes[9] = (Prize){ SCREEN_W/2 + 175, 385, 24, VIOLET, 0, 0, 0 };
        prizes[10]= (Prize){ SCREEN_W/2 + 225, 385, 24, SKYBLUE, 0, 0, 0 }; 
        prizes[16]= (Prize){ SCREEN_W/2 + 275, 385, 22, DARKGRAY, 0, 0, 1 }; 
        prizes[18]= (Prize){ SCREEN_W/2 - 20, 385, 24, VIOLET, 0, 0, 0 }; 
        prizes[19]= (Prize){ SCREEN_W/2 - 70, 385, 24, DARKGRAY, 0, 0, 1 }; 
        prizes[20]= (Prize){ SCREEN_W/2 - 125, 385, 24, SKYBLUE, 0, 0, 2 }; 
        prizes[21]= (Prize){ SCREEN_W/2 - 175, 385, 24, RED, 0, 0, 0 }; 
        
        //BARIS ATAS (y = 340)
        prizes[22]= (Prize){ SCREEN_W/2 + 205, 340, 24, DARKGRAY, 0, 0, 1 }; 
        prizes[23]= (Prize){ SCREEN_W/2 + 150, 340, 24, GREEN, 0, 0, 0 }; 
        prizes[24]= (Prize){ SCREEN_W/2 + 255, 345, 24, SKYBLUE, 0, 0, 0 }; 
        prizes[17] = (Prize){ SCREEN_W/2 + 313, 350, 24, RED, 0, 0, 0 };
        initialized = 1;
    }
}

int DrawProgramClaw(void) {

    InitClaw(); 
    float dt = GetFrameTime();

    Rectangle btnRec = {SCREEN_W / 2 + 85, 505, 100, 40};
    Vector2 mouse = GetMousePosition();
    int btnHover = CheckCollisionPointRec(mouse, btnRec);
    int btnPressed = btnHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    
    switch (state) {
    case STATE_IDLE:
            armOffset = 25.0f; 
            int isMoving = 0; 

            clawY = startY + sinf(GetTime() * 3.0f) * 4.0f;
            
            if (IsKeyDown(KEY_RIGHT) && clawX < SCREEN_W - 110) {
                clawX += clawSpeed * dt;
                isMoving = 1;
            }
            if (IsKeyDown(KEY_LEFT) && clawX > dropX) {
                clawX -= clawSpeed * dt;
                isMoving = 1;
            }
            
            UpdateSfxRail(isMoving); 

            if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER) || btnPressed) {
                UpdateSfxRail(0); 
                PlaySfxDown();    
                state = STATE_DROPPING;
            }
            break;

        case STATE_DROPPING:
            clawY += clawSpeed * dt;
            
            int stopDropping = 0; // Penanda capit harus berhenti

            // 1. Cek tabrakan dengan lantai (kondisi paling dasar)
            if (clawY >= bottomY - 50.0f) {
                clawY = bottomY - 50.0f;
                stopDropping = 1;
            } 
            else if (clawX <= dropWallX + clawRadius && clawY >= dropWallTopY - 50.0f) {
                clawY = dropWallTopY - 50.0f;
                stopDropping = 1;
            }

            else {
                // 2. Cek tabrakan dengan benda/hadiah saat turun
                float clawTipX = clawX;
                float clawTipY = clawY + 40.0f; // Asumsi ujung bawah capit ada di +40 piksel
                
                for (int i = 0; i < MAX_PRIZES; i++) {
                    // Hanya cek benda yang masih ada di dalam mesin
                    if (!prizes[i].isWon && !prizes[i].isCaught) {
                        
                        // Cek apakah capit sedang berada di atas objek ini (kesejajaran sumbu X)
                        // Menggunakan jarak horizontal (dx) dengan sedikit toleransi 15 piksel
                        float dx = fabsf(clawTipX - prizes[i].x);
                        if (dx <= prizes[i].radius + 15.0f) { 
                            
                            // Hitung titik teratas dari bola/batu (Sumbu Y pusat dikurangi radiusnya)
                            float topOfPrize = prizes[i].y - prizes[i].radius;
                            
                            // Jika ujung capit menyentuh atau melewati bagian atas bola
                            if (clawTipY >= topOfPrize) {
                                
                                // Set posisi Y capit agar bertengger tepat di atas benda tersebut
                                clawY = topOfPrize - 40.0f; 
                                stopDropping = 1;
                                break; // Hentikan loop karena capit sudah menabrak sesuatu
                            }
                        }
                    }
                }
            }

            // Jika capit menabrak lantai ATAU benda, langsung mulai proses Grab
            if (stopDropping) {
                state = STATE_GRABBING;
            }
            break;

        case STATE_GRABBING:
            armOffset -= 30.0f * dt; // Capit menutup
            if (armOffset <= 12.0f) {
                armOffset = 12.0f;
                
                // Deteksi Tabrakan
                float clawTipX = clawX;
                float clawTipY = clawY + 40.0f;

                int bestPrize = -1;
                float bestY = 9999.0f;       
                float minDistance = 9999.0f; 
                
                // Mengecek ke SELURUH hadiah yang ada di layar
                for (int i = 0; i < MAX_PRIZES; i++) {
                    if (!prizes[i].isWon && !prizes[i].isCaught) {
                        
                        // Hitung jarak ujung capit ke bola
                        float dx = clawTipX - prizes[i].x;
                        float dy = clawTipY - prizes[i].y;
                        float distance = sqrtf(dx*dx + dy*dy);
                        
                        // Jika bola masuk dalam jangkauan capit
                        if (distance <= prizes[i].radius + 15.0f) { 
                            
                            // LOGIKA PRIORITAS:
                            // 1. Utamakan bola yang berada di lapisan paling atas (Y paling kecil di layar)
                            if (prizes[i].y < bestY) {
                                bestY = prizes[i].y;
                                minDistance = distance;
                                bestPrize = i;
                            } 
                            // 2. Jika ada dua bola di lapisan yang SAMA-SAMA atas, pilih yang paling dekat posisinya ke tengah capit
                            else if (prizes[i].y == bestY && distance < minDistance) {
                                minDistance = distance;
                                bestPrize = i;
                            }
                        }
                    }
                }
                
                // Jika ditemukan kandidat bola terbaik, capit bola tersebut!
                if (bestPrize != -1) {
                    heldPrize = bestPrize;
                    prizes[heldPrize].isCaught = 1;
                }

                PlaySfxUp();
                state = STATE_RETURNING; // Naik lagi
            }
            break;

        case STATE_RETURNING:
            clawY -= clawSpeed * dt; // Naik
            if (heldPrize != -1) {
                prizes[heldPrize].x = clawX;
                prizes[heldPrize].y = clawY + 50.0f;
            }

            if (clawY <= startY) {
                clawY = startY;
                state = STATE_MOVING_HOME; // Menuju lubang hadiah
            }
            break;

        case STATE_MOVING_HOME:
            // Gerak otomatis ke kiri menuju dropX
            if (clawX > dropX) {
                clawX -= clawSpeed * dt;
                if (heldPrize != -1) prizes[heldPrize].x = clawX;
                UpdateSfxRail(1);
            } else {
                clawX = dropX;
                UpdateSfxRail(0);
                state = STATE_RELEASING;
            }
            break;

        case STATE_RELEASING:
            armOffset += 30.0f * dt; // Capit membuka

            if (armOffset >= 25.0f) {
                armOffset = 25.0f; 
            }
            
            if (heldPrize != -1) {
                prizes[heldPrize].y += (clawSpeed * 1.5f) * dt; // Bola jatuh ke bawah
                if (prizes[heldPrize].y > bottomY + 100.0f) { // Menghilang masuk lubang
                    prizes[heldPrize].isWon = 1;
                    if (prizes[heldPrize].type == 1) {
                        StartStoneShake();
                        PlaySfxSoundBatu();
                    }
                    else {
                        PlaySfxPrize();
                    }
                    heldPrize = -1;
                }
            }
            
            
            if (armOffset >= 25.0f && heldPrize == -1) {
                state = STATE_IDLE; 
            }
            break;
    }

    //EFEK GETER
    Camera2D camera = StoneVfx(dt);
    BeginMode2D(camera); //Mulai geter

    // RENDER VISUAL
    DrawBodyMesin(clawX, clawY, dropX);

    // Gambar Hadiah
    for (int i = 0; i < MAX_PRIZES; i++) {
        DrawPrize(prizes[i]);
    }

    // Tuas / Joystick 
    DrawJoyStick(clawX, dropX);

    // Gambar Capit 
    DrawClaw(clawX, clawY, armOffset, 1); 

    // Tombol CAPIT 
    int btnDown = ((btnHover && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER));
    drawTombolCapit(btnRec, btnHover, btnDown);

    // tombol keluar
    Rectangle btnOutRec = {SCREEN_W / 2 + 205, 505, 90, 40};
    Vector2 mouseOut = GetMousePosition();
    int btnHoverOut = CheckCollisionPointRec(mouseOut, btnOutRec);
    int btnPressedOut = ((btnHoverOut && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) || IsKeyPressed(KEY_O));
    int btnDownOut = ((btnHoverOut && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) || IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_O));
    drawTombolOut(btnOutRec, btnHoverOut, btnDownOut);

    if (btnPressedOut) {
        initialized = 0; 
        PlayMenuBGM(); 
        return 1;        
    }

    //Mesin
    DrawRectangleRounded((Rectangle){10, 25, 65, 40}, 0.5f, 10, mainRed);
    DrawRectangleRounded((Rectangle){24, 37, 40, 15}, 0.5f, 10, darkRed); 
    
    //KACA DROP
    DrawRectangle(60, 385, 113, 72, (Color){0, 0, 0, 150});
   
    // Indikator Status
    DrawIndikatorStatus(state);
    
    // indikator skor
    DrawIndikatorSkor(prizes);
    
    EndMode2D(); //Akhir geter

    return 0;
}
