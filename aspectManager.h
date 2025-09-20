#ifndef ASPECT_MANAGER
#define ASPECT_MANAGER


#include "raylib.h"
#include "METH.h"


RenderTexture2D DrawTarget;
int WantedWidth;
int WantedHeight;
bool IntegerScale = false;


void InitAscpectManager(int GameWidth, int GameHeight) {
    WantedWidth = GameWidth;
    WantedHeight = GameHeight;
    DrawTarget = LoadRenderTexture(WantedWidth, WantedHeight);
}


float GetGameScale() {
    return IntegerScale ? floor(MIN((float)GetScreenWidth() / WantedWidth, (float)GetScreenHeight() / WantedHeight)) : MIN((float)GetScreenWidth() / WantedWidth, (float)GetScreenHeight() / WantedHeight);
}


Vector2 ScreenToGame(Vector2 What) {
    Vector2 NewPos = { 0 };
    float Scale = GetGameScale();
    NewPos.x = (What.x - (GetScreenWidth() - (WantedWidth * Scale)) * 0.5f) / Scale;
    NewPos.y = (What.y - (GetScreenHeight() - (WantedHeight * Scale)) * 0.5f) / Scale;
    NewPos = Vector2Clamp(NewPos, (Vector2){ 0, 0 }, (Vector2){ (float)WantedWidth, (float)WantedHeight });
    return NewPos;
}


void BeginGameDraw() {
    BeginTextureMode(DrawTarget);
}


void EndGameDraw() {
    EndTextureMode();
}


void DrawGame() {
    BeginDrawing();
        ClearBackground(BLACK);
        float Scale = GetGameScale();


        DrawTexturePro(DrawTarget.texture, (Rectangle){ 0.0f, 0.0f, (float)DrawTarget.texture.width, (float)-DrawTarget.texture.height }, (Rectangle){ (GetScreenWidth() - ((float)WantedWidth * Scale)) * 0.5f, (GetScreenHeight() - ((float)WantedHeight * Scale)) * 0.5f, (float)WantedWidth * Scale, (float)WantedHeight * Scale }, (Vector2){ 0, 0 }, 0.0f, WHITE);
    EndDrawing();
}


void UnloadAspectManager() {
    UnloadRenderTexture(DrawTarget);
}


#endif
