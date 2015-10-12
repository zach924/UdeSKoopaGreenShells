#pragma once
#include "Button.h"
class ButtonSell :
    public Button
{
public:
    ButtonSell(int sectionOffset, int columnIndex, int rowIndex, ButtonState = ButtonState::Disabled);
    ~ButtonSell();

    void DoAction();

    void LoadTextTexture();
};