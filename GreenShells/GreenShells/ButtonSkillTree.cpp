#include <iostream>
#include "ButtonSkillTree.h"
#include "SelectionManager.h"

//TODO: to be removed
#include "GameSession.h"
#include "Map.h"

ButtonSkillTree::ButtonSkillTree(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonSkillTree::~ButtonSkillTree()
{
}

void ButtonSkillTree::DoAction()
{
	// TODO: do action

	//TODO: to be removed

	Map m = GameSession::GetInstance().GetWorldState()->GetMapCopy();
	std::vector<Position> poss = m.GetArea(Position(1, 1), 2);
	std::cout << "Number of tile: " + poss.size() << std::endl;
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
