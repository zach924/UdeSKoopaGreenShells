#include <iostream>
#include "SkillTreePopUp.h"
#include "ButtonText.h"
#include "GameSession.h"
#include "Player.h"


SkillTreePopUp::SkillTreePopUp(const char * windowName, int width, int height)
    :PopUpWindow(windowName, width, height),
    m_closeButton(new ButtonText(m_width - 150, 5, 100, 40, "Close", []() {})),
    m_colomnWidth((width - COST_WIDTH) / 8), // 3 for army + 3 for empire + 2 for utility
    m_rowHeight((height - HEADER_HEIGHT) / 8) // 8 tiers
{
    m_scienceTexture = new Texture();
    m_scienceTexture->LoadFromFile("..\\Sprite\\Resources\\64x64\\science.bmp", m_rend);

    m_heightSpacer = (m_rowHeight - BUTTON_HEIGHT) / 2;
    m_widthSpace = (m_colomnWidth - BUTTON_WIDTH) / 2;

    std::shared_ptr<Player> currentPlayer{ GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID()) };

    //Army Tree
    auto currentArmyTree = currentPlayer->GetArmySkillTree();
    auto canResearchArmyTree = currentArmyTree.GetReadyForResearch();
    m_Buttons.emplace(Skills::RangerT1, CreateButton(1, 0, "Ranger MK1", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::RangerT1); }, currentArmyTree.RangerT1 ? ButtonState::Pressed : canResearchArmyTree.RangerT1 ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::Militia, CreateButton(1, 1, "Militia", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::Militia); }, currentArmyTree.Militia ? ButtonState::Pressed : canResearchArmyTree.Militia ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::SwordT2, CreateButton(0, 2, "Sword MK2", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::SwordT2); }, currentArmyTree.SwordT2 ? ButtonState::Pressed : canResearchArmyTree.SwordT2 ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::AxeT1, CreateButton(2, 2, "Axe MK1", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::AxeT1); }, currentArmyTree.AxeT1 ? ButtonState::Pressed : canResearchArmyTree.AxeT1 ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::SwordT3, CreateButton(0, 3, "Sword MK3", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::SwordT3); }, currentArmyTree.SwordT3 ? ButtonState::Pressed : canResearchArmyTree.SwordT3 ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::RangerT2, CreateButton(1, 3, "Ranger MK2", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::RangerT2); }, currentArmyTree.RangerT2 ? ButtonState::Pressed : canResearchArmyTree.RangerT2 ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::AxeT2, CreateButton(2, 3, "Axe MK2", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::AxeT2); }, currentArmyTree.AxeT2 ? ButtonState::Pressed : canResearchArmyTree.AxeT2 ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::MaceT1, CreateButton(1, 4, "Mace MK1", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::MaceT1); }, currentArmyTree.MaceT1 ? ButtonState::Pressed : canResearchArmyTree.MaceT1 ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::RangerT3, CreateButton(1, 5, "Ranger MK3", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::RangerT3); }, currentArmyTree.RangerT3 ? ButtonState::Pressed : canResearchArmyTree.RangerT3 ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::MaceT2, CreateButton(2, 5, "Mace MK2", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::MaceT2); }, currentArmyTree.MaceT2 ? ButtonState::Pressed : canResearchArmyTree.MaceT2 ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::Fortress, CreateButton(0, 6, "Fortress", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::Fortress); }, currentArmyTree.Fortress ? ButtonState::Pressed : canResearchArmyTree.Fortress ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::Shield, CreateButton(1, 6, "Shield", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::Shield); }, currentArmyTree.Shield ? ButtonState::Pressed : canResearchArmyTree.Shield ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::Canon, CreateButton(1, 7, "Cannons", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::Canon); }, currentArmyTree.Canon ? ButtonState::Pressed : canResearchArmyTree.Canon ? ButtonState::Unpressed : ButtonState::Disabled));

    //Empire Tree
    auto currentEmpireTree = currentPlayer->GetEmpireSkillTree();
    auto canResearchEmpireTree = currentEmpireTree.GetReadyForResearch();
    m_Buttons.emplace(Skills::Settler, CreateButton(4,0, "Settler", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::Settler); }, currentEmpireTree.Settler ? ButtonState::Pressed : canResearchEmpireTree.Settler ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::Monastery, CreateButton(4,1, "Monastery", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::Monastery); }, currentEmpireTree.Monastery ? ButtonState::Pressed :   canResearchEmpireTree.Monastery ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::Farm, CreateButton(3,2, "Farm", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::Farm); }, currentEmpireTree.Farm ? ButtonState::Pressed :   canResearchEmpireTree.Farm ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::Fishery, CreateButton(4,2, "Fishery", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::Fishery); }, currentEmpireTree.Fishery ? ButtonState::Pressed :   canResearchEmpireTree.Fishery ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::Stable, CreateButton(5,2, "Stable", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::Stable); }, currentEmpireTree.Stable ? ButtonState::Pressed :   canResearchEmpireTree.Stable ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::Windmill, CreateButton(3,3, "Windmill", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::Windmill); }, currentEmpireTree.Windmill ? ButtonState::Pressed :   canResearchEmpireTree.Windmill ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::Cathedral, CreateButton(4,3, "Cathedral", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::Cathedral); }, currentEmpireTree.Cathedral ? ButtonState::Pressed :   canResearchEmpireTree.Cathedral ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::Fort, CreateButton(5,3, "Fort", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::Fort); }, currentEmpireTree.Fort ? ButtonState::Pressed :   canResearchEmpireTree.Fort ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::MilitaryTent, CreateButton(3,4, "Military Tent", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::MilitaryTent); }, currentEmpireTree.MilitaryTent ? ButtonState::Pressed :   canResearchEmpireTree.MilitaryTent ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::InnAndTavern, CreateButton(5,4, "Inns & Taverns", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::InnAndTavern); }, currentEmpireTree.InnAndTavern ? ButtonState::Pressed :   canResearchEmpireTree.InnAndTavern ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::Warehouse, CreateButton(4,5, "Warehouse", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::Warehouse); }, currentEmpireTree.Warehouse ? ButtonState::Pressed :   canResearchEmpireTree.Warehouse ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::RessourcesBonus, CreateButton(4,6, "Bonus Res.", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::RessourcesBonus); }, currentEmpireTree.RessourcesBonus ? ButtonState::Pressed :   canResearchEmpireTree.RessourcesBonus ? ButtonState::Unpressed : ButtonState::Disabled));

    //Utility Tree
    auto currentUtilityTree = currentPlayer->GetUtilitySkillTree();
    auto canResearchUtilityTree = currentUtilityTree.GetReadyForResearch();
    m_Buttons.emplace(Skills::Watchtower, CreateButton(7,0, "Watchtower", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::Watchtower); }, currentUtilityTree.Watchtower ? ButtonState::Pressed :   canResearchUtilityTree.Watchtower ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::ScienceUpgrade, CreateButton(7,1, "Science Bonus", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::ScienceUpgrade); }, currentUtilityTree.ScienceUpgrade ? ButtonState::Pressed :   canResearchUtilityTree.ScienceUpgrade ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::BorderGrowth, CreateButton(7,2, "Border Growth", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::BorderGrowth); }, currentUtilityTree.BorderGrowth ? ButtonState::Pressed :   canResearchUtilityTree.BorderGrowth ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::Embark, CreateButton(6,3, "Embark", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::Embark); }, currentUtilityTree.Embark ? ButtonState::Pressed :   canResearchUtilityTree.Embark ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::MovementUpgrade, CreateButton(7,3, "+1 ActionPoint", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::MovementUpgrade); }, currentUtilityTree.MovementUpgrade ? ButtonState::Pressed :   canResearchUtilityTree.MovementUpgrade ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::VisionUpgrade, CreateButton(6,4, "Vision Bonus", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::VisionUpgrade); }, currentUtilityTree.VisionUpgrade ? ButtonState::Pressed :   canResearchUtilityTree.VisionUpgrade ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::MountainWalking, CreateButton(7,4, "Mountain Walk", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::MountainWalking); }, currentUtilityTree.MountainWalking ? ButtonState::Pressed :   canResearchUtilityTree.MountainWalking ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::ArmorUpgrade, CreateButton(6,5, "Armor", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::ArmorUpgrade); }, currentUtilityTree.ArmorUpgrade ? ButtonState::Pressed :   canResearchUtilityTree.ArmorUpgrade ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::MountainConstruction, CreateButton(7,5, "Mountain Cons", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::MountainConstruction); }, currentUtilityTree.MountainConstruction ? ButtonState::Pressed :   canResearchUtilityTree.MountainConstruction ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::University, CreateButton(6,6, "University", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::University); }, currentUtilityTree.University ? ButtonState::Pressed :   canResearchUtilityTree.University ? ButtonState::Unpressed : ButtonState::Disabled));
    m_Buttons.emplace(Skills::NoFogOfWar, CreateButton(7,6, "No Fog of War", [currentPlayer]() { currentPlayer->UnlockSkill(GameSession::GetInstance().GetWorldState()->GetCurrentTurn(), Skills::NoFogOfWar); }, currentUtilityTree.NoFogOfWar ? ButtonState::Pressed :   canResearchUtilityTree.NoFogOfWar ? ButtonState::Unpressed : ButtonState::Disabled));
}

