#pragma once
#include "Button.h"
class ButtonNo : public Button
{
public:
    ButtonNo(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state);
    ~ButtonNo();

    void DoAction();

    void LoadTextTexture(SDL_Renderer* rend = nullptr);
};
