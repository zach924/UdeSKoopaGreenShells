#include <iostream>
#include "ButtonUnitSell.h"
#include "SelectionManager.h"
#include "YesNoPopUp.h"
#include "GameWindow.h"

ButtonUnitSell::ButtonUnitSell(int sectionOffset, int columnIndex, int rowIndex, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, state)
{
}

ButtonUnitSell::~ButtonUnitSell()
{
}

void ButtonUnitSell::DoAction()
{
	std::function<void()> yesFunction = []() {SelectionManager::GetInstance().UnitSell(); }; // TODO call sell function in selection manager (wich sell it is?)

	YesNoPopUp* popUp = new YesNoPopUp("Sell", 700, 700, yesFunction);

	GameWindow::GetInstance().AddPopUpWindow(popUp);
}

void ButtonUnitSell::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\Sell_text.bmp" , rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
