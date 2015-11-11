#include <iostream>
#include "ButtonMenu.h"

#include "ResPopUp.h"
#include "GameWindow.h"


ButtonMenu::ButtonMenu(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}


ButtonMenu::~ButtonMenu()
{
}

void ButtonMenu::DoAction()
{
    ResPopUp* popUp = new ResPopUp("Menu", 360, 375);

    GameWindow::GetInstance().AddPopUpWindow(popUp);
}

void ButtonMenu::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.CreateFromText("Menu");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}