#pragma once
#include "Button.h"
class ButtonSpawnUnit :
    public Button
{
public:
    ButtonSpawnUnit(int sectionOffset, int columnIndex, int rowIndex, int buttonOffset, ButtonState = ButtonState::Disabled);
    ~ButtonSpawnUnit();

    void DoAction();

    void LoadTextTexture();
};