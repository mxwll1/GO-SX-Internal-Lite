#include "draw.h"
#include "SDK/Utils.h"

bool crosshair = false;

enum FontSize {
    SMALL = 0,
    BIG
};

CDrawings* CDrawings::instance = nullptr;

CDrawings::CDrawings() {
    if(!hFont) {
        hFont = GetFont(MENUGET_STRING("Main", "menu_font"), 12, FontFlags::FONTFLAG_OUTLINE);
    }

    if(!bFont) {
        bFont = GetFont(MENUGET_STRING("Main", "menu_font"), 16, FontFlags::FONTFLAG_ANTIALIAS);
    }
}

CDrawings::~CDrawings()
{
    hFont = 0;
    bFont = 0;
}

HFONT CDrawings::GetFont(const char* fontName, int size, FontFlags flags) {
    HFONT tmpFont = Interfaces::Surface()->CreateFont();
    Interfaces::Surface()->SetFontGlyphSet(tmpFont, fontName, size, 400, 0, 0, flags);

    return tmpFont;
}

void CDrawings::CheckFonts() {
    if(!hFont) {
        hFont = GetFont(MENUGET_STRING("Main", "menu_font"), 12, FontFlags::FONTFLAG_OUTLINE);
    }

    if(!bFont) {
        hFont = GetFont(MENUGET_STRING("Main", "menu_font"), 16, FontFlags::FONTFLAG_ANTIALIAS);
    }
}

void CDrawings::DrawString(int font, int x, int y, Color clrColor, /*bool bCenter,*/ wchar_t* szText)
{
    if (!szText) {
        return;
    }

    HFONT drawFont;
    if(font == FontSize::SMALL) {
        drawFont = hFont;
    } else {
        drawFont = bFont;
    }

    Interfaces::Surface()->DrawSetTextPos(x, y);
    Interfaces::Surface()->DrawSetTextFont(drawFont);
    Interfaces::Surface()->DrawSetTextColor(clrColor);
    Interfaces::Surface()->DrawPrintText(szText, (int)wcslen(szText));
}

void CDrawings::DrawString(int font, int x, int y, Color textColor, const char* textString, bool bCenter) {
    if (!textString) {
        return;
    }

    HFONT drawFont;
    if(font == FontSize::SMALL) {
        drawFont = hFont;
    } else {
        drawFont = bFont;
    }

    wchar_t* szString = Utils::WCharConvert(textString);

    if (bCenter)
    {
        int Wide = 0, Tall = 0;

        Interfaces::Surface()->GetTextSize(drawFont, szString, Wide, Tall);

        x -= Wide / 2;
    }

    Interfaces::Surface()->DrawSetTextPos(x, y);
    Interfaces::Surface()->DrawSetTextFont(drawFont);
    Interfaces::Surface()->DrawSetTextColor(textColor);
    Interfaces::Surface()->DrawPrintText(szString, (int)wcslen(szString));
}

void CDrawings::DrawShadowString(int font, int x, int y, Color clrColor, bool bCenter, const char* szText, ...)
{
    va_list va_alist;
    char szBuffer[256] = { '\0' };

    va_start(va_alist, szText);
    vsprintf(szBuffer, szText, va_alist);
    va_end(va_alist);

    wchar_t* szString = Utils::WCharConvert(szBuffer);

    DrawString(font, x + 1, y + 1, Color(0, 0, 0), szString);
    DrawString(font, x, y, clrColor, szString);
}

void CDrawings::DrawShadowString(HFONT drawFont, int x, int y, Color clrColor, bool bCenter, const char* szText, ...)
{
    va_list va_alist;
    char szBuffer[256] = { '\0' };

    va_start(va_alist, szText);
    vsprintf(szBuffer, szText, va_alist);
    va_end(va_alist);

    wchar_t* szString = Utils::WCharConvert(szBuffer);

    DrawString(drawFont, x + 1, y + 1, Color(0, 0, 0), szString);
    DrawString(drawFont, x, y, clrColor, szString);
}

