#include "src/screens/sound.h"

static Music bgmMenu;
static Music bgmClaw;
static Sound sfxCU;
static Sound sfxDown;
static Sound sfxRail;
static Sound sfxGetPrize;
static Sound sfxButton;
static Sound sfxStoneHit;

void InitGameAudio(void) {  
    InitAudioDevice();

    bgmMenu = LoadMusicStream("src/asset/Wii Party Soundtrack - Main Menu Music [fzepGtfHL9A].mp3");
    bgmClaw = LoadMusicStream("src/asset/Namco - Sweet Land Premia Music [BGzNhEZGK38].mp3");
    sfxCU = LoadSound("src/asset/CLAWUP(rev).mp3");
    sfxDown = LoadSound("src/asset/CLAWDOWN.mp3");
    sfxRail = LoadSound("src/asset/rail2.mp3");
    sfxGetPrize = LoadSound("src/asset/DAPETHADIAH.mp3");
    sfxButton = LoadSound("src/asset/buttonSfx.mp3");
    sfxStoneHit = LoadSound("src/asset/soundBatu.mp3");

    SetMusicVolume(bgmMenu, 0.5f); 
    SetMusicVolume(bgmClaw, 0.7f);
    SetSoundVolume(sfxCU, 0.5f);
    SetSoundVolume(sfxDown, 0.5f);
    SetSoundVolume(sfxRail, 0.3f);
    SetSoundVolume(sfxGetPrize, 0.5f);
    SetSoundVolume(sfxButton, 0.5f);
    SetSoundVolume(sfxStoneHit, 1.0f);
}

void PlayMenuBGM(void) {
    if (IsMusicStreamPlaying(bgmClaw)) {
        StopMusicStream(bgmClaw); 
    }
    if (!IsMusicStreamPlaying(bgmMenu)) {
        PlayMusicStream(bgmMenu);
    }
}

void PlayClawBGM(void) {
    if (IsMusicStreamPlaying(bgmMenu)) {
        StopMusicStream(bgmMenu); 
    }
    if (!IsMusicStreamPlaying(bgmClaw)) {
        PlayMusicStream(bgmClaw);
    }
}

void UpdateGameAudio(Screen current) {
    if (current == MENU) {
        UpdateMusicStream(bgmMenu);
    } 
    else if (current == CLAW) {
        UpdateMusicStream(bgmClaw);
    }
}

void PlaySfxDown(void) { 
    PlaySound(sfxDown); 
}
    
void PlaySfxUp(void) { 
    PlaySound(sfxCU); 
}

void PlaySfxPrize(void) { 
    PlaySound(sfxGetPrize); 
}

void PlaySfxButton(void) { 
    PlaySound(sfxButton); 
}

void PlaySfxSoundBatu(void) { 
    PlaySound(sfxStoneHit); 
}

void UpdateSfxRail(int isMoving) {
    if (isMoving) {
        if (!IsSoundPlaying(sfxRail)) PlaySound(sfxRail);
    } else {
        if (IsSoundPlaying(sfxRail)) StopSound(sfxRail);
    }
}

void UnloadGameAudio(void) {
    UnloadMusicStream(bgmMenu);
    UnloadMusicStream(bgmClaw);
    UnloadSound(sfxCU);
    UnloadSound(sfxDown);
    UnloadSound(sfxRail);
    UnloadSound(sfxGetPrize);
    CloseAudioDevice();
}