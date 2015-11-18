#pragma once
#include "Button.h"
#include "Texture.h"

class ButtonNextTurn : public Button
{
    Texture m_waitingTexture;
public:
    ButtonNextTurn(int posX, int posY, int width, int height, ButtonState state = ButtonState::Unpressed);
    ~ButtonNextTurn();
    virtual void DoAction();

    void LoadTextTexture(SDL_Renderer* rend = nullptr);
    virtual Texture* GetTextTexture(SDL_Renderer* rend = nullptr);
};

