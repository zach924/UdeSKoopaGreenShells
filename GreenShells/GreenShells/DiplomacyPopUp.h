#pragma once
#include "PopUpWindow.h"
#include <vector>

class ButtonDiplomacyAction;

class DiplomacyPopUp : public PopUpWindow
{
    static const char* WINDOW_NAME;
    static const int WINDOW_HEIGHT;
    static const int WINDOW_WIDTH;

    //CONSTANTS
    const char* LARGEST_NAME = "ZZZZZZZZZZZZZZZZZZZZZZZ";
    const char* WAR_TEXT = "At war";
    const char* PEACE_TEXT = "At peace";
    const char* ALLIANCE_TEXT = "Allied";
    const char* NEGOCIATING_PEACE_TEXT = "Negociating peace";
    const char* NEGOCIATING_ALLIANCE_TEXT = "Negociating an alliance";
    const int BUTTON_WIDTH = 120;
    const int BUTTON_HEIGHT = 40;

    std::vector <std::pair<ButtonDiplomacyAction, std::function<void()> > > m_buttons;
    TTF_Font* m_textFont;
    TTF_Font* m_buttonFont;

    void ClearButtons();

public:
    DiplomacyPopUp();
    ~DiplomacyPopUp();
    virtual bool handleEvent(SDL_Event& e);
    virtual void ShowWindow(SDL_Renderer* rend);
};

