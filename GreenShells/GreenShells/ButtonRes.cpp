#include <iostream>
#include "ButtonRes.h"

#include "ResPopUp.h"
#include "GameWindow.h"


ButtonRes::ButtonRes(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
	:Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}


ButtonRes::~ButtonRes()
{
}

void ButtonRes::DoAction()
{
	//std::function<void()> yesFunction = []() {SelectionManager::GetInstance().UnitSell(); };

	ResPopUp* popUp = new ResPopUp("res", 450, 600);
	//YesNoPopUp* popUp = new YesNoPopUp("Are you sure you want to sell that unit?", 350, 150, yesFunction);

	GameWindow::GetInstance().AddPopUpWindow(popUp);
}

void ButtonRes::LoadTextTexture(SDL_Renderer* rend)
{
	try
	{
		m_textTexture.LoadFromFile("..\\Sprite\\Button\\No_text.bmp", rend);
        std::cout << "Loading TEXT_BUTTON_RES" << std::endl;

	}
	catch (std::exception e)
	{
		std::string msg{ e.what() };
		std::cout << msg << std::endl;
	}
}