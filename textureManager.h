#ifndef TEXTURE_MANAGER
#define TEXTURE_MANAGER


#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CMA.h"
#include "globalVars.h"


#define MAX_TEXTURES 1000


typedef struct {
    int ID;
    Texture2D Texture;
    char * Path;
    bool Freed;
    int RefCount;
} SGameTexture;


SGameTexture* GameTextures[MAX_TEXTURES] = {};


void InitTextures() {
    for (int i = 0; i < MAX_TEXTURES; i++) {
        GameTextures[i] = NULL;
    }
}


void AddGameTexture(SGameTexture* Texture) {
    for (int i = 0; i < MAX_TEXTURES; i++) {
        if (GameTextures[i] == NULL) {
            GameTextures[i] = Texture;
            return;
        }
    }


    printf("ERROR: Texture array is full :(\n");
}


SGameTexture* LoadGameTexture(const char* FilePath) {
    printf("Loading texture: %s\n", FilePath);


    for (int i = 0; i < MAX_TEXTURES; i++) {
        if (GameTextures[i] != NULL && GameTextures[i]->Path != NULL &&
            strcmp(FilePath, GameTextures[i]->Path) == 0) {
            GameTextures[i]->RefCount++;
            return GameTextures[i];
            }
    }


    SGameTexture* NewTexture = AllocateMem(sizeof(SGameTexture));
    NewTexture->ID = GetRandomValue(0, 1000000);
    NewTexture->Freed = false;
    NewTexture->RefCount = 1;
    NewTexture->Path = AllocateMem(strlen(FilePath) + 1);
    strcpy(NewTexture->Path, FilePath);


    NewTexture->Texture = LoadTexture(FilePath);
    if (NewTexture->Texture.id == 0) {
        printf("ERROR: Failed to load texture: %s\n", FilePath);
        FreeMem(NewTexture->Path);
        FreeMem(NewTexture);
        return NULL;
    }


    AddGameTexture(NewTexture);
    return NewTexture;
}


void UnloadGameTexture(SGameTexture* Texture) {
    if (Texture == NULL) {return;}


    Texture->RefCount --;
    

    if (Texture->RefCount > 0) {
        return;
    }


    if (Texture->Freed) return;
    Texture->Freed = true;


    printf("Unloading texture: %s\n", Texture->Path);


    for (int i = 0; i < MAX_TEXTURES; i++) {
        if (GameTextures[i] == Texture) {
            UnloadTexture(Texture->Texture);
            FreeMem(Texture->Path);
            FreeMem(Texture);
            GameTextures[i] = NULL;
            return;
        }
    }


    UnloadTexture(Texture->Texture);
    FreeMem(Texture->Path);
    FreeMem(Texture);
}


void UnloadTextures() {
    for (int i = 0; i < MAX_TEXTURES; i++) {
        if (GameTextures[i] != NULL) {
            UnloadGameTexture(GameTextures[i]);
        }
    }
}


void DrawGameTexture(SGameTexture* Tex, Rectangle Source, Vector2 Pos, float Rot, Vector2 Scale, Vector2 Pivot, Color Blend) {
    Pivot.x *= Scale.x > 0 ? Scale.x : -Scale.x;
    Pivot.y *= Scale.y > 0 ? Scale.y : -Scale.y;
    Source.width *= Sign(Scale.x);
    Source.height *= Sign(Scale.y);


    DrawTexturePro(Tex->Texture, Source, (Rectangle){Pos.x, Pos.y, Tex->Texture.width * Scale.x, Tex->Texture.height * Scale.y}, Pivot, Rot, Blend);
}


#endif
