#pragma once
#include "Button.h"
class ButtonDistrictCancel :
    public Button
{
public:
    ButtonDistrictCancel(int sectionOffset, int columnIndex, int rowIndex, ButtonState = ButtonState::Disabled);
    ~ButtonDistrictCancel();

    void DoAction();

    void LoadTextTexture();
};