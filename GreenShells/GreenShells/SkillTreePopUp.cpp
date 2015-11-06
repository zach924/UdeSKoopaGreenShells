#include "SkillTreePopUp.h"

SkillTreePopUp::SkillTreePopUp(const char * windowName, int width, int height)
    :PopUpWindow(windowName, width, height)
{
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

    //// Show Yes Button
    //x = m_yesButton->GetLeftX();
    //y = m_yesButton->GetTopY();
    //width = m_yesButton->GetWidth();
    //height = m_yesButton->GetHeight();
    //SDL_Rect renderQuadYes = { x, y, width, height };

    //Texture* buttonTextureYes = m_yesButton->GetButtonTexture(m_rend);
    //Texture * textTextureYes = m_yesButton->GetTextTexture(m_rend);

    //SDL_RenderCopy(m_rend, buttonTextureYes->GetTexture(), NULL, &renderQuadYes);
    //SDL_RenderCopy(m_rend, textTextureYes->GetTexture(), NULL, &renderQuadYes);

    //// Show No Button
    //x = m_noButton->GetLeftX();
    //y = m_noButton->GetTopY();
    //width = m_noButton->GetWidth();
    //height = m_noButton->GetHeight();
    //SDL_Rect renderQuadNo = { x, y, width, height };

    //Texture* buttonTextureNo = m_noButton->GetButtonTexture(m_rend);
    //Texture * textTextureNo = m_noButton->GetTextTexture(m_rend);

    //SDL_RenderCopy(m_rend, buttonTextureNo->GetTexture(), NULL, &renderQuadNo);
    //SDL_RenderCopy(m_rend, textTextureNo->GetTexture(), NULL, &renderQuadNo);

    SDL_RenderPresent(m_rend);
}

bool SkillTreePopUp::handleEvent(SDL_Event & e)
{
    return false;
}