void CDrawings::DrawString(int font, int x, int y, Color clrColor, bool bCenter, const char* szText, ...)
{
    if (!szText) {
        return;
    }

    HFONT drawFont;
    if(font == FontSize::SMALL) {
        drawFont = hFont;
    } else {
        drawFont = bFont;
    }

    va_list va_alist;
    char szBuffer[256] = { '\0' };

    va_start(va_alist, szText);
    vsprintf(szBuffer, szText, va_alist);
    va_end(va_alist);

    wchar_t* szString = Utils::WCharConvert(szBuffer);

    if (bCenter)
    {
        int Wide = 0, Tall = 0;

        Interfaces::Surface()->GetTextSize(drawFont, szString, Wide, Tall);

        x -= Wide / 2;
    }

    Interfaces::Surface()->DrawSetTextPos(x, y);
    Interfaces::Surface()->DrawSetTextFont(drawFont);
    Interfaces::Surface()->DrawSetTextColor(clrColor);
    Interfaces::Surface()->DrawPrintText(szString, (int)strlen(szBuffer));
}

void CDrawings::DrawString(HFONT drawFont, int x, int y, Color clrColor, /*bool bCenter,*/ wchar_t* szText)
{
    if (!szText) {
        return;
    }

    Interfaces::Surface()->DrawSetTextPos(x, y);
    Interfaces::Surface()->DrawSetTextFont(drawFont);
    Interfaces::Surface()->DrawSetTextColor(clrColor);
    Interfaces::Surface()->DrawPrintText(szText, (int)wcslen(szText));
}

void CDrawings::DrawString(HFONT drawFont, int x, int y, Color textColor, const char* textString, bool bCenter) {
    if (!textString) {
        return;
    }

    wchar_t* szString = Utils::WCharConvert(textString);

    if (bCenter)
    {
        int Wide = 0, Tall = 0;

        Interfaces::Surface()->GetTextSize(drawFont, szString, Wide, Tall);

        x -= Wide / 2;
    }

    Interfaces::Surface()->DrawSetTextPos(x, y);
    Interfaces::Surface()->DrawSetTextFont(drawFont);
    Interfaces::Surface()->DrawSetTextColor(textColor);
    Interfaces::Surface()->DrawPrintText(szString, (int)wcslen(szString));
}

void CDrawings::DrawString(HFONT drawFont, int x, int y, Color clrColor, bool bCenter, const char* szText, ...)
{
    if (!szText) {
        return;
    }

    va_list va_alist;
    char szBuffer[256] = { '\0' };

    va_start(va_alist, szText);
    vsprintf(szBuffer, szText, va_alist);
    va_end(va_alist);

    wchar_t* szString = Utils::WCharConvert(szBuffer);

    if (bCenter)
    {
        int Wide = 0, Tall = 0;

        Interfaces::Surface()->GetTextSize(drawFont, szString, Wide, Tall);

        x -= Wide / 2;
    }

    Interfaces::Surface()->DrawSetTextPos(x, y);
    Interfaces::Surface()->DrawSetTextFont(drawFont);
    Interfaces::Surface()->DrawSetTextColor(clrColor);
    Interfaces::Surface()->DrawPrintText(szString, (int)strlen(szBuffer));
}

void CDrawings::DrawRect(int x, int y, int w, int h, Color clrColor, bool drawBevel)
{
    Interfaces::Surface()->DrawSetColor(clrColor);
    Interfaces::Surface()->DrawFilledRect(x, y, x + w, y + h);

    if(drawBevel) {
        DrawBevel(x, y, w, h);
    }
}

void CDrawings::DrawBevel(int x, int y, int w, int h) {
    DrawLine(x, y + (h - 1), x + (w - 1), y + (h - 1), Color(0, 0, 0, 135));
    DrawLine(x + (w - 1), y, x + (w - 1), y + (h - 1), Color(0, 0, 0, 135));

    DrawLine(x, y, x + (w - 1), y, Color(255, 255, 255, 55));
    DrawLine(x, y, x, y + (h - 1), Color(255, 255, 255, 55));
}

void CDrawings::DrawOutlineRect(int x, int y, int w, int h, Color clrColor)
{
    Interfaces::Surface()->DrawSetColor(clrColor);
    Interfaces::Surface()->DrawOutlinedRect(x, y, x + w, y + h);
}

void CDrawings::DrawLine(int x, int y, int x1, int y1, Color clrColor)
{
    Interfaces::Surface()->DrawSetColor(clrColor);
    Interfaces::Surface()->DrawLine(x, y, x1, y1);
}

void CDrawings::Circle(Vector2D position, float points, float radius, Color color)
{
    float step = (float)M_PI * 2.0f / points;
    
    for (float a = 0; a < (M_PI * 2.0f); a += step)
    {
        Vector2D start(radius * cosf(a) + position.x, radius * sinf(a) + position.y);
        Vector2D end(radius * cosf(a + step) + position.x, radius * sinf(a + step) + position.y);
        DrawLine(start.x, start.y, end.x, end.y, color);
    }
}

