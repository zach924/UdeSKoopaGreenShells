#pragma once
#include "Button.h"
class ButtonSave :
    public Button
{
public:
    ButtonSave(int posX, int posY, int width, int height, ButtonState state);

    void DoAction();

    void LoadTextTexture(SDL_Renderer* rend = nullptr);

    ~ButtonSave();
};

