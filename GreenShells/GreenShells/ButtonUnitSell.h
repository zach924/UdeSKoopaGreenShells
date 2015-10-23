#pragma once
#include "Button.h"
class ButtonUnitSell :
    public Button
{
public:
    ButtonUnitSell(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState = ButtonState::Disabled);
    ~ButtonUnitSell();

    void DoAction();

    void LoadTextTexture(SDL_Renderer* rend);
};