#pragma once

#ifndef utils_h
#define utils_h

#include "SDK.h"

#define INRANGE(x,a,b)  (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

typedef void (*RankRevealAllFn) (float*);

class Utils
{
public:
    static bool ScreenTransform(const Vector& point, Vector& screen)
    {
        const VMatrix& w2sMatrix = Interfaces::Engine()->WorldToScreenMatrix();
        screen.x = w2sMatrix.m[0][0] * point.x + w2sMatrix.m[0][1] * point.y + w2sMatrix.m[0][2] * point.z + w2sMatrix.m[0][3];
        screen.y = w2sMatrix.m[1][0] * point.x + w2sMatrix.m[1][1] * point.y + w2sMatrix.m[1][2] * point.z + w2sMatrix.m[1][3];
        screen.z = 0.0f;

        float w = w2sMatrix.m[3][0] * point.x + w2sMatrix.m[3][1] * point.y + w2sMatrix.m[3][2] * point.z + w2sMatrix.m[3][3];

        if(w < 0.001f) {
            screen.x *= 100000;
            screen.y *= 100000;
            return true;
        }

        float invw = 1.0f / w;
        screen.x *= invw;
        screen.y *= invw;

        return false;
    }

    static bool WorldToScreen(const Vector &origin, Vector &screen)
    {
        if(!ScreenTransform(origin, screen)) {
            int iScreenWidth, iScreenHeight;
            Interfaces::Engine()->GetScreenSize(iScreenWidth, iScreenHeight);

            screen.x = (iScreenWidth / 2.0f) + (screen.x * iScreenWidth) / 2;
            screen.y = (iScreenHeight / 2.0f) - (screen.y * iScreenHeight) / 2;

            return true;
        }
        return false; 
    }

    static wchar_t *WCharConvert(const char *c)
    {
        const size_t cSize = strlen(c)+1;
        wchar_t* wc = new wchar_t[cSize];
        mbstowcs (wc, c, cSize);

        return wc;
    }

    static void RankRevealAll(float* input);
private:
    static RankRevealAllFn m_fncRankRevealAll;
};

#endif // !utils_h
