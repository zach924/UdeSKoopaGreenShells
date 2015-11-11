#pragma once
#include "PopUpWindow.h"
#include "ButtonResSelect.h"
#include "ButtonQuit.h"
#include "ButtonSave.h"

class MenuPopUp :
    public PopUpWindow
{
private:

    ButtonResSelect* m_allResButtons [5];
    ButtonQuit * m_quitButton;
    ButtonSave * m_saveButton;

public:
    MenuPopUp(const char* windowName, int width, int height);
    ~MenuPopUp();

    void ShowWindow(SDL_Renderer* rend);

    bool handleEvent(SDL_Event& e);
    void RenderButton(Button* button);

};

