#include "ConstructDistrictPopUp.h"
#include "DistrictCityCenter.h"

#include "DistrictHunter.h"
#include "DistrictFarm.h"
#include "DistrictWindMill.h"

#include "DistrictBlacksmith.h"
#include "DistrictStable.h"
#include "DistrictFort.h"

#include "DistrictMonastery.h"
#include "DistrictCathedral.h"
#include "DistrictSchool.h"
#include "DistrictFishery.h"

#include "DistrictInn.h"
#include "DistrictTavern.h"
#include "DistrictMilitaryTent.h"

#include "GameSession.h"
#include "Player.h"
#include "SelectionManager.h"


ConstructDistrictPopUp::ConstructDistrictPopUp(const char* windowName, int width, int height)
    : PopUpWindow(windowName, width, height)
    , m_allButtons()
{
    int buffer = 20;
    int currentX = 50;
    int currentY = m_fontSize + buffer;
    int buttonWidth = 200;
    int buttonHeight = 50;
    auto currentPlayer = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    EmpireSkillTree empSkillTree = currentPlayer->GetEmpireSkillTree();

    ButtonState state;
    if (empSkillTree.Windmill)
    {
        state = currentPlayer->HasEnoughFood(DistrictWindMill::FOOD_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
        m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Windmill", []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictWindMill::DISTRICT_TYPE); }, nullptr, state));
    }
    else if (empSkillTree.Farm)
    {
        state = currentPlayer->HasEnoughFood(DistrictFarm::FOOD_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
        m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Farm", []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictFarm::DISTRICT_TYPE); }, nullptr, state));
    }
    else
    {
        state = currentPlayer->HasEnoughFood(DistrictHunter::FOOD_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
        m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Hunter", []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictHunter::DISTRICT_TYPE); }, nullptr, state));
    }

    currentY += buttonHeight + buffer;

    state = currentPlayer->HasEnoughFood(DistrictFishery::FOOD_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
    m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Fishery", []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictFishery::DISTRICT_TYPE); }, nullptr, state));
    
    currentY += buttonHeight + buffer;

    if (empSkillTree.Fort)
    {
        state = currentPlayer->HasEnoughFood(DistrictFort::FOOD_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
        m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Fort", []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictFort::DISTRICT_TYPE); }, nullptr, state));
    }
    else if (empSkillTree.Stable)
    {
        state = currentPlayer->HasEnoughFood(DistrictStable::FOOD_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
        m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Stable", []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictStable::DISTRICT_TYPE); }, nullptr, state));
    }
    else
    {
        state = currentPlayer->HasEnoughFood(DistrictBlacksmith::FOOD_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
        m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Blacksmith", []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictBlacksmith::DISTRICT_TYPE); }, nullptr, state));
    }

    currentY += buttonHeight + buffer;

    if (empSkillTree.School)
    {
        state = currentPlayer->HasEnoughFood(DistrictSchool::FOOD_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
        m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "School", []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictSchool::DISTRICT_TYPE); }, nullptr, state));
    }
    else if (empSkillTree.Cathedral)
    {
        state = currentPlayer->HasEnoughFood(DistrictCathedral::FOOD_COST) ? ButtonState::Unpressed : ButtonState::Disabled;
        m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Cathedral", []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictCathedral::DISTRICT_TYPE); }, nullptr, state));
    }
    else
    {
        state = currentPlayer->HasEnoughFood(DistrictMonastery::FOOD_COST) && empSkillTree.Monastery ? ButtonState::Unpressed : ButtonState::Disabled;
        m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Monastery", []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictMonastery::DISTRICT_TYPE); }, nullptr, state));
    }
    

    currentY += buttonHeight + buffer;

    state = currentPlayer->HasEnoughFood(DistrictInn::FOOD_COST) && empSkillTree.InnAndTavern ? ButtonState::Unpressed : ButtonState::Disabled;
    m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Inn", []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictInn::DISTRICT_TYPE); }, nullptr, state));


    currentY += buttonHeight + buffer;
    
    state = currentPlayer->HasEnoughFood(DistrictTavern::FOOD_COST) && empSkillTree.InnAndTavern ? ButtonState::Unpressed : ButtonState::Disabled;
    m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Tavern", []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictTavern::DISTRICT_TYPE); }, nullptr, state));

    currentY += buttonHeight + buffer;
    currentX += buttonWidth + buffer;
    state = ButtonState::Unpressed;

    m_allButtons.emplace_back(ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Cancel", []() {}, nullptr, state));
}


ConstructDistrictPopUp::~ConstructDistrictPopUp()
{
}

bool ConstructDistrictPopUp::handleEvent(SDL_Event & e)
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

void ConstructDistrictPopUp::ShowWindow(SDL_Renderer * rend)
{
    SDL_RenderClear(m_rend);
    int horizontalPos = 25;
    int verticalPos = 0;
    int height = m_fontSize;

    Texture menuHeader;
    menuHeader.CreateFromText("Construct District", m_font, m_rend);
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
