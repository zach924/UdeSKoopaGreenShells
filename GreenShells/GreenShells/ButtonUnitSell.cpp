#include <iostream>
#include "ButtonUnitSell.h"
#include "SelectionManager.h"
#include "YesNoPopUp.h"
#include "GameWindow.h"

ButtonUnitSell::ButtonUnitSell(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonUnitSell::~ButtonUnitSell()
{
}

void ButtonUnitSell::DoAction()
{
    std::function<void()> yesFunction = []() {SelectionManager::GetInstance().UnitSell(); };

    YesNoPopUp* popUp = new YesNoPopUp("Are you sure you want to sell that unit?", 350, 150, yesFunction);

    GameWindow::GetInstance().AddPopUpWindow(popUp);
}

void ButtonUnitSell::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("Resources\\Sprite\\Button\\Sell_text.bmp" , rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
