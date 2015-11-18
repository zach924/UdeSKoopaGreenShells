#pragma once
#include "Button.h"
class ButtonDiplomacy :
    public Button
{
    const Color NEGOCIATING_COLOR = { 255,128,0 };
    Texture m_negociatingTexture;
public:
    ButtonDiplomacy(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState = ButtonState::Disabled);
    ~ButtonDiplomacy();

    void DoAction();

    void LoadTextTexture(SDL_Renderer* rend);

    //override
    virtual Texture* GetButtonTexture(SDL_Renderer* rend = nullptr);    
    //override
    virtual Texture* GetTextTexture(SDL_Renderer* rend = nullptr);
};