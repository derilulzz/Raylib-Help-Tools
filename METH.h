#ifndef METH
#define METH


#include "raymath.h"


float GetDelta() {
    return Clamp(GetFrameTime(), 0, 0.1f);
}


#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
float SLerp(float A, float B, float Force) {
    return A + (B - A) * (1 - exp(-Force * GetDelta()));
}
float Sign(float X) {
    return X == 0 ? 0 : X < 0 ? -1 : 1;
}
Vector2 SLerpVec2(Vector2 A, Vector2 B, float Force) {
    return (Vector2){SLerp(A.x, B.x, Force), SLerp(A.y, B.y, Force)};
}
Color SLerpColr(Color A, Color B, float Force) {
    return (Color){(unsigned char)(SLerp(A.r, B.r, Force)), (unsigned char)SLerp(A.g, B.g, Force), (unsigned char)SLerp(A.b, B.b, Force), (unsigned char)SLerp(A.a, B.a, Force)};
}
float AngleDifference(float A, float B) {
    float Diff = B - A;
    while (Diff > PI) Diff -= 2 * PI;
    while (Diff < -PI) Diff += 2 * PI;
    return Diff;
}
float SLerpAngle(float Start, float End, float Speed) {
    float Diff = AngleDifference(Start, End);
    return Start + Diff * fmin(Speed * GetDelta(), 1.0f);
}


#endif
