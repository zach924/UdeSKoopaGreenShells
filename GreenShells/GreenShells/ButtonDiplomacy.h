#pragma once
#include "Button.h"
class ButtonDiplomacy :
    public Button
{
public:
    ButtonDiplomacy(int sectionOffset, int columnIndex, int rowIndex, ButtonState = ButtonState::Disabled);
    ~ButtonDiplomacy();

    void DoAction();

    void LoadTextTexture(SDL_Renderer* rend);
};