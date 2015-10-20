#pragma once
#include "Button.h"
class ButtonUnitUpgrade :
    public Button
{
public:
    ButtonUnitUpgrade(int sectionOffset, int columnIndex, int rowIndex, int buttonOffset, ButtonState = ButtonState::Disabled);
    ~ButtonUnitUpgrade();

    void DoAction();

    void LoadTextTexture();
};