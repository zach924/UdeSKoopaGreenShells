#pragma once
#include "Button.h"
class ButtonDistrictSell :
    public Button
{
public:
    ButtonDistrictSell(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState = ButtonState::Disabled);
    ~ButtonDistrictSell();

    void DoAction();

    void LoadTextTexture(SDL_Renderer* rend);
};