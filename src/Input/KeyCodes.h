#pragma once
#include <unordered_map>
#include <string>
#include <cctype>
#include "InputManager.h"

namespace KeyCode {
    // Константы для часто используемых клавиш
    constexpr int W = 87;
    constexpr int S = 83;
    constexpr int A = 65;
    constexpr int D = 68;
    constexpr int SPACE = 32;
    constexpr int ESCAPE = 256;
    constexpr int LEFT_ALT = 342;
    constexpr int V = 86;
    constexpr int F3 = 292;

    // ✅ Функция fromString должна быть определена ПЕРВОЙ
    inline int fromString(const std::string& keyName) {
        // Приводим к верхнему регистру для единообразия
        std::string upper = keyName;
        for (char& c : upper) {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }

        static const std::unordered_map<std::string, int> map = {
            // Буквы
            {"A", 65}, {"B", 66}, {"C", 67}, {"D", 68}, {"E", 69},
            {"F", 70}, {"G", 71}, {"H", 72}, {"I", 73}, {"J", 74},
            {"K", 75}, {"L", 76}, {"M", 77}, {"N", 78}, {"O", 79},
            {"P", 80}, {"Q", 81}, {"R", 82}, {"S", 83}, {"T", 84},
            {"U", 85}, {"V", 86}, {"W", 87}, {"X", 88}, {"Y", 89}, {"Z", 90},

            // Цифры
            {"0", 48}, {"1", 49}, {"2", 50}, {"3", 51}, {"4", 52},
            {"5", 53}, {"6", 54}, {"7", 55}, {"8", 56}, {"9", 57},

            // Специальные клавиши
            {"SPACE", 32},
            {"APOSTROPHE", 39},
            {"COMMA", 44},
            {"MINUS", 45},
            {"PERIOD", 46},
            {"SLASH", 47},
            {"SEMICOLON", 59},
            {"EQUAL", 61},
            {"LEFT_BRACKET", 91},
            {"BACKSLASH", 92},
            {"RIGHT_BRACKET", 93},
            {"GRAVE_ACCENT", 96},

            // Функциональные клавиши
            {"ESCAPE", 256},
            {"ENTER", 257},
            {"TAB", 258},
            {"BACKSPACE", 259},
            {"INSERT", 260},
            {"DELETE", 261},
            {"RIGHT", 262},
            {"LEFT", 263},
            {"DOWN", 264},
            {"UP", 265},
            {"PAGE_UP", 266},
            {"PAGE_DOWN", 267},
            {"HOME", 268},
            {"END", 269},
            {"CAPS_LOCK", 280},
            {"SCROLL_LOCK", 281},
            {"NUM_LOCK", 282},
            {"PRINT_SCREEN", 283},
            {"PAUSE", 284},

            // F-клавиши
            {"F1", 290}, {"F2", 291}, {"F3", 292}, {"F4", 293},
            {"F5", 294}, {"F6", 295}, {"F7", 296}, {"F8", 297},
            {"F9", 298}, {"F10", 299}, {"F11", 300}, {"F12", 301},
            {"F13", 302}, {"F14", 303}, {"F15", 304}, {"F16", 305},
            {"F17", 306}, {"F18", 307}, {"F19", 308}, {"F20", 309},
            {"F21", 310}, {"F22", 311}, {"F23", 312}, {"F24", 313},
            {"F25", 314},

            // Модификаторы
            {"LEFT_SHIFT", 340},
            {"LEFT_CONTROL", 341},
            {"LEFT_ALT", 342},
            {"LEFT_SUPER", 343},
            {"RIGHT_SHIFT", 344},
            {"RIGHT_CONTROL", 345},
            {"RIGHT_ALT", 346},
            {"RIGHT_SUPER", 347},
            {"MENU", 348},
        };

        auto it = map.find(upper);
        if (it != map.end()) {
            return it->second;
        }
        return -1;  // не найдено
    }

    // ✅ Теперь isPressed и isJustPressed видят fromString
    inline bool isPressed(const std::string& keyName) {
        int code = fromString(keyName);
        if (code == -1) return false;
        return InputManager::isKeyPressed(code);
    }

    inline bool isJustPressed(const std::string& keyName) {
        int code = fromString(keyName);
        if (code == -1) return false;
        return InputManager::isKeyJustPressed(code);
    }
}