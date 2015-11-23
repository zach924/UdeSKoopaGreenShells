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

#include "DistrictInn.h"
#include "DistrictTavern.h"
#include "DistrictMilitaryTent.h"

#include "GameSession.h"
#include "Player.h"
#include "SelectionManager.h"

ConstructDistrictPopUp::ConstructDistrictPopUp(const char* windowName, int width, int height)
    : PopUpWindow(windowName, width, height)
{
    int buffer = 20;
    int currentX = 50;
    int currentY = m_fontSize + buffer;
    int buttonWidth = 200;
    int buttonHeight = 50;
    int index = 0;
    auto currentPlayer = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    EmpireSkillTree empSkillTree = currentPlayer->GetEmpireSkillTree();

    ButtonState state;
    std::function<void()> spawnDistrict;
    m_allButtons[index];

    if (empSkillTree.Windmill)
    {
        state = currentPlayer->HasRessourcesForDistrict(DistrictWindMill::DISTRICT_TYPE) ? ButtonState::Unpressed : ButtonState::Disabled;
        spawnDistrict = []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictWindMill::DISTRICT_TYPE); };
        m_allButtons[index] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Windmill", spawnDistrict, nullptr, state);
    }
    else if (empSkillTree.Farm)
    {
        state = currentPlayer->HasRessourcesForDistrict(DistrictFarm::DISTRICT_TYPE) ? ButtonState::Unpressed : ButtonState::Disabled;
        spawnDistrict = []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictFarm::DISTRICT_TYPE); };
        m_allButtons[index] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Farm", spawnDistrict, nullptr, state);
    }
    else
    {
        state = currentPlayer->HasRessourcesForDistrict(DistrictHunter::DISTRICT_TYPE) ? ButtonState::Unpressed : ButtonState::Disabled;
        spawnDistrict = []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictHunter::DISTRICT_TYPE); };
        m_allButtons[index] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Hunter", spawnDistrict, nullptr, state);
    }

    currentY += buttonHeight + buffer;
    ++index;
    if (empSkillTree.Fort)
    {
        state = currentPlayer->HasRessourcesForDistrict(DistrictFort::DISTRICT_TYPE) ? ButtonState::Unpressed : ButtonState::Disabled;
        spawnDistrict = []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictFort::DISTRICT_TYPE); };
        m_allButtons[index] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Fort", spawnDistrict, nullptr, state);
    }
    else if (empSkillTree.Stable)
    {
        state = currentPlayer->HasRessourcesForDistrict(DistrictStable::DISTRICT_TYPE) ? ButtonState::Unpressed : ButtonState::Disabled;
        spawnDistrict = []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictStable::DISTRICT_TYPE); };
        m_allButtons[index] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Stable", spawnDistrict, nullptr, state);
    }
    else
    {
        state = currentPlayer->HasRessourcesForDistrict(DistrictBlacksmith::DISTRICT_TYPE) ? ButtonState::Unpressed : ButtonState::Disabled;
        spawnDistrict = []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictBlacksmith::DISTRICT_TYPE); };
        m_allButtons[index] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Blacksmith", spawnDistrict, nullptr, state);
    }

    currentY += buttonHeight + buffer;
    ++index;
    if (empSkillTree.School)
    {
        state = currentPlayer->HasRessourcesForDistrict(DistrictSchool::DISTRICT_TYPE) ? ButtonState::Unpressed : ButtonState::Disabled;
        spawnDistrict = []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictSchool::DISTRICT_TYPE); };
        m_allButtons[index] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "School", spawnDistrict, nullptr, state);
    }
    else if (empSkillTree.Cathedral)
    {
        state = currentPlayer->HasRessourcesForDistrict(DistrictCathedral::DISTRICT_TYPE) ? ButtonState::Unpressed : ButtonState::Disabled;
        spawnDistrict = []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictCathedral::DISTRICT_TYPE); };
        m_allButtons[index] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Cathedral", spawnDistrict, nullptr, state);
    }
    else
    {
        state = currentPlayer->HasRessourcesForDistrict(DistrictMonastery::DISTRICT_TYPE) && empSkillTree.Monastery ? ButtonState::Unpressed : ButtonState::Disabled;
        spawnDistrict = []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictMonastery::DISTRICT_TYPE); };
        m_allButtons[index] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Monastery", spawnDistrict, nullptr, state);
    }
    

    currentY += buttonHeight + buffer;
    ++index;
    state = currentPlayer->HasRessourcesForDistrict(DistrictInn::DISTRICT_TYPE) && empSkillTree.InnAndTavern ? ButtonState::Unpressed : ButtonState::Disabled;
    spawnDistrict = []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictInn::DISTRICT_TYPE); };
    m_allButtons[index] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Inn", spawnDistrict, nullptr, state);


    currentY += buttonHeight + buffer;
    ++index;
    state = currentPlayer->HasRessourcesForDistrict(DistrictTavern::DISTRICT_TYPE) && empSkillTree.InnAndTavern ? ButtonState::Unpressed : ButtonState::Disabled;
    spawnDistrict = []() {SelectionManager::GetInstance().CreateDistrictPressed(DistrictTavern::DISTRICT_TYPE); };
    m_allButtons[index] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Tavern", spawnDistrict, nullptr, state);

    currentY += buttonHeight + buffer;
    currentX += buttonWidth + buffer;
    ++index;
    spawnDistrict = []() {};
    m_allButtons[index] = new ButtonText(currentX, currentY, buttonWidth, buttonHeight, "Cancel", spawnDistrict, nullptr, ButtonState::Unpressed);
}


ConstructDistrictPopUp::~ConstructDistrictPopUp()
{
}

bool ConstructDistrictPopUp::handleEvent(SDL_Event & e)
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