void CDrawings::DrawCornerBox(int x, int y, int w, int h, int cx, int cy, Color clrColor)
{
    DrawLine(x, y, x + (w / cx), y, clrColor);
    DrawLine(x, y, x, y + (h / cy), clrColor);

    DrawLine(x + w, y, x + w - (w / cx), y, clrColor);
    DrawLine(x + w, y, x + w, y + (h / cy), clrColor);

    DrawLine(x, y + h, x + (w / cx), y + h, clrColor);
    DrawLine(x, y + h, x, y + h - (h / cy), clrColor);

    DrawLine(x + w, y + h, x + w - (w / cx), y + h, clrColor);
    DrawLine(x + w, y + h, x + w, y + h - (h / cy), clrColor);
}

void CDrawings::DynamicBox(C_CSPlayer* pPlayer, const char* szName, Color clrColor)
{
    matrix3x4_t trans = pPlayer->GetRgflCoordinateFrame();

    Vector min = pPlayer->GetVecMins();
    Vector max = pPlayer->GetVecMaxs();

    Vector pointList[] = {
        Vector(min.x, min.y, min.z),
        Vector(min.x, max.y, min.z),
        Vector(max.x, max.y, min.z),
        Vector(max.x, min.y, min.z),
        Vector(max.x, max.y, max.z),
        Vector(min.x, max.y, max.z),
        Vector(min.x, min.y, max.z),
        Vector(max.x, min.y, max.z)
    };

    Vector transformed[8];

    for (int i = 0; i < 8; i++) {
        CMath::VectorTransform(pointList[i], trans, transformed[i]);
    }

    Vector flb, brt, blb, frt, frb, brb, blt, flt;

    if (!Utils::WorldToScreen(transformed[3], flb) ||
        !Utils::WorldToScreen(transformed[0], blb) ||
        !Utils::WorldToScreen(transformed[2], frb) ||
        !Utils::WorldToScreen(transformed[6], blt) ||
        !Utils::WorldToScreen(transformed[5], brt) ||
        !Utils::WorldToScreen(transformed[4], frt) ||
        !Utils::WorldToScreen(transformed[1], brb) ||
        !Utils::WorldToScreen(transformed[7], flt)) {
        return;
    }

    Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

    float left = flb.x;
    float top = flb.y;
    float right = flb.x;
    float bottom = flb.y;

    for (int i = 0; i < 8; i++) {
        if (left > arr[i].x) {
            left = arr[i].x;
        }
        if (top < arr[i].y) {
            top = arr[i].y;
        }
        if (right < arr[i].x) {
            right = arr[i].x;
        }
        if (bottom > arr[i].y) {
            bottom = arr[i].y;
        }
    }

    float x = left;
    float y = bottom;
    float w = right - left;
    float h = top - bottom;
    DrawCornerBox((int)(x - 1), (int)(y - 1), (int)(w + 2), (int)(h + 1), 3, 5, Color(0, 0, 0, 255));
    DrawCornerBox((int)x, (int)y, (int)w, (int)(h - 1), 3, 5, clrColor);

    DrawString(0, (int)(x + (w / 2)), (int)(y - 14), Color(255, 255, 255, 255), true, "%s", szName);
    int health = pPlayer->GetHealth();

    if (health > 100) {
        health = 100;
    }

    int r = (int)(255 - health * 2.55);
    int g = (int)(health * 2.55);

    int healthBar = (int)(w / 100 * health);

    DrawRect(x, (int)(y + h), w, (int)(h / 100 * 7), Color(0, 0, 0, 255));
    DrawRect(x + 1, (int)(y + h + 1), healthBar - 2, (int)((h / 100 * 6) - 2), Color(r, g, 0, 255));
}

void CDrawings::DrawTriangle(int width, int height, Color clrColor, int x, int y, bool down) {
    int hwidth = width / 2;
    int x0 = x + hwidth;
    int y0 = y - 1;
    int x1 = x + hwidth;
    if(down)
    {
        x0 = x;
        y0 = y;
        x1 = x + width;
    }
    for(int i = 0; i < height; i++) {
        if(!down)
        {
            x0 -= 1;
            x1 += 1;
            y0 += 1;
        }
        DrawLine(x0, y0, x1, y0, clrColor);
        if(down)
        {
            x0 += 1;
            x1 -= 1;
            y0 += 1;
        }
    }
}
