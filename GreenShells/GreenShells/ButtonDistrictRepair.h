#pragma once
#include "Button.h"
class ButtonDistrictRepair :
    public Button
{
public:
    ButtonDistrictRepair(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState = ButtonState::Disabled);
    ~ButtonDistrictRepair();

    void DoAction();

    void LoadTextTexture(SDL_Renderer* rend);
};