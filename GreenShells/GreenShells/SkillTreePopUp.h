#pragma once
#include <vector>
#include <map>
#include <string>
#include <functional>
#include "PopUpWindow.h"
#include "Button.h"
#include "Skills.h"

class Player;
class ButtonText;

class SkillTreePopUp
    : public PopUpWindow
{
private:
    const int HEADER_HEIGHT = 100;
    const int COST_WIDTH = 100;
    const int BUTTON_HEIGHT = 50;
    const int BUTTON_WIDTH = 130;
    int m_colomnWidth;
    int m_rowHeight;
    int m_heightSpacer;
    int m_widthSpace;
    ButtonText* m_closeButton;
    std::map<Skills, ButtonText*> m_Buttons;

    void ShowButton(ButtonText* button);
    void DrawDependencies(int firstColumn, int firstRow, int secondColumn, int secondRow);
    void DrawCostsStrings(int cost, int column);
    void SetButtonState(std::shared_ptr<Player> player, Skills skill, ButtonText* button);
    ButtonText* CreateButton(int column, int row, std::string text, std::function<void()> function, ButtonState state);
    Texture* m_scienceTexture;
    TTF_Font* m_font;
public:
    SkillTreePopUp(const char* windowName, int width, int height);
    ~SkillTreePopUp();

    void ShowWindow(SDL_Renderer* rend);

    bool handleEvent(SDL_Event& e);
};