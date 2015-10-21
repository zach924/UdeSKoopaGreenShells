#include <iostream>
#include "ButtonSkillTree.h"
#include "SelectionManager.h"

ButtonSkillTree::ButtonSkillTree(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonSkillTree::~ButtonSkillTree()
{
}

void ButtonSkillTree::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonSkillTree::LoadTextTexture()
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\SkillTree_text.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
