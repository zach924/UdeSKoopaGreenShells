#pragma once
#include <string>
#include "Button.h"
#include <functional>

class ButtonText :
    public Button
{
private:
    std::string m_text;
    std::function<void()> m_function;
public:
    ButtonText(int posX, int posY, int width, int height, std::string text, std::function<void()> lambda, ButtonState state = ButtonState::Unpressed);
    ~ButtonText();
    virtual void DoAction();

    void LoadTextTexture(SDL_Renderer* rend = nullptr);
};