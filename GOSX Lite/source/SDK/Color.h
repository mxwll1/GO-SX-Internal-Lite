#pragma once

#ifndef color_h
#define color_h

#include "Definitions.h"
#include <stdint.h>

#define DEFCOLOR_SRC(name, r, g, b) static Color name##(uint8_t a = 255){ \
                                                       return Color(r, g, b, a); \
                                                  }
class Color {
public:
    // constructors
    Color() {
        *((int *)this) = 0;
    }

    Color(uint8_t r, uint8_t g, uint8_t b) {
        SetColor(r, g, b, 255);
    }

    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        SetColor(r, g, b, a);
    }

    void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0) {
        _color[0] = (uint8_t)r;
        _color[1] = (uint8_t)g;
        _color[2] = (uint8_t)b;
        _color[3] = (uint8_t)a;
    }

    void GetColor(uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) const {
        r = _color[0];
        g = _color[1];
        b = _color[2];
        a = _color[3];
    }

    static Color FromARGB(unsigned long color) {
        int a = (color & 0xFF000000) >> 24;
        int r = (color & 0x00FF0000) >> 16;
        int g = (color & 0x0000FF00) >> 8;
        int b = (color & 0x000000FF);

        return Color(r, g, b, a);
    }

    void SetARGB(unsigned long color) {
        int a = (color & 0xFF000000) >> 24;
        int r = (color & 0x00FF0000) >> 16;
        int g = (color & 0x0000FF00) >> 8;
        int b = (color & 0x000000FF);

        SetColor(r, g, b, a);
    }

    uint32_t GetARGB() const {
        int a = (_color[3]) >> 24;
        int r = (_color[0]) >> 16;
        int g = (_color[1]) >> 8;
        int b = (_color[2]);

        return a | r | g | b;
    }

    float Base() {
        float clr[3];

        clr[0] = _color[0] / 255.0f;
        clr[1] = _color[1] / 255.0f;
        clr[2] = _color[2] / 255.0f;

        return clr[0];
    }

    uint8_t &operator[](int index) {
        return _color[index];
    }

    const uint8_t &operator[](int index) const {
        return _color[index];
    }

    bool operator == (const Color &rhs) const {
        return (*((int *)this) == *((int *)&rhs));
    }

    bool operator != (const Color &rhs) const {
        return !(operator==(rhs));
    }

    int r() { return _color[0]; }
    int g() { return _color[1]; }
    int b() { return _color[2]; }
    int a() { return _color[3]; }

    int GetR() { return _color[0]; }
    int GetG() { return _color[1]; }
    int GetB() { return _color[2]; }
    int GetA() { return _color[3]; }

    void SetR(uint8_t _i) { _color[0] = _i; }
    void SetG(uint8_t _i) { _color[1] = _i; }
    void SetB(uint8_t _i) { _color[2] = _i; }
    void SetA(uint8_t _i) { _color[3] = _i; }

    Color &operator=(const Color &rhs) {
        *(int*)(&_color[0]) = *(int*)&rhs._color[0];
        return *this;
    }

    Color operator+(const Color &rhs) const {
        int red = _color[0] + rhs._color[0];
        int green = _color[1] + rhs._color[1];
        int blue = _color[2] + rhs._color[2];
        int alpha = _color[3] + rhs._color[3];

        red = red > 255 ? 255 : red;
        green = green > 255 ? 255 : green;
        blue = blue > 255 ? 255 : blue;
        alpha = alpha > 255 ? 255 : alpha;

        return Color(red, green, blue, alpha);
    }

    Color operator-(const Color &rhs) const {
        int red = _color[0] - rhs._color[0];
        int green = _color[1] - rhs._color[1];
        int blue = _color[2] - rhs._color[2];
        int alpha = _color[3] - rhs._color[3];

        red = red < 0 ? 0 : red;
        green = green < 0 ? 0 : green;
        blue = blue < 0 ? 0 : blue;
        alpha = alpha < 0 ? 0 : alpha;
        return Color(red, green, blue, alpha);
    }

    operator const uint8_t*() {
        return (uint8_t*)(&_color[0]);
    }

    //DEFCOLOR_SRC(Gosxctvis, 0, 153, 255);
    //DEFCOLOR_SRC(Gosxct, 102, 255, 0);
    //DEFCOLOR_SRC(Gosxtvis, 255, 170, 0);
    //DEFCOLOR_SRC(Gosxt, 255, 0, 180);
private:
    uint8_t _color[4];
};

#endif // !color_h
