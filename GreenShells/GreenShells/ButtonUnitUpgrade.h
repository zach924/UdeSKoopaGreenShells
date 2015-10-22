#pragma once
#include "Button.h"
class ButtonUnitUpgrade :
    public Button
{
public:
    ButtonUnitUpgrade(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState = ButtonState::Disabled);
    ~ButtonUnitUpgrade();

    void DoAction();

    void LoadTextTexture();
};