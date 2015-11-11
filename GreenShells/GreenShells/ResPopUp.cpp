#include "ResPopUp.h"

#include "GameWindow.h"



ResPopUp::ResPopUp(const char* windowName, int width, int height)
    :PopUpWindow(windowName, width, height)
{
    int buffer = 20;
    int sectionBuffer = 40;
    int currentX = 50;
    int currentY = m_fontSize + buffer;
    int buttonWidth = 120;
    int buttonHeight = 50;

    m_allResButtons[0] = new ButtonResSelect("1280_720", currentX, currentY, buttonWidth, buttonHeight, RES_1280_720, ButtonState::Unpressed);

    currentY += buffer + buttonHeight;
    m_allResButtons[1] = new ButtonResSelect("1600_900", currentX, currentY, buttonWidth, buttonHeight, RES_1600_900, ButtonState::Unpressed);

    currentY += buffer + buttonHeight;
    m_allResButtons[2] = new ButtonResSelect("1600_1024", currentX, currentY, buttonWidth, buttonHeight, RES_1600_1024, ButtonState::Unpressed);

    currentY += sectionBuffer + buttonHeight;
    m_quitButton = new ButtonQuit(currentX, currentY, buttonWidth, buttonHeight, ButtonState::Unpressed);

    currentY = m_fontSize + buffer;
    currentX += buttonWidth + buffer;
    m_allResButtons[3] = new ButtonResSelect("1920_1080", currentX, currentY, buttonWidth, buttonHeight, RES_1920_1080, ButtonState::Unpressed);

    currentY += buffer + buttonHeight;
    m_allResButtons[4] = new ButtonResSelect("1920_1080*", currentX, currentY, buttonWidth, buttonHeight, RES_1920_1080_FullScreen, ButtonState::Unpressed);

    currentY += buffer + buttonHeight;
    currentY += sectionBuffer + buttonHeight;
    m_saveButton = new ButtonSave(currentX, currentY, buttonWidth, buttonHeight, ButtonState::Unpressed);
    
}


ResPopUp::~ResPopUp()
{
}

void ResPopUp::ShowWindow(SDL_Renderer * rend)
{
    SDL_RenderClear(m_rend);
    int horizontalPos = 25;
    int verticalPos = 0;
    int height = m_fontSize;

    Texture menuHeader;
    menuHeader.CreateFromText("Menu", m_font, m_rend);
    SDL_Rect menuHeaderRect{ horizontalPos, verticalPos, menuHeader.GetWidth(), menuHeader.GetHeight() };
    SDL_RenderCopy(m_rend, menuHeader.GetTexture(), NULL, &menuHeaderRect);

    for (ButtonResSelect* button : m_allResButtons)
    {
        //the button
        Texture* buttonTexture = button->GetButtonTexture(m_rend);
        int buttonX = button->GetLeftX();
        int buttonY = button->GetTopY();

        //this will stretch the texture to the following width/height
        int buttonWidth = button->GetWidth();
        int buttonHeight = button->GetHeight();
        SDL_Rect buttonRect = { buttonX, buttonY, buttonWidth, buttonHeight };
        SDL_RenderCopy(m_rend, buttonTexture->GetTexture(), NULL, &buttonRect);

        //the text on the button
        Texture * textTexture = button->GetTextTexture(m_rend);
        int textH = textTexture->GetHeight();
        int textW = textTexture->GetWidth();
        int horizontalOffset = (buttonWidth - textW) / 2;
        int verticalOffset = (buttonHeight - textH) / 2;
        SDL_Rect textRect = { buttonX + horizontalOffset, buttonY + verticalOffset, textW, textH };
        SDL_RenderCopy(m_rend, textTexture->GetTexture(), NULL, &textRect);
    }
    RenderButton(m_quitButton);
    RenderButton(m_saveButton);

    SDL_RenderPresent(m_rend);
}

void ResPopUp::RenderButton(Button* button)
{
    //the button
    Texture* buttonTexture = button->GetButtonTexture(m_rend);
    int buttonX = button->GetLeftX();
    int buttonY = button->GetTopY();

    //this will stretch the texture to the following width/height
    int buttonWidth = button->GetWidth();
    int buttonHeight = button->GetHeight();
    SDL_Rect buttonRect = { buttonX, buttonY, buttonWidth, buttonHeight };
    SDL_RenderCopy(m_rend, buttonTexture->GetTexture(), NULL, &buttonRect);

    //the text on the button
    Texture * textTexture = button->GetTextTexture(m_rend);
    int textH = textTexture->GetHeight();
    int textW = textTexture->GetWidth();
    int horizontalOffset = (buttonWidth - textW) / 2;
    int verticalOffset = (buttonHeight - textH) / 2;
    SDL_Rect textRect = { buttonX + horizontalOffset, buttonY + verticalOffset, textW, textH };
    SDL_RenderCopy(m_rend, textTexture->GetTexture(), NULL, &textRect);
}

bool ResPopUp::handleEvent(SDL_Event & e)
{
    for (ButtonResSelect* button : m_allResButtons)
    {
        if (button->IsUnpressed() && button->IsInside(e.button.x, e.button.y))
        {
            GameWindow::GetInstance().ChangeResolution(button->GetRes());
            return true;
        }
    }

    if (m_quitButton->IsUnpressed() && m_quitButton->IsInside(e.button.x, e.button.y))
    {
        m_quitButton->DoAction();
        return true;
    }
    
    if (m_saveButton->IsUnpressed() && m_saveButton->IsInside(e.button.x, e.button.y))
    {
        m_saveButton->DoAction();
        return true;
    }
    
    return false;
}
