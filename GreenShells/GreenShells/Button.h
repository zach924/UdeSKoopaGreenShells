#pragma once
#include "Texture.h"

enum ButtonState
{
    Unpressed,
    Pressed,
    Disabled
};

class Button
{
public:
    static const int STANDARD_BUTTON_HEIGHT = 50;
    static const int STANDARD_BUTTON_WIDTH = 90;

protected:
    // Not static (no curiously recurring template pattern like tile)
    // because we do not need since only one button of each will exist;
    Texture m_textTexture;

    ButtonState m_buttonState;
    virtual void LoadTextTexture(SDL_Renderer* rend) = 0;
    Texture m_unpressedButton;
    Texture m_pressedButton;
    const Color DISABLED_BUTTON_COLOR{ 192,192,192 };
    const Color DEFAULT_BUTTON_COLOR{ 255,255,255 };
    void LoadButtonTextures(SDL_Renderer* rend);

private:

    int m_topLimit;
    int m_botLimit;
    int m_rightLimit;
    int m_lefLimit;

public:
    Button(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state);
    Button(int posX, int posY, int width, int height, ButtonState state);
    ~Button();

    bool IsInside(int xPos, int yPos);
    bool IsUnpressed();

    virtual void DoAction() = 0;
    void SetButtonState(ButtonState state);

    int GetTopY();
    int GetLeftX();

    int GetWidth();
    int GetHeight();

    /*
    * Omitting rend, and it will be rendered for the main game window
    */
    virtual Texture* GetTextTexture(SDL_Renderer* rend = nullptr);
    /*
    * Omitting rend, and it will be rendered for the main game window
    */
    virtual Texture* GetButtonTexture(SDL_Renderer* rend = nullptr);
};