SkillTreePopUp::~SkillTreePopUp()
{
    delete m_scienceTexture;
    for (auto button : m_Buttons)
    {
        delete button.second;
    }
}

void SkillTreePopUp::ShowButton(ButtonText* button)
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

void SkillTreePopUp::DrawDependencies(int firstColumn, int firstRow, int secondColumn, int secondRow)
{
    //Draw multiple lines to make it thick
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (firstColumn * m_colomnWidth) + m_widthSpace + (BUTTON_WIDTH / 2) + 1, HEADER_HEIGHT + (firstRow * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (secondColumn * m_colomnWidth) + m_widthSpace + (BUTTON_WIDTH / 2) + 1, HEADER_HEIGHT + (secondRow * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (firstColumn * m_colomnWidth) + m_widthSpace + (BUTTON_WIDTH / 2), HEADER_HEIGHT + (firstRow * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (secondColumn * m_colomnWidth) + m_widthSpace + (BUTTON_WIDTH / 2), HEADER_HEIGHT + (secondRow * m_rowHeight) + m_heightSpacer);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (firstColumn * m_colomnWidth) + m_widthSpace + (BUTTON_WIDTH / 2) - 1, HEADER_HEIGHT + (firstRow * m_rowHeight) + m_heightSpacer + BUTTON_HEIGHT, COST_WIDTH + (secondColumn * m_colomnWidth) + m_widthSpace + (BUTTON_WIDTH / 2) - 1, HEADER_HEIGHT + (secondRow * m_rowHeight) + m_heightSpacer);
}

void SkillTreePopUp::DrawCostsStrings(int cost, int column)
{
    Texture tierCosts;
    tierCosts.CreateFromText(std::to_string(cost), m_font, m_rend);
    SDL_Rect tierCostsRect{ 15, HEADER_HEIGHT + (column * m_rowHeight) + m_heightSpacer, tierCosts.GetWidth(), tierCosts.GetHeight() };
    SDL_RenderCopy(m_rend, tierCosts.GetTexture(), NULL, &tierCostsRect);
}

ButtonText * SkillTreePopUp::CreateButton(int column, int row, std::string text, std::function<void()> function, ButtonState state)
{
    return new ButtonText(COST_WIDTH + (column * m_colomnWidth) + m_widthSpace, HEADER_HEIGHT + (row * m_rowHeight) + m_heightSpacer, BUTTON_WIDTH, BUTTON_HEIGHT, text, function, state);
}

void SkillTreePopUp::SetButtonState(Skills skill, ButtonText* button)
{
    std::unique_ptr<Player> currentPlayer{ GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID()) };

    //Army Tree
    auto currentArmyTree = currentPlayer->GetArmySkillTree();
    auto canResearchArmyTree = currentArmyTree.GetReadyForResearch();
    auto currentEmpireTree = currentPlayer->GetEmpireSkillTree();
    auto canResearchEmpireTree = currentEmpireTree.GetReadyForResearch();
    auto currentUtilityTree = currentPlayer->GetUtilitySkillTree();
    auto canResearchUtilityTree = currentUtilityTree.GetReadyForResearch();
    switch (skill)
    {
    case Militia:
        button->SetButtonState(currentArmyTree.Militia ? ButtonState::Pressed : canResearchArmyTree.Militia ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case RangerT1:
        button->SetButtonState(currentArmyTree.RangerT1 ? ButtonState::Pressed : canResearchArmyTree.RangerT1 ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case RangerT2:
        button->SetButtonState(currentArmyTree.RangerT2 ? ButtonState::Pressed : canResearchArmyTree.RangerT2 ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case RangerT3:
        button->SetButtonState(currentArmyTree.RangerT3 ? ButtonState::Pressed : canResearchArmyTree.RangerT3 ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case SwordT2:
        button->SetButtonState(currentArmyTree.SwordT2 ? ButtonState::Pressed : canResearchArmyTree.SwordT2 ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case SwordT3:
        button->SetButtonState(currentArmyTree.SwordT3 ? ButtonState::Pressed : canResearchArmyTree.SwordT3 ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case AxeT1:
        button->SetButtonState(currentArmyTree.AxeT1 ? ButtonState::Pressed : canResearchArmyTree.AxeT1 ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case AxeT2:
        button->SetButtonState(currentArmyTree.AxeT2 ? ButtonState::Pressed : canResearchArmyTree.AxeT2 ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case MaceT1:
        button->SetButtonState(currentArmyTree.MaceT1 ? ButtonState::Pressed : canResearchArmyTree.MaceT1 ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case MaceT2:
        button->SetButtonState(currentArmyTree.MaceT2 ? ButtonState::Pressed : canResearchArmyTree.MaceT2 ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case Fortress:
        button->SetButtonState(currentArmyTree.Fortress ? ButtonState::Pressed : canResearchArmyTree.Fortress ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case Shield:
        button->SetButtonState(currentArmyTree.Shield ? ButtonState::Pressed : canResearchArmyTree.Shield ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case Canon:
        button->SetButtonState(currentArmyTree.Canon ? ButtonState::Pressed : canResearchArmyTree.Canon ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case Settler:
        button->SetButtonState(currentEmpireTree.Settler ? ButtonState::Pressed : canResearchEmpireTree.Settler ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case Monastery:
        button->SetButtonState(currentEmpireTree.Monastery ? ButtonState::Pressed : canResearchEmpireTree.Monastery ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case Farm:
        button->SetButtonState(currentEmpireTree.Farm ? ButtonState::Pressed : canResearchEmpireTree.Farm ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case Windmill:
        button->SetButtonState(currentEmpireTree.Windmill ? ButtonState::Pressed : canResearchEmpireTree.Windmill ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case Fishery:
        button->SetButtonState(currentEmpireTree.Fishery ? ButtonState::Pressed : canResearchEmpireTree.Fishery ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case Stable:
        button->SetButtonState(currentEmpireTree.Stable ? ButtonState::Pressed : canResearchEmpireTree.Stable ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case Cathedral:
        button->SetButtonState(currentEmpireTree.Cathedral ? ButtonState::Pressed : canResearchEmpireTree.Cathedral ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case Fort:
        button->SetButtonState(currentEmpireTree.Fort ? ButtonState::Pressed : canResearchEmpireTree.Fort ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case MilitaryTent:
        button->SetButtonState(currentEmpireTree.MilitaryTent ? ButtonState::Pressed : canResearchEmpireTree.MilitaryTent ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case InnAndTavern:
        button->SetButtonState(currentEmpireTree.InnAndTavern ? ButtonState::Pressed : canResearchEmpireTree.InnAndTavern ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case Warehouse:
        button->SetButtonState(currentEmpireTree.Warehouse ? ButtonState::Pressed : canResearchEmpireTree.Warehouse ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case RessourcesBonus:
        button->SetButtonState(currentEmpireTree.RessourcesBonus ? ButtonState::Pressed : canResearchEmpireTree.RessourcesBonus ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case Watchtower:
        button->SetButtonState(currentUtilityTree.Watchtower ? ButtonState::Pressed : canResearchUtilityTree.Watchtower ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case ScienceUpgrade:
        button->SetButtonState(currentUtilityTree.ScienceUpgrade ? ButtonState::Pressed : canResearchUtilityTree.ScienceUpgrade ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case BorderGrowth:
        button->SetButtonState(currentUtilityTree.BorderGrowth ? ButtonState::Pressed : canResearchUtilityTree.BorderGrowth ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case MovementUpgrade:
        button->SetButtonState(currentUtilityTree.MovementUpgrade ? ButtonState::Pressed : canResearchUtilityTree.MovementUpgrade ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case Embark:
        button->SetButtonState(currentUtilityTree.Embark ? ButtonState::Pressed : canResearchUtilityTree.Embark ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case VisionUpgrade:
        button->SetButtonState(currentUtilityTree.VisionUpgrade ? ButtonState::Pressed : canResearchUtilityTree.VisionUpgrade ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case MountainWalking:
        button->SetButtonState(currentUtilityTree.MountainWalking ? ButtonState::Pressed : canResearchUtilityTree.MountainWalking ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case MountainConstruction:
        button->SetButtonState(currentUtilityTree.MountainConstruction ? ButtonState::Pressed : canResearchUtilityTree.MountainConstruction ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case ArmorUpgrade:
        button->SetButtonState(currentUtilityTree.ArmorUpgrade ? ButtonState::Pressed : canResearchUtilityTree.ArmorUpgrade ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case University:
        button->SetButtonState(currentUtilityTree.University ? ButtonState::Pressed : canResearchUtilityTree.University ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    case NoFogOfWar:
        button->SetButtonState(currentUtilityTree.NoFogOfWar ? ButtonState::Pressed : canResearchUtilityTree.NoFogOfWar ? ButtonState::Unpressed : ButtonState::Disabled);
        break;
    default:
        break;
    }
}

void SkillTreePopUp::ShowWindow(SDL_Renderer * rend)
{
    SDL_SetRenderDrawColor(m_rend, 0, 100, 200, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_rend);

    SDL_SetRenderDrawColor(m_rend, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    //Vertical lines
    SDL_RenderDrawLine(m_rend, COST_WIDTH, 50, COST_WIDTH, m_height);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (3 * m_colomnWidth), 50, COST_WIDTH + (3 * m_colomnWidth), m_height);
    SDL_RenderDrawLine(m_rend, COST_WIDTH + (6 * m_colomnWidth), 50, COST_WIDTH + (6 * m_colomnWidth), m_height);

    //Horizontal lines
    SDL_RenderDrawLine(m_rend, 0, 50, m_width, 50);
    SDL_RenderDrawLine(m_rend, 0, HEADER_HEIGHT, m_width, HEADER_HEIGHT);
    SDL_RenderDrawLine(m_rend, 0, HEADER_HEIGHT + (1 * m_rowHeight), m_width, HEADER_HEIGHT + (1 * m_rowHeight));
    SDL_RenderDrawLine(m_rend, 0, HEADER_HEIGHT + (2 * m_rowHeight), m_width, HEADER_HEIGHT + (2 * m_rowHeight));
    SDL_RenderDrawLine(m_rend, 0, HEADER_HEIGHT + (3 * m_rowHeight), m_width, HEADER_HEIGHT + (3 * m_rowHeight));
    SDL_RenderDrawLine(m_rend, 0, HEADER_HEIGHT + (4 * m_rowHeight), m_width, HEADER_HEIGHT + (4 * m_rowHeight));
    SDL_RenderDrawLine(m_rend, 0, HEADER_HEIGHT + (5 * m_rowHeight), m_width, HEADER_HEIGHT + (5 * m_rowHeight));
    SDL_RenderDrawLine(m_rend, 0, HEADER_HEIGHT + (6 * m_rowHeight), m_width, HEADER_HEIGHT + (6 * m_rowHeight));
    SDL_RenderDrawLine(m_rend, 0, HEADER_HEIGHT + (7 * m_rowHeight), m_width, HEADER_HEIGHT + (7 * m_rowHeight));

    //Headers
    {
        //Pop up title
        SDL_Texture* titleTexture = m_texts.at(0);
        SDL_Rect renderQuadText = { 25, 10, 200, m_fontSize };
        SDL_RenderCopy(m_rend, titleTexture, NULL, &renderQuadText);

        //Available science
        std::shared_ptr<Player> currentPlayer{ GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID()) };
        Texture amountScienceHeader;
        amountScienceHeader.CreateFromText("Available Science : " + std::to_string(currentPlayer->GetScience()), m_font, m_rend);
        SDL_Rect amountScienceRect{ 200, 10, amountScienceHeader.GetWidth(), amountScienceHeader.GetHeight() };
        SDL_RenderCopy(m_rend, amountScienceHeader.GetTexture(), NULL, &amountScienceRect);


        SDL_Rect renderQuadScience = { 205 + amountScienceHeader.GetWidth(), 10, 32, 32 };
        SDL_RenderCopy(m_rend, m_scienceTexture->GetTexture(), NULL, &renderQuadScience);

        //Table
        int headerHight = 60;
        Texture costHeader;
        costHeader.CreateFromText("Costs", m_font, m_rend);
        int costX = 5;
        SDL_Rect costHeaderRect{ costX, headerHight, costHeader.GetWidth(), costHeader.GetHeight() };
        SDL_RenderCopy(m_rend, costHeader.GetTexture(), NULL, &costHeaderRect);

        Texture armyHeader;
        armyHeader.CreateFromText("Army Tree", m_font, m_rend);
        int armyX = COST_WIDTH + (3 * m_colomnWidth / 2) - (armyHeader.GetWidth()/2);
        SDL_Rect armyHeaderRect{ armyX, headerHight, armyHeader.GetWidth(), armyHeader.GetHeight() };
        SDL_RenderCopy(m_rend, armyHeader.GetTexture(), NULL, &armyHeaderRect);

        Texture empireHeader;
        empireHeader.CreateFromText("Empire Tree", m_font, m_rend);
        int empireX = COST_WIDTH + 3 * m_colomnWidth + (3 * m_colomnWidth / 2) - (armyHeader.GetWidth() / 2);
        SDL_Rect empireHeaderRect{ empireX, headerHight, empireHeader.GetWidth(), empireHeader.GetHeight() };
        SDL_RenderCopy(m_rend, empireHeader.GetTexture(), NULL, &empireHeaderRect);

        Texture utilityHeader;
        utilityHeader.CreateFromText("Utility Tree", m_font, m_rend);
        int utilityX = COST_WIDTH + 6 * m_colomnWidth + (2 * m_colomnWidth / 2) - (armyHeader.GetWidth() / 2);
        SDL_Rect utilityHeaderRect{ utilityX, headerHight, utilityHeader.GetWidth(), utilityHeader.GetHeight() };
        SDL_RenderCopy(m_rend, utilityHeader.GetTexture(), NULL, &utilityHeaderRect);

        DrawCostsStrings(Player::SKILL_COST_TIER1, 0);
        DrawCostsStrings(Player::SKILL_COST_TIER2, 1);
        DrawCostsStrings(Player::SKILL_COST_TIER3, 2);
        DrawCostsStrings(Player::SKILL_COST_TIER4, 3);
        DrawCostsStrings(Player::SKILL_COST_TIER5, 4);
        DrawCostsStrings(Player::SKILL_COST_TIER6, 5);
        DrawCostsStrings(Player::SKILL_COST_TIER7, 6);
        DrawCostsStrings(Player::SKILL_COST_TIER8, 7);
    }

    SDL_SetRenderDrawColor(m_rend, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);

    //Army dependencies
    DrawDependencies(1,0,1,1);
    DrawDependencies(1,1,0,2);
    DrawDependencies(1,1,2,2);
    DrawDependencies(0,2,0,3);
    DrawDependencies(0,2,1,3);
    DrawDependencies(2,2,2,3);
    DrawDependencies(2,2,1,3);
    DrawDependencies(1,3,1,4);
    DrawDependencies(1,4,1,5);
    DrawDependencies(1,4,2,5);
    DrawDependencies(1,5,0,6);
    DrawDependencies(1,5,1,6);
    DrawDependencies(1,6,1,7);
    
    //Empire dependencies
    DrawDependencies(4,0,4,1);
    DrawDependencies(4,1,3,2);
    DrawDependencies(4,1,4,2);
    DrawDependencies(4,1,5,2);
    DrawDependencies(3,2,3,3);
    DrawDependencies(3,2,4,3);
    DrawDependencies(4,2,4,3);
    DrawDependencies(5,2,4,3);
    DrawDependencies(5,2,5,3);
    DrawDependencies(3,3,3,4);
    DrawDependencies(4,3,3,4);
    DrawDependencies(4,3,5,4);
    DrawDependencies(5,3,5,4);
    DrawDependencies(5,4,4,5);
    DrawDependencies(4,5,4,6);

    //Utility dependencies
    DrawDependencies(7,0,7,1);
    DrawDependencies(7,1,7,2);
    DrawDependencies(7,2,6,3);
    DrawDependencies(7,2,7,3);
    DrawDependencies(6,3,6,4);
    DrawDependencies(7,3,6,4);
    DrawDependencies(7,3,7,4);
    DrawDependencies(6,4,6,5);
    DrawDependencies(7,4,7,5);
    DrawDependencies(6,5,6,6);
    DrawDependencies(6,5,7,6);

    ShowButton(m_closeButton);
    for (auto button : m_Buttons)
    {
        SetButtonState(button.first, button.second);
        ShowButton(button.second);
    }

    SDL_RenderPresent(m_rend);
}

bool SkillTreePopUp::handleEvent(SDL_Event & e)
{
    if (m_closeButton->IsUnpressed() && m_closeButton->IsInside(e.button.x, e.button.y))
    {
        return true;
    }
    for (auto button : m_Buttons)
    {
        if (button.second->IsUnpressed() && button.second->IsInside(e.button.x, e.button.y))
        {
            button.second->DoAction();
        }
    }
    return false;
}
