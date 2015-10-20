#pragma once
#include "Button.h"
class ButtonDistrictSell :
    public Button
{
public:
    ButtonDistrictSell(int sectionOffset, int columnIndex, int rowIndex, int buttonOffset, ButtonState = ButtonState::Disabled);
    ~ButtonDistrictSell();

    void DoAction();

    void LoadTextTexture();
};