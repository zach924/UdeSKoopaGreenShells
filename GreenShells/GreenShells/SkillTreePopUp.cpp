#include <iostream>
#include "SkillTreePopUp.h"
#include "ButtonText.h"

SkillTreePopUp::SkillTreePopUp(const char * windowName, int width, int height)
    :PopUpWindow(windowName, width, height)
{
    m_buttons.emplace_back(new ButtonText(100, 100, 100, 100, "Ranger", []() { std::cout << "Pressed Ranger button" << std::endl; }));
}

SkillTreePopUp::~SkillTreePopUp()
{
}

void SkillTreePopUp::ShowWindow(SDL_Renderer * rend)
{
    //Show Text
    SDL_RenderClear(m_rend);
    int x = 25;
    int y = 0;
    int width = 200;
    int height = m_fontSize;

    for (int i = 0; i < m_texts.size(); ++i)
    {
        SDL_Texture* texture = m_texts.at(i);

        y = (i * m_fontSize) + 10;

        SDL_Rect renderQuadText = { x, y, width, height };

        SDL_RenderCopy(m_rend, texture, NULL, &renderQuadText);
    }

    for (auto button : m_buttons)
    {
        x = button->GetLeftX();
        y = button->GetTopY();
        width = button->GetWidth();
        height = button->GetHeight();
        SDL_Rect renderQuad = { x, y, width, height };

        Texture* buttonTexture = button->GetButtonTexture(m_rend);
        Texture * textTexture = button->GetTextTexture(m_rend);

        SDL_RenderCopy(m_rend, buttonTexture->GetTexture(), NULL, &renderQuad);
        SDL_RenderCopy(m_rend, textTexture->GetTexture(), NULL, &renderQuad);
    }

    SDL_RenderPresent(m_rend);
}

bool SkillTreePopUp::handleEvent(SDL_Event & e)
{
    for (auto button : m_buttons)
    {
        if (button->IsUnpressed() && button->IsInside(e.button.x, e.button.y))
        {
            button->DoAction();
            return true;
        }
    }
    return false;
}
