#include "SpawnUnitPopUp.h"
#include "UnitSettler.h"

#include "UnitSwordsmanI.h"
#include "UnitSwordsmanII.h"
#include "UnitSwordsmanIII.h"

#include "UnitArcherI.h"
#include "UnitArcherII.h"
#include "UnitArcherIII.h"

#include "UnitAxemanI.h"
#include "UnitAxemanII.h"

#include "UnitMaceI.h"
#include "UnitMaceII.h"

#include "UnitCannon.h"
#include "UnitShield.h"

#include "GameSession.h"
#include "Player.h"
#include "SelectionManager.h"



SpawnUnitPopUp::SpawnUnitPopUp(const char* windowName, int width, int height)
    : PopUpWindow(windowName, width, height)
{
    int buffer = 20;
    int currentX = 50;
    int currentY = m_fontSize + buffer;
    int buttonWidth = 200;
    int buttonHeight = 50;
    auto currentPlayer = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());

    ButtonState state = currentPlayer->HasRessourcesFor(currentPlayer->GetSwordsmanTier())? ButtonState::Unpressed : ButtonState::Disabled;
    std::function<void()> spawnUnit = []() {SelectionManager::GetInstance().SpawnSwordsman(); };
    m_allButtons[0] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Swordsman", spawnUnit, nullptr, state);

    currentY += buttonHeight + buffer;
    state = currentPlayer->HasRessourcesFor(currentPlayer->GetAxemanTier()) ? ButtonState::Unpressed : ButtonState::Disabled;
    spawnUnit = []() {SelectionManager::GetInstance().SpawnAxeman(); };
    m_allButtons[1] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Axeman", spawnUnit, nullptr, state);

    currentY += buttonHeight + buffer;
    state = currentPlayer->HasRessourcesFor(currentPlayer->GetCannonTier()) ? ButtonState::Unpressed : ButtonState::Disabled;
    spawnUnit = []() {SelectionManager::GetInstance().SpawnCannon(); };
    m_allButtons[2] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Cannon", spawnUnit, nullptr, state);

    currentY += buttonHeight + buffer;
    state = currentPlayer->HasRessourcesFor(currentPlayer->GetSettlerTier()) ? ButtonState::Unpressed : ButtonState::Disabled;
    spawnUnit = []() {SelectionManager::GetInstance().SpawnSettler(); };
    m_allButtons[3] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Settler", spawnUnit, nullptr, state);
    
    currentX += buttonWidth + buffer;
    currentY = m_fontSize + buffer;
    state = currentPlayer->HasRessourcesFor(currentPlayer->GetArcherTier()) ? ButtonState::Unpressed : ButtonState::Disabled;
    spawnUnit = []() {SelectionManager::GetInstance().SpawnArcher(); };
    m_allButtons[4] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Archer", spawnUnit, nullptr, state);

    currentY += buttonHeight + buffer;
    state = currentPlayer->HasRessourcesFor(currentPlayer->GetMaceTier()) ? ButtonState::Unpressed : ButtonState::Disabled;
    spawnUnit = []() {SelectionManager::GetInstance().SpawnMace(); };
    m_allButtons[5] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Mace", spawnUnit, nullptr, state);

    currentY += buttonHeight + buffer;
    state = currentPlayer->HasRessourcesFor(currentPlayer->GetShieldTier()) ? ButtonState::Unpressed : ButtonState::Disabled;
    spawnUnit = []() {SelectionManager::GetInstance().SpawnShield(); };
    m_allButtons[6] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Shield", spawnUnit, nullptr, state);
    
    currentY += buttonHeight + buffer;
    currentY += buttonHeight + buffer;
    spawnUnit = []() {};
    m_allButtons[7] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Cancel", spawnUnit, nullptr, ButtonState::Unpressed);

}


SpawnUnitPopUp::~SpawnUnitPopUp()
{
}

bool SpawnUnitPopUp::handleEvent(SDL_Event & e)
{
    for (ButtonText* button : m_allButtons)
    {
        if (button->IsUnpressed() && button->IsInside(e.button.x, e.button.y))
        {
            button->DoAction();
            return true;
        }
    }
    return false;
}

void SpawnUnitPopUp::ShowWindow(SDL_Renderer * rend)
{
    SDL_RenderClear(m_rend);
    int horizontalPos = 25;
    int verticalPos = 0;
    int height = m_fontSize;

    Texture menuHeader;
    menuHeader.CreateFromText("Spawn Unit", m_font, m_rend);
    SDL_Rect menuHeaderRect{ horizontalPos, verticalPos, menuHeader.GetWidth(), menuHeader.GetHeight() };
    SDL_RenderCopy(m_rend, menuHeader.GetTexture(), NULL, &menuHeaderRect);

    for (ButtonText* button : m_allButtons)
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

    SDL_RenderPresent(m_rend);
}
