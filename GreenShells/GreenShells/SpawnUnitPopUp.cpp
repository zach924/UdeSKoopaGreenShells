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
    , m_allButtons()
{
    int buffer = 20;
    int currentX = 50;
    int currentY = m_fontSize + buffer;
    int buttonWidth = 200;
    int buttonHeight = 50;
    auto currentPlayer = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    auto armySkillTree = currentPlayer->GetArmySkillTree();

    ButtonState state;

    if (armySkillTree.SwordT3)
    {
        state = currentPlayer->HasEnoughWeapons(UnitSwordsmanIII::WEAPON_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
        m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Swordsman MK3", []() {SelectionManager::GetInstance().CreateUnitPressed(UnitSwordsmanIII::UNIT_TYPE); }, nullptr, state));
    }
    else if (armySkillTree.SwordT2)
    {
        state = currentPlayer->HasEnoughWeapons(UnitSwordsmanII::WEAPON_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
        m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Swordsman MK2", []() {SelectionManager::GetInstance().CreateUnitPressed(UnitSwordsmanII::UNIT_TYPE); }, nullptr, state));
    }
    else
    {
        state = currentPlayer->HasEnoughWeapons(UnitSwordsmanI::WEAPON_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
        m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Swordsman MK1", []() {SelectionManager::GetInstance().CreateUnitPressed(UnitSwordsmanI::UNIT_TYPE); }, nullptr, state));
    }

    currentY += buttonHeight + buffer;

    if (armySkillTree.AxeT2)
    {
        state = currentPlayer->HasEnoughWeapons(UnitAxemanII::WEAPON_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
        m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Axeman MK2", []() {SelectionManager::GetInstance().CreateUnitPressed(UnitAxemanII::UNIT_TYPE); }, nullptr, state));
    }
    else
    {
        state = armySkillTree.AxeT1 && currentPlayer->HasEnoughWeapons(UnitAxemanI::WEAPON_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
        m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Axeman MK2", []() {SelectionManager::GetInstance().CreateUnitPressed(UnitAxemanII::UNIT_TYPE); }, nullptr, state));
    }

    currentY += buttonHeight + buffer;


    state = armySkillTree.Canon && currentPlayer->HasEnoughWeapons(UnitCannon::WEAPON_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
    m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Cannon MK1", []() {SelectionManager::GetInstance().CreateUnitPressed(UnitAxemanI::UNIT_TYPE); }, nullptr, state));


    currentY += buttonHeight + buffer;


    state = currentPlayer->GetEmpireSkillTree().Settler && currentPlayer->HasEnoughFood(UnitSettler::FOOD_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
    m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Settler", []() {SelectionManager::GetInstance().CreateUnitPressed(UnitSettler::UNIT_TYPE); }, nullptr, state));


    //Second column
    currentX += buttonWidth + buffer;
    currentY = m_fontSize + buffer;

    if (armySkillTree.ArcherT3)
    {
        state = currentPlayer->HasEnoughWeapons(UnitArcherIII::WEAPON_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
        m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Archer MK3", []() {SelectionManager::GetInstance().CreateUnitPressed(UnitArcherIII::UNIT_TYPE); }, nullptr, state));
    }
    else if (armySkillTree.ArcherT2)
    {
        state = currentPlayer->HasEnoughWeapons(UnitArcherII::WEAPON_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
        m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Archer MK2", []() {SelectionManager::GetInstance().CreateUnitPressed(UnitArcherII::UNIT_TYPE); }, nullptr, state));
    }
    else
    {
        state = armySkillTree.ArcherT1 && currentPlayer->HasEnoughWeapons(UnitArcherI::WEAPON_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
        m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Archer MK1", []() {SelectionManager::GetInstance().CreateUnitPressed(UnitArcherI::UNIT_TYPE); }, nullptr, state));
    }

    currentY += buttonHeight + buffer;

    if (armySkillTree.MaceT2)
    {
        state = currentPlayer->HasEnoughWeapons(UnitMaceII::WEAPON_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
        m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Mace MK2", []() {SelectionManager::GetInstance().CreateUnitPressed(UnitMaceII::UNIT_TYPE); }, nullptr, state));
    }
    else
    {
        state = armySkillTree.MaceT1 && currentPlayer->HasEnoughWeapons(UnitMaceI::WEAPON_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
        m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Mace MK1", []() {SelectionManager::GetInstance().CreateUnitPressed(UnitMaceI::UNIT_TYPE); }, nullptr, state));
    }

    currentY += buttonHeight + buffer;

    state = armySkillTree.Shield && currentPlayer->HasEnoughWeapons(UnitShield::WEAPON_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
    m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Shield MK1", []() {SelectionManager::GetInstance().CreateUnitPressed(UnitShield::UNIT_TYPE); }, nullptr, state));

    currentY += buttonHeight + buffer;  
    currentY += buttonHeight + buffer;

    state = ButtonState::Unpressed;
    m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Cancel", []() {}, nullptr, state));
}


SpawnUnitPopUp::~SpawnUnitPopUp()
{
}

bool SpawnUnitPopUp::handleEvent(SDL_Event & e)
{
    for (ButtonText button : m_allButtons)
    {
        if (button.IsUnpressed() && button.IsInside(e.button.x, e.button.y))
        {
            button.DoAction();
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

    for (ButtonText button : m_allButtons)
    {
        //the button
        Texture* buttonTexture = button.GetButtonTexture(m_rend);
        int buttonX = button.GetLeftX();
        int buttonY = button.GetTopY();

        //this will stretch the texture to the following width/height
        int buttonWidth = button.GetWidth();
        int buttonHeight = button.GetHeight();
        SDL_Rect buttonRect = { buttonX, buttonY, buttonWidth, buttonHeight };
        SDL_RenderCopy(m_rend, buttonTexture->GetTexture(), NULL, &buttonRect);

        //the text on the button
        Texture * textTexture = button.GetTextTexture(m_rend);
        int textH = textTexture->GetHeight();
        int textW = textTexture->GetWidth();
        int horizontalOffset = (buttonWidth - textW) / 2;
        int verticalOffset = (buttonHeight - textH) / 2;
        SDL_Rect textRect = { buttonX + horizontalOffset, buttonY + verticalOffset, textW, textH };
        SDL_RenderCopy(m_rend, textTexture->GetTexture(), NULL, &textRect);
    }

    SDL_RenderPresent(m_rend);
}
