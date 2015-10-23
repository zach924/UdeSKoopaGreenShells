#pragma once
#include "Button.h"
class ButtonUnitHeal :
    public Button
{
public:
    ButtonUnitHeal(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState = ButtonState::Disabled);
    ~ButtonUnitHeal();

    void DoAction();

    void LoadTextTexture(SDL_Renderer* rend);
};

