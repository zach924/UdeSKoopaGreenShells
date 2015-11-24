#include <iostream>
#include "ButtonSkillTree.h"
#include "SelectionManager.h"
#include "SkillTreePopUp.h"
#include "GameWindow.h"

ButtonSkillTree::ButtonSkillTree(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonSkillTree::~ButtonSkillTree()
{
}

void ButtonSkillTree::DoAction()
{
    SkillTreePopUp* popUp = new SkillTreePopUp("Skill Tree", 1280, 720);
    GameWindow::GetInstance().AddPopUpWindow(popUp);
}

void ButtonSkillTree::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\SkillTree_text.bmp", rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
