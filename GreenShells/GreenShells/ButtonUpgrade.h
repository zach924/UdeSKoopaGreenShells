#pragma once
#include "Button.h"
class ButtonUpgrade :
    public Button
{
public:
    ButtonUpgrade(int sectionOffset, int columnIndex, int rowIndex, ButtonState = ButtonState::Disabled);
    ~ButtonUpgrade();

    void DoAction();

    void LoadTextTexture();
};