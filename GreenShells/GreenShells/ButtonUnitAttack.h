#pragma once
#include "Button.h"

class ButtonUnitAttack : public Button
{
public:
    ButtonUnitAttack(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState = ButtonState::Disabled);
    ~ButtonUnitAttack();

    void DoAction();

    void LoadTextTexture(SDL_Renderer* rend);
};
