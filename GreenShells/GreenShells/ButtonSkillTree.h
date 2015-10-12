#pragma once
#include "Button.h"
class ButtonSkillTree :
    public Button
{
public:
    ButtonSkillTree(int sectionOffset, int columnIndex, int rowIndex, ButtonState = ButtonState::Disabled);
    ~ButtonSkillTree();

    void DoAction();

    void LoadTextTexture();
};