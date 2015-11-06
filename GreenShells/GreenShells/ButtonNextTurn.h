#pragma once
#include "Button.h"
class ButtonNextTurn :
    public Button
{
public:
    ButtonNextTurn(int posX, int posY, int width, int height, ButtonState state = ButtonState::Unpressed);
    ~ButtonNextTurn();
    virtual void DoAction();

    void LoadTextTexture(SDL_Renderer* rend = nullptr);
};

