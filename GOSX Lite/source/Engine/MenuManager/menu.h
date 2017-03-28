//
//  menu.hpp
//  GOSX Pro
//
//  Created by Andre Kalisch on 02.03.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef menu_h
#define menu_h

#include "Engine/DrawManager/draw.h"
#include "Engine/SettingsManager/SimpleIni.h"
#include "Engine/functions.h"

enum FieldType_t {
    FIELDTYPE_BOOL = 0,
    FIELDTYPE_INPUT,
    FIELDTYPE_FLOAT,
    FIELDTYPE_INT,
    FIELDTYPE_COLOR,
    FIELDTYPE_SELECT
};

typedef struct
{
    char    m_szDefinition[12];
    char    m_szShiftDefinition[12];
    char    m_szAltDefinition[12];
}KeyStroke_t;

class CHackMenu {
public:
    CHackMenu();
    static CHackMenu* Instance() {
        if(!instance) {
            instance = new CHackMenu();
        }

        return instance;
    }
    void OpenMenu(bool init = false);
    void DrawMenu();
    void CloseMenu();
    bool IsMenuOpen();
    int GetCursorPosition();
    void SetCursorPosition(int position);
    int GetItemCount();
    void HandleInput(int keynum);
    void ClickHandler();
    void SetMouseState(bool released = false);
    void SetMousePressed(bool value = false);
private:
    void AddTab(const char* section);
    void AddMenuItem(const char *section, const char* key, int col, int row, FieldType_t type);
    void DrawCheckbox(int col, int row, bool value);
    void DrawMouseCursor(int mx, int my);
    void DrawHeader();
    void DrawSaveButton();
    void DrawColorSet(const char *section, const char* key, int x, int y, Color value);
    void DrawSlider(const char *section, const char* key, int x, int y, float value, float minValue, float maxValue);
    void DrawPercentSlider(const char *section, const char* key, int x, int y, int value, int minValue, int maxValue);
    void DrawColorSlider(const char *section, const char* key, int x, int y, int value, Color colorValue);
    void DrawInputField(const char *section, const char *key, int x, int y, std::string value);
    void DrawSelectField(const char *section, const char *key, int x, int y, int value, std::map<int, const char*> list, std::map<int, const char*> values);
    void SaveMousePosition();
    bool IsMouseOverThis(int x, int y, int w, int h);
protected:
    static CHackMenu* instance;
    CDrawings* dMgr = nullptr;
    bool MenuOpen = false;
    bool ClickedOnce = false;
    int CursorPosition = 1;
    int baseHeight = 0;
    int baseWidth = 0;
    int baseX = 0;
    int baseY = 0;
    int ItemIndex = 1;
    int tabCount = 0;
    int activeTab = 1;
    int InputIndex = 1;
    int activeInput = 0;
    int selectIndex = 1;
    int activeSelect = 0;
    HFONT headerFont = NULL;
    HFONT sliderFont = NULL;
    HFONT colorSliderFont = NULL;
    bool mouseReleased = false;
    bool mousePressed = false;
    std::string m_szCurrentString[100];
    std::size_t m_nCurrentPos[100];
    bool stringIsEmpty = false;
    int lastMousePosX = 0;
    int lastMousePosY = 0;
    IConVar* mouseEnable = nullptr;
    std::map<const char*, int> tabIndex;
    std::map<int, const char*> indexTab;
    std::map<const char*, int> menuIndex;
    std::map<int, const char*> indexMenu;
};

#endif /* menu_h */
