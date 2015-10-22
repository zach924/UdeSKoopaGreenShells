#pragma once
#include "Button.h"
class ButtonSkillTree :
    public Button
{
public:
    ButtonSkillTree(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState = ButtonState::Disabled);
    ~ButtonSkillTree();

    void DoAction();

    void LoadTextTexture();
};