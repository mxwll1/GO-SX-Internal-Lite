#ifndef draw_h
#define draw_h

#include "SDK/SDK.h"
#include "SDK/CCSPlayer.h"

#ifndef CP_UTF8
#define CP_UTF7	65000   /* UTF-7 translation.  */
#define CP_UTF8	65001   /* UTF-8 translation.  */
#endif

class CDrawings
{
public:
	CDrawings();
	~CDrawings();

    static CDrawings* Instance() {
        if(!instance) {
            instance = new CDrawings();
        }

        return instance;
    }

    void	DrawString(int font, int x, int y, Color clrColor, /*bool bCenter,*/ wchar_t* szText);
    void    DrawString(int font, int x, int y, Color textColor, const char* textString, bool bCenter);
    void	DrawString(int font, int x, int y, Color clrColor, bool bCenter, const char* szText, ...);
    void	DrawString(HFONT font, int x, int y, Color clrColor, /*bool bCenter,*/ wchar_t* szText);
    void    DrawString(HFONT font, int x, int y, Color textColor, const char* textString, bool bCenter);
    void	DrawString(HFONT font, int x, int y, Color clrColor, bool bCenter, const char* szText, ...);
    void    DrawShadowString(int font, int x, int y, Color clrColor, bool bCenter, const char* szText, ...);
    void    DrawShadowString(HFONT drawFont, int x, int y, Color clrColor, bool bCenter, const char* szText, ...);
	void	DrawRect(int x, int y, int w, int h, Color clrColor, bool drawBevel = false);
    void    DrawBevel(int x, int y, int w, int h);
	void	DrawOutlineRect(int x, int y, int w, int h, Color clrColor);
	void	DrawLine(int x0, int y0, int x1, int y1, Color clrColor);
    void    Circle(Vector2D position, float points, float radius, Color color);
	void	DrawCornerBox(int x, int y, int w, int h, int cx, int cy, Color clrColor);
    void	DynamicBox(C_CSPlayer* pPlayer, const char* szName, Color clrColor);
    void    DrawTriangle(int width, int height, Color clrColor, int x = 0, int y = 0, bool down = false);
    HFONT   GetFont(const char* fontName, int size, FontFlags flags);
    void    CheckFonts();

private:
    static  CDrawings*  instance;
            HFONT       hFont           = NULL;
            HFONT       bFont           = NULL;
            int         iScreenWidth    = 0;
            int         iScreenHeight   = 0;
};

#endif
