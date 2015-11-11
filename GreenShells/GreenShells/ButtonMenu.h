#pragma once
#include "Button.h"
class ButtonMenu : public Button
{
public:
    ButtonMenu(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state);
    ~ButtonMenu();

    void DoAction();

    void LoadTextTexture(SDL_Renderer* rend = nullptr);
};

