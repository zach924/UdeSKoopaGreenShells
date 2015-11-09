#include <iostream>
#include "ButtonDiplomacy.h"
#include "SelectionManager.h"
#include "DiplomacyPopUp.h"
#include "GameWindow.h"

ButtonDiplomacy::ButtonDiplomacy(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonDiplomacy::~ButtonDiplomacy()
{
}

void ButtonDiplomacy::DoAction()
{
    DiplomacyPopUp* popUp = new DiplomacyPopUp();
    GameWindow::GetInstance().AddPopUpWindow(popUp);
}

void ButtonDiplomacy::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\Diplomacy_text.bmp", rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}