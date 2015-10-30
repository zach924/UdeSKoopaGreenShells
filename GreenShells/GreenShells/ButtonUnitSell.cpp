#include <iostream>
#include "ButtonUnitSell.h"
#include "SelectionManager.h"
#include "YesNoPopUp.h"
#include "GameWindow.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif // _DEBUG

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif
ButtonUnitSell::ButtonUnitSell(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonUnitSell::~ButtonUnitSell()
{
}

void ButtonUnitSell::DoAction()
{
	std::function<void()> yesFunction = []() {SelectionManager::GetInstance().UnitSell(); }; // TODO call sell function in selection manager (wich sell it is?)

	YesNoPopUp* popUp = new YesNoPopUp("Are you sure you want to sell that unit?", 350, 150, yesFunction);

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
