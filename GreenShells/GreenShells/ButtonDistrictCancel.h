#pragma once
#include "Button.h"
class ButtonDistrictCancel :
    public Button
{
public:
    ButtonDistrictCancel(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState = ButtonState::Disabled);
    ~ButtonDistrictCancel();

    void DoAction();

    void LoadTextTexture(SDL_Renderer* rend);
};