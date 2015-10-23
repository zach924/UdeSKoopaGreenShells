#pragma once
#include "Button.h"
class ButtonConstructDistrict :
    public Button
{
public:
    ButtonConstructDistrict(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState = ButtonState::Disabled);
    ~ButtonConstructDistrict();

    void DoAction();

    void LoadTextTexture(SDL_Renderer* rend);
};