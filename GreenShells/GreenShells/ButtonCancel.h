#pragma once
#include "Button.h"
class ButtonCancel :
    public Button
{
public:
    ButtonCancel(int sectionOffset, int columnIndex, int rowIndex, ButtonState = ButtonState::Disabled);
    ~ButtonCancel();

    void DoAction();

    void LoadTextTexture();
};