#ifndef ANIMATION
#define ANIMATION


#include <raylib.h>
#include <raymath.h>
#include "globalVars.h"
#include "textureManager.h"


#define MAX_FRAMES 5000
#define MAX_ANIMS 10000


typedef struct {
    const char * Name;
    int StartFrame;
    int EndFrame;
} SAnimationDelimiter;


typedef enum {
    ANIM_END_LOOP,
    ANIM_END_END,
} ANIM_END_TYPE;


typedef struct {
    int ID;
    float CurrentFrame;
    float Speed;
    Rectangle* Frames[MAX_FRAMES];
    SGameTexture* SpriteSheet;
    int FrameWidth;
    int FrameHeight;
    int FrameAmount;
    bool Freed;
    ANIM_END_TYPE EndType;
    bool Finished;
    bool AutoPlay;
    SAnimationDelimiter* Animations[MAX_ANIMS];
    SAnimationDelimiter* CurrentAnimDeli;
    bool Persistent;
} SAnimation;


SAnimation* Animations[MAX_ANIMS] = {};


void InitAnims() {
    for (int i = 0; i < MAX_ANIMS; i++) {
        Animations[i] = NULL;
    }
}


void AddAnimation(SAnimation* Anim) {
    for (int i = 0; i < MAX_ANIMS; i++) {
        if (Animations[i] == NULL) {
            Animations[i] = Anim;
            return;
        }
    }
}


void DefineAnimationDelimiter(SAnimation* ForWho, const char * Name, int StartFrame, int EndFrame) {
    for (int a = 0; a < MAX_ANIMS; a++) {
        if (ForWho->Animations[a] == NULL) {
            ForWho->Animations[a] = AllocateMem(sizeof(SAnimationDelimiter));
            ForWho->Animations[a]->Name = Name;
            ForWho->Animations[a]->StartFrame = StartFrame;
            ForWho->Animations[a]->EndFrame = EndFrame;


            if (ForWho->CurrentAnimDeli == NULL) {
                ForWho->CurrentAnimDeli = ForWho->Animations[a];
            }


            return;
        }
    }
}


void PlayAnimation(SAnimation* ForWho, const char * Name) {
    for (int a = 0; a < MAX_ANIMS; a++) {
        if (ForWho->Animations[a] != NULL && strcmp(Name, ForWho->Animations[a]->Name) == 0) {
            if (ForWho->CurrentAnimDeli != ForWho->Animations[a]) {
                ForWho->CurrentFrame = ForWho->Animations[a]->StartFrame;
            }


            ForWho->CurrentAnimDeli = ForWho->Animations[a];


            return;
        }
    }
}


// Create a new animation from a sprite sheet
SAnimation* CreateAnimation(SGameTexture* SpriteSheet, float Speed, int FrameWidth, int FrameHeight) {
    SAnimation* Anim = AllocateMem(sizeof(SAnimation));
    Anim->ID = GetRandomValue(0, 1000000);
    Anim->CurrentFrame = 0;
    Anim->FrameWidth = FrameWidth;
    Anim->FrameHeight = FrameHeight;
    Anim->Speed = Speed;
    Anim->SpriteSheet = SpriteSheet;
    Anim->Freed = false;
    Anim->EndType = ANIM_END_LOOP;
    Anim->Finished = false;
    Anim->AutoPlay = true;
    Anim->Persistent = false;
    Anim->CurrentAnimDeli = NULL;
    for (int a = 0; a < MAX_ANIMS; a++) {
        Anim->Animations[a] = NULL;
    }


    for (int i = 0; i < MAX_FRAMES; i++) {
        Anim->Frames[i] = NULL;
    }


    int CurrentFrame = 0;
    for (int y = 0; y < SpriteSheet->Texture.height; y+=FrameHeight) {
        for (int x = 0; x < SpriteSheet->Texture.width; x+=FrameWidth) {
            if (CurrentFrame >= MAX_FRAMES) {
                break;
            }

            
            Anim->Frames[CurrentFrame] = AllocateMem(sizeof(Rectangle));
            Anim->Frames[CurrentFrame]->x = x;
            Anim->Frames[CurrentFrame]->y = y;
            Anim->Frames[CurrentFrame]->width = FrameWidth;
            Anim->Frames[CurrentFrame]->height = FrameHeight;
            CurrentFrame ++;
        }
    }


    Anim->FrameAmount = CurrentFrame;


    AddAnimation(Anim);
    return Anim;
}


// Update a single animation
void UpdateAnimation(SAnimation* Anim) {
    bool Ended = floor(Anim->CurrentFrame) >= Anim->FrameAmount;


    if (Anim->CurrentAnimDeli != NULL) {
        Ended = floor(Anim->CurrentFrame) > Anim->CurrentAnimDeli->EndFrame;
    }


    if (Ended) {
        switch (Anim->EndType) {
            case ANIM_END_LOOP :
                if (Anim->CurrentAnimDeli != NULL) {
                    Anim->CurrentFrame = Anim->CurrentAnimDeli->StartFrame;
                }else{
                    Anim->CurrentFrame = 0;
                }
            break;


            case ANIM_END_END :
                if (Anim->CurrentAnimDeli != NULL) {
                    Anim->CurrentFrame = Anim->CurrentAnimDeli->EndFrame;
                }


                Anim->Finished = true;
            break;
        }
    }else{
        Anim->Finished = false;
    }


    Anim->CurrentFrame += Anim->Speed * GetDelta();
}


void UpdateAnimations() {
    for (int i = 0; i < MAX_ANIMS; i++) {
        if (Animations[i] != NULL && Animations[i]->AutoPlay) {
            UpdateAnimation(Animations[i]);
        }
    }
}


void DrawAnimation(SAnimation* Anim, Vector2 Pos, float Rot, Vector2 Scale, Vector2 Pivot, Color Blend) {
    if (Anim == NULL || Anim->Freed || Anim->SpriteSheet == NULL || Anim->SpriteSheet->Freed || Anim->CurrentFrame <= -1) {return;}

    
    int CurrF = floor(Anim->CurrentFrame);


    if (Anim->CurrentAnimDeli == NULL) {
        CurrF = Clamp(CurrF, 0, Anim->FrameAmount - 1);
    }else{
        CurrF = Clamp(CurrF, 0, Anim->CurrentAnimDeli->EndFrame);
    }


    Rectangle UsedFrame = *Anim->Frames[CurrF];
    UsedFrame = (Rectangle){UsedFrame.x, UsedFrame.y, UsedFrame.width, UsedFrame.height};


    Pivot.x *= Scale.x > 0 ? Scale.x : -Scale.x;
    Pivot.y *= Scale.y > 0 ? Scale.y : -Scale.y;
    UsedFrame.width *= Scale.x <= 0 ? Sign(Scale.x) : 1;
    UsedFrame.height *= Scale.y <= 0 ? Sign(Scale.y) : 1;


    DrawTexturePro(Anim->SpriteSheet->Texture, UsedFrame, (Rectangle){Pos.x, Pos.y, Anim->FrameWidth * Scale.x, Anim->FrameHeight * Scale.y}, Pivot, Rot, Blend);
}


// Unload a specific animation and optionally its texture
void UnloadAnimation(SAnimation* Anim) {
    if (!Anim || Anim->Freed) {return;}
    

    Anim->Freed = true;
    

    for (int i = 0; i < MAX_ANIMS; i++) {
        if (Animations[i] != NULL && Animations[i] == Anim) {
            Animations[i] = NULL;
            break;
        }
    }
    for (int i = 0; i < MAX_ANIMS; i++) {
        if (Anim->Animations[i] != NULL) {
            FreeMem(Anim->Animations[i]);
            Anim->Animations[i] = NULL;
        }
    }


    for (int j = 0; j < Anim->FrameAmount; j++) {
        if (Anim->Frames[j] != NULL) {
            FreeMem(Anim->Frames[j]);
            Anim->Frames[j] = NULL;
        }
    }


    UnloadGameTexture(Anim->SpriteSheet);


    FreeMem(Anim);
}


SAnimation* CopyAnimation(SAnimation* What) {
    if (What == NULL) {return NULL;}


    SAnimation* Anim = CreateAnimation(LoadGameTexture(What->SpriteSheet->Path), What->Speed, What->FrameWidth, What->FrameHeight);


    for (int a = 0; a < MAX_ANIMS; a++) {
        if (What->Animations[a] != NULL) {
            DefineAnimationDelimiter(Anim, What->Animations[a]->Name, What->Animations[a]->StartFrame, What->Animations[a]->EndFrame);
        }
    }


    return Anim;
}


// Unload all animations and optionally their textures
void UnloadAnimations() {
    for (int i = 0; i < MAX_ANIMS; i++) {
        if (Animations[i] != NULL && !Animations[i]->Persistent) {
            UnloadAnimation(Animations[i]);
        }
    }
}


#endif
