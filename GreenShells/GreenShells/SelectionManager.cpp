#include <iostream>

#include "SelectionManager.h"
#include "MapRemote.h"
#include "Position.h"
#include "ServerSession.h"
#include "Tile.h"
#include "GameSession.h"
#include "ClickManager.h"
#include "Player.h"

#include "UnitEmpty.h"

#include "DistrictEmpty.h"
#include "DistrictCityCenter.h"

#include "DistrictHunter.h"
#include "DistrictFarm.h"
#include "DistrictWindMill.h"
#include "DistrictWarehouse.h"

#include "DistrictBlacksmith.h"
#include "DistrictStable.h"
#include "DistrictFort.h"
#include "DistrictFortress.h"

#include "DistrictMonastery.h"
#include "DistrictCathedral.h"
#include "DistrictSchool.h"
#include "DistrictUniversity.h"

#include "DistrictWatchTower.h"
#include "DistrictInn.h"
#include "DistrictTavern.h"
#include "DistrictMilitaryTent.h"

#include "ButtonUnitAttack.h"
#include "ButtonUnitCancel.h"
#include "ButtonUnitHeal.h"
#include "ButtonUnitMove.h"
#include "ButtonUnitSell.h"
#include "ButtonUnitUpgrade.h"

#include "ButtonDistrictCancel.h"
#include "ButtonDistrictRepair.h"
#include "ButtonDistrictSell.h"
#include "ButtonDistrictUpgrade.h"

#include "ButtonNextTurn.h"
#include "ButtonConstructDistrict.h"
#include "ButtonDiplomacy.h"
#include "ButtonSpawnUnit.h"
#include "ButtonGeneralCancel.h"
#include "ButtonSkillTree.h"
#include "ButtonMenu.h"

#include "YesNoPopUp.h"
#include "GameWindow.h"

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

SelectionManager::SelectionManager()
    :m_state(m_idle)
    , m_unitEmpty(new UnitEmpty(-1))
    , m_districtEmpty(new DistrictEmpty(-1))
    , m_actionPossibleTiles()
    , m_districtTypeToConstruct(-1)
    , m_unitTypeToCreate(-1)
    , m_selectedPosition(-1, -1)
{
}

SelectionManager::~SelectionManager()
{
    delete m_unitEmpty;
    delete m_districtEmpty;
}

UnitBase* SelectionManager::GetSelectedUnit()
{
    if (m_selectedPosition == Position(-1, -1))
    {
        return m_unitEmpty;
    }
    else
    {
        unique_ptr<Map> map{ GameSession::GetInstance().GetWorldState()->GetMapCopy() };
        TileBase* tile = map->GetTile(m_selectedPosition);

        UnitBase* unitSelected = nullptr;
        if (tile->IsSeen(GameSession::GetInstance().GetCurrentPlayerID()))
        {
            unitSelected = tile->GetUnit();
        }

        return unitSelected ? unitSelected->Clone() : m_unitEmpty;
    }
}

DistrictBase* SelectionManager::GetSelectedDistrict()
{
    if (m_selectedPosition == Position(-1, -1))
    {
        return m_districtEmpty;
    }
    else
    {
        unique_ptr<Map> map{ GameSession::GetInstance().GetWorldState()->GetMapCopy() };
        TileBase* tile = map->GetTile(m_selectedPosition);

        DistrictBase* districtSelected = nullptr;

        if (tile->IsDiscovered(GameSession::GetInstance().GetCurrentPlayerID()))
        {
            districtSelected = tile->GetDistrict();
        }

        return districtSelected ? districtSelected->Clone() : m_districtEmpty;
    }
}

std::vector<Position> SelectionManager::GetOverlayTiles()
{
    return m_actionPossibleTiles;
}

void SelectionManager::Cancel()
{
    m_state = m_idle;
    m_actionPossibleTiles.clear();
    UpdateButtonState();
}

void SelectionManager::UpdateButtonState()
{
    UnitBase* selectedUnit{ GetSelectedUnit() };
    DistrictBase* selectedDistrict{ GetSelectedDistrict() };

    std::vector<Button*> buttons = ClickManager::GetInstance().GetButtons();

    for (auto btn : buttons)
    {
        if (dynamic_cast<ButtonUnitAttack*>(btn) != nullptr)
        {
            if (selectedUnit->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID()
                && selectedUnit->GetActionPointsRemaining() > 0
                && m_state == m_idle)
            {
                btn->SetButtonState(ButtonState::Unpressed);
            }
            else if (selectedUnit->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID()
                && selectedUnit->GetActionPointsRemaining() > 0
                && m_state == m_unitAttacking)
            {
                btn->SetButtonState(ButtonState::Pressed);
            }
            else
            {
                btn->SetButtonState(ButtonState::Disabled);
            }
        }
        else if (dynamic_cast<ButtonUnitMove*>(btn) != nullptr)
        {
            if (selectedUnit->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID()
                && selectedUnit->GetActionPointsRemaining() > 0
                && m_state == m_idle)
            {
                btn->SetButtonState(ButtonState::Unpressed);
            }
            else if (selectedUnit->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID()
                && selectedUnit->GetActionPointsRemaining() > 0
                && m_state == m_unitMoving)
            {
                btn->SetButtonState(ButtonState::Pressed);
            }
            else
            {
                btn->SetButtonState(ButtonState::Disabled);
            }
        }
        else if (dynamic_cast<ButtonUnitCancel*>(btn) != nullptr)
        {
            if (selectedUnit->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID()
                && selectedUnit->GetActionPointsRemaining() > 0
                && m_state == m_unitAttacking || m_state == m_unitMoving)
            {
                btn->SetButtonState(ButtonState::Unpressed);
            }
            else
            {
                btn->SetButtonState(ButtonState::Disabled);
            }
        }
        else if (dynamic_cast<ButtonUnitHeal*>(btn) != nullptr)
        {
            if (selectedUnit->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID()
                && selectedUnit->GetActionPointsRemaining() > 0
                && m_state == m_idle
                && selectedUnit->GetHealth() < selectedUnit->GetMaxHealth())
            {
                btn->SetButtonState(ButtonState::Unpressed);
            }
            else
            {
                btn->SetButtonState(ButtonState::Disabled);
            }
        }
        else if (dynamic_cast<ButtonUnitSell*>(btn) != nullptr)
        {
            if (selectedUnit->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID()
                && m_state == m_idle
                && selectedUnit->GetActionPointsRemaining() > 0)
            {
                btn->SetButtonState(ButtonState::Unpressed);
            }
            else
            {
                btn->SetButtonState(ButtonState::Disabled);
            }
        }
        else if (dynamic_cast<ButtonUnitUpgrade*>(btn) != nullptr)
        {
            if (selectedUnit->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID()
                && selectedUnit->GetActionPointsRemaining() > 0
                && m_state == m_idle
                && selectedUnit->CanUpgrade())
            {
                btn->SetButtonState(ButtonState::Unpressed);
            }
            else
            {
                btn->SetButtonState(ButtonState::Disabled);
            }
        }
        else if (dynamic_cast<ButtonDistrictRepair*>(btn) != nullptr)
        {
            if (selectedDistrict->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID()
                && selectedDistrict->GetActionPointsRemaining() > 0
                && selectedDistrict->GetHealth() < selectedDistrict->GetMaxHealth())
            {
                btn->SetButtonState(ButtonState::Unpressed);
            }
            else
            {
                btn->SetButtonState(ButtonState::Disabled);
            }
        }
        else if (dynamic_cast<ButtonDistrictSell*>(btn) != nullptr)
        {
            if (selectedDistrict->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID()
                && selectedDistrict->GetActionPointsRemaining() > 0)
            {
                btn->SetButtonState(ButtonState::Unpressed);
            }
            else
            {
                btn->SetButtonState(ButtonState::Disabled);
            }
        }
        else if (dynamic_cast<ButtonDistrictUpgrade*>(btn) != nullptr)
        {
            if (selectedDistrict->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID()
                && selectedDistrict->GetActionPointsRemaining() > 0
                && selectedDistrict->CanUpgrade())
            {
                btn->SetButtonState(ButtonState::Unpressed);
            }
            else
            {
                btn->SetButtonState(ButtonState::Disabled);
            }
        }
        else if (dynamic_cast<ButtonDistrictCancel*>(btn) != nullptr)
        {
            btn->SetButtonState(ButtonState::Disabled);
        }
        else if (dynamic_cast<ButtonDiplomacy*>(btn) != nullptr)
        {
            btn->SetButtonState(ButtonState::Unpressed);
        }
        else if (dynamic_cast<ButtonSkillTree*>(btn) != nullptr)
        {
            btn->SetButtonState(ButtonState::Unpressed);
        }
        else if (dynamic_cast<ButtonConstructDistrict*>(btn) != nullptr)
        {
            if (dynamic_cast<DistrictCityCenter*>(selectedDistrict) != nullptr
                && selectedDistrict->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID())
            {
                btn->SetButtonState(ButtonState::Unpressed);
            }
            else
            {
                btn->SetButtonState(ButtonState::Disabled);
            }
        }
        else if (dynamic_cast<ButtonSpawnUnit*>(btn) != nullptr)
        {
            if (dynamic_cast<DistrictCityCenter*>(selectedDistrict) != nullptr
                && selectedDistrict->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID()
                && selectedUnit == m_unitEmpty)
            {
                btn->SetButtonState(ButtonState::Unpressed);
            }
            else
            {
                btn->SetButtonState(ButtonState::Disabled);
            }
        }
        else if (dynamic_cast<ButtonGeneralCancel*>(btn) != nullptr)
        {
            if (m_state == m_createDistrict)
            {
                btn->SetButtonState(ButtonState::Unpressed);
            }
            else
            {
                btn->SetButtonState(ButtonState::Disabled);
            }
        }
        else if (dynamic_cast<ButtonNextTurn*>(btn) != nullptr)
        {
            if (GameSession::GetInstance().GetCurrentPlayerCopy()->IsPlayerReadyForNextTurn())
            {
                btn->SetButtonState(ButtonState::Disabled);
            }
            else
            {
                btn->SetButtonState(ButtonState::Unpressed);
            }
        }
        else if (dynamic_cast<ButtonMenu*>(btn) != nullptr)
        {
            btn->SetButtonState(ButtonState::Unpressed);
        }
        else
        {
            assert(false && "You must implement this for your button!");
        }
    }

    if (dynamic_cast<DistrictEmpty*>(selectedDistrict) == nullptr)
    {
        delete selectedDistrict;
    }
    if (dynamic_cast<UnitEmpty*>(selectedUnit) == nullptr)
    {
        delete selectedUnit;
    }

}


void SelectionManager::Idle(Position pos)
{
    m_selectedPosition = pos;
    UpdateButtonState();
}

void SelectionManager::Attack(Position pos)
{
    unique_ptr<Map> map{ GameSession::GetInstance().GetWorldState()->GetMapCopy() };
    UnitBase* unit = map->GetTile(pos)->GetUnit();
    int actorOwner;
    if (unit != nullptr)
    {
        actorOwner = unit->GetOwnerID();
    }
    else
    {
        DistrictBase* district = map->GetTile(pos)->GetDistrict();
        assert(district != nullptr && "We should never get this far is there are no district or unit in the tile");
        actorOwner = district->GetOwnerID();
    }

    int currentPlayerId = GameSession::GetInstance().GetCurrentPlayerID();
    int currentTurn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();

    if (actorOwner >= 0
        && actorOwner != currentPlayerId
        && GameSession::GetInstance().GetCurrentPlayerCopy()->GetDiplomaticRelations()[actorOwner].GetRelationStatus() == RelationStatus::War)
    {
        GameSession::GetInstance().GetWorldState()->Attack(GameSession::GetInstance().GetCurrentPlayerID(), m_selectedPosition, pos);
    }
    else
    {
        std::string msg = "Do you want to declare war on " + GameSession::GetInstance().GetWorldState()->GetPlayer(actorOwner)->GetPlayerName() + " ?";
        auto window = new YesNoPopUp(msg.c_str(), 300, 150, [actorOwner, currentTurn]() {GameSession::GetInstance().GetCurrentPlayerCopy()->GoToWar(actorOwner, currentTurn); });
        GameWindow::GetInstance().AddPopUpWindow(window);
    }
    EndAction();
}

void SelectionManager::CreateDistrict(Position pos)
{
    GameSession::GetInstance().GetWorldState()->CreateDistrict(m_districtTypeToConstruct, pos, GameSession::GetInstance().GetCurrentPlayerID());
    EndAction();
}

void SelectionManager::CreateUnit(Position pos)
{
    GameSession::GetInstance().GetWorldState()->CreateUnit(m_unitTypeToCreate, pos, GameSession::GetInstance().GetCurrentPlayerID());
    EndAction();
}

void SelectionManager::Move(Position pos)
{
    unique_ptr<Map> map{ GameSession::GetInstance().GetWorldState()->GetMapCopy() };
    int tileOwner = map->GetTile(pos)->GetPlayerOwnerId();
    int currentPlayerId = GameSession::GetInstance().GetCurrentPlayerID();
    int currentTurn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();

    if (tileOwner < 0
        || tileOwner == currentPlayerId
        || GameSession::GetInstance().GetCurrentPlayerCopy()->GetDiplomaticRelations()[tileOwner].GetRelationStatus() == RelationStatus::War)
    {
        GameSession::GetInstance().GetWorldState()->MoveUnit(currentPlayerId, m_selectedPosition, pos);
    }
    else
    {
        std::string msg = "Do you want to declare war on " + GameSession::GetInstance().GetWorldState()->GetPlayer(tileOwner)->GetPlayerName() + " ?";
        auto window = new YesNoPopUp(msg.c_str(), 300, 150, [tileOwner, currentTurn]() {GameSession::GetInstance().GetCurrentPlayerCopy()->GoToWar(tileOwner, currentTurn); });
        GameWindow::GetInstance().AddPopUpWindow(window);
    }
    EndAction();
}

void SelectionManager::EndAction()
{
    m_state = m_idle;
    m_actionPossibleTiles.clear();
    m_selectedPosition.Column = -1;
    m_selectedPosition.Row = -1;
    UpdateButtonState();
}

void SelectionManager::HandleSelection(Position pos)
{
    auto map = GameSession::GetInstance().GetWorldState()->GetMapCopy();
    TileBase* tile = map->GetTile(pos);

    // If the tile selected is not in our range of action possible, we remove the selected actor and do like no action was waiting
    if (m_state != m_idle && std::find(m_actionPossibleTiles.begin(), m_actionPossibleTiles.end(), tile->GetPosition()) == m_actionPossibleTiles.end())
    {
        Cancel();
    }

    switch (m_state)
    {
    case m_idle:
        std::cout << "Selecting Unit and district at pos " << pos.Column << " " << pos.Row << std::endl;
        Idle(pos);
        break;
    case  m_createDistrict:
        std::cout << "Create a district" << std::endl;
        CreateDistrict(pos);
        break;
    case m_unitMoving:
        std::cout << "Moving Unit" << std::endl;
        Move(pos);
        break;
    case m_unitAttacking:
        std::cout << "Attacking Unit" << std::endl;
        Attack(pos);

        break;
    default:
        break;
    }

    UpdateButtonState();
}

void SelectionManager::HandleRightClickPressed(Position pos)
{
    //we have nothing selected, we do nothing
    if (m_selectedPosition == Position(-1, -1))
    {
        Cancel();
        return;
    }

    auto map = GameSession::GetInstance().GetWorldState()->GetMapCopy();
    TileBase* selectedTile = map->GetTile(m_selectedPosition);

    //we have no unit selected, we do nothing
    if (selectedTile->GetUnit() == nullptr)
    {
        Cancel();
        return;
    }

    auto allPositionsNear = map->GetArea(m_selectedPosition, selectedTile->GetUnit()->GetActionPointsRemaining(), GameSession::GetInstance().GetCurrentPlayerCopy()->GetMoveRestriction());
    m_actionPossibleTiles.clear();

    for (Position currentPos : allPositionsNear)
    {
        TileBase* currentTile = map->GetTile(currentPos);

        if (currentPos != m_selectedPosition &&
            currentTile->GetUnit() == nullptr &&
            (currentTile->GetDistrict() == nullptr || //no district
                (currentTile->GetDistrict()->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID() && //a district that belongs to the current player and
                    currentTile->GetUnit() == nullptr)))//is free of units
        {
            m_actionPossibleTiles.push_back(currentPos);
        }
    }
}

void SelectionManager::HandleRightClickUnpressed(Position pos)
{
    //we have nothing selected, we do nothing
    if (m_selectedPosition == Position(-1, -1))
    {
        Cancel();
        return;
    }

    auto map = GameSession::GetInstance().GetWorldState()->GetMapCopy();
    TileBase* selectedTile = map->GetTile(m_selectedPosition);

    //we have no unit selected, we do nothing
    if (selectedTile->GetUnit() == nullptr)
    {
        Cancel();
        return;
    }

    TileBase* tile = map->GetTile(pos);

    //if we are in the middle of an action OR if the tile selected is not in our range of action possible, we remove the selected actor and do like no action was waiting
    if (m_state != m_idle || std::find(m_actionPossibleTiles.begin(), m_actionPossibleTiles.end(), tile->GetPosition()) == m_actionPossibleTiles.end())
    {
        Cancel();
        return;
    }

    std::cout << "Right clicking somewhere";
    if (pos != m_selectedPosition &&
        (tile->IsFree() ||
            (tile->GetDistrict() != nullptr &&
                tile->GetDistrict()->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID())))
    {
        Move(pos);
    }


    UpdateButtonState();
}

void SelectionManager::CreateDistrictPressed(int districtType)
{
    if (IsADistrictSelected())
    {
        std::cout << "Selection Manager create district State" << std::endl;

        m_state = m_createDistrict;
        m_districtTypeToConstruct = districtType;

        unique_ptr<Map> map{ GameSession::GetInstance().GetWorldState()->GetMapCopy() };
        std::set<Position> allPositionNear = map->GetArea(m_selectedPosition, DistrictCityCenter::T4_BORDER_SIZE, GameSession::GetInstance().GetCurrentPlayerCopy()->GetUtilitySkillTree().MountainConstruction ? ALLOW__GROUND_MOUNTAIN : NO_FILTER);

        m_actionPossibleTiles.clear();
        for (Position pos : allPositionNear)
        {
            if (map->GetTile(pos)->GetPlayerOwnerId() == GameSession::GetInstance().GetCurrentPlayerID() && map->GetTile(pos)->GetDistrict() == nullptr)
            {
                m_actionPossibleTiles.push_back(pos);
            }
        }
    }
}

void SelectionManager::CreateUnitPressed(int unitType)
{
    if (IsADistrictSelected())
    {
        m_unitTypeToCreate = unitType;
        CreateUnit(m_selectedPosition);
    }
}

void SelectionManager::UnitAttackPressed()
{
    if (IsAUnitSelected())
    {
        std::cout << "Selection Manager attack State" << std::endl;

        m_state = m_unitAttacking;

        unique_ptr<Map> map{ GameSession::GetInstance().GetWorldState()->GetMapCopy() };
        unique_ptr<UnitBase> unit{ GetSelectedUnit() };

        std::set<Position> allPositionNear = map->GetArea(m_selectedPosition, unit->GetAttackRange(), NO_FILTER);
        m_actionPossibleTiles.clear();
        for (Position pos : allPositionNear)
        {
            if ((map->GetTile(pos)->GetDistrict() != nullptr && map->GetTile(pos)->GetDistrict()->GetOwnerID() != GameSession::GetInstance().GetCurrentPlayerID()) ||
                (map->GetTile(pos)->GetUnit() != nullptr && map->GetTile(pos)->GetUnit()->GetOwnerID() != GameSession::GetInstance().GetCurrentPlayerID()))
            {
                m_actionPossibleTiles.push_back(pos);
            }
        }

        UpdateButtonState();
    }
}

void SelectionManager::UnitMovePressed()
{
    if (IsAUnitSelected())
    {
        std::cout << "Selection Manager Move State" << std::endl;

        m_state = m_unitMoving;

        unique_ptr<Map> map{ GameSession::GetInstance().GetWorldState()->GetMapCopy() };
        Position unitPosition = m_selectedPosition;

        unique_ptr<UnitBase> unit{ GetSelectedUnit() };
        std::set<Position> allPositionNear = map->GetArea(unitPosition, unit->GetActionPointsRemaining(), GameSession::GetInstance().GetCurrentPlayerCopy()->GetMoveRestriction());
        m_actionPossibleTiles.clear();
        for (Position pos : allPositionNear)
        {
            if (pos != unitPosition && // Position is not the same
                map->GetTile(pos)->GetUnit() == nullptr && // No unit on the tile already
                (map->GetTile(pos)->GetDistrict() == nullptr || // No district on the tile
                    (map->GetTile(pos)->GetDistrict()->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID()))) // If there is a district on the tile, is it our?
            {
                m_actionPossibleTiles.push_back(pos);
            }
        }

        UpdateButtonState();
    }
}

bool SelectionManager::IsAUnitSelected()
{
    UnitBase* unit = GetSelectedUnit();
    bool isUnitSelected = false;
    if (unit != m_unitEmpty)
    {
        delete unit;
        isUnitSelected = true;
    }
    return isUnitSelected;
}

bool SelectionManager::IsADistrictSelected()
{
    DistrictBase* district = GetSelectedDistrict();
    bool isUnitSelected = false;
    if (district != m_districtEmpty)
    {
        delete district;
        isUnitSelected = true;
    }
    return isUnitSelected;
}

void SelectionManager::UnitSell()
{
    // TODO: Sell Unit
}

void SelectionManager::DistrictSell()
{
    // TODO: Sell District
}

void SelectionManager::UnitUpgrade()
{
    // TODO: unit upgrade
}

void SelectionManager::DistrictUpgrade()
{
    // TODO: unit upgrade
}

void SelectionManager::UnitHeal()
{
    // TODO
}

void SelectionManager::DistrictRepair()
{
    // TODO
}


void SelectionManager::SpawnSwordsman()
{
    ArmySkillTree skillTree = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID())->GetArmySkillTree();

    if (skillTree.SwordT3)
    {
        CreateUnitPressed(UnitSwordsmanIII::UNIT_TYPE);
    }
    else if (skillTree.SwordT2)
    {
        CreateUnitPressed(UnitSwordsmanII::UNIT_TYPE);
    }
    else
    {
        CreateUnitPressed(UnitSwordsmanI::UNIT_TYPE);
    }
}

void SelectionManager::SpawnArcher()
{
    ArmySkillTree skillTree = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID())->GetArmySkillTree();
    if (skillTree.ArcherT3)
    {
        CreateUnitPressed(UnitArcherIII::UNIT_TYPE);
    }
    else if (skillTree.ArcherT2)
    {
        CreateUnitPressed(UnitArcherII::UNIT_TYPE);
    }
    else if (skillTree.ArcherT1)
    {
        CreateUnitPressed(UnitArcherI::UNIT_TYPE);
    }

}

void SelectionManager::SpawnAxeman()
{
    ArmySkillTree skillTree = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID())->GetArmySkillTree();
    if (skillTree.AxeT2)
    {
        CreateUnitPressed(UnitAxemanII::UNIT_TYPE);
    }
    else if (skillTree.AxeT1)
    {
        CreateUnitPressed(UnitAxemanI::UNIT_TYPE);
    }

}

void SelectionManager::SpawnMace()
{
    ArmySkillTree skillTree = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID())->GetArmySkillTree();
    if (skillTree.MaceT2)
    {
        CreateUnitPressed(UnitMaceII::UNIT_TYPE);
    }
    else if (skillTree.MaceT1)
    {
        CreateUnitPressed(UnitMaceI::UNIT_TYPE);
    }

}

void SelectionManager::SpawnCannon()
{
    ArmySkillTree skillTree = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID())->GetArmySkillTree();
    if (skillTree.Canon)
    {
        CreateUnitPressed(UnitCannon::UNIT_TYPE);
    }

}

void SelectionManager::SpawnShield()
{
    ArmySkillTree skillTree = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID())->GetArmySkillTree();
    if (skillTree.Shield)
    {
        CreateUnitPressed(UnitShield::UNIT_TYPE);
    }

}

void SelectionManager::SpawnSettler()
{
    EmpireSkillTree skillTree = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID())->GetEmpireSkillTree();
    if (skillTree.Settler)
    {
        CreateUnitPressed(UnitSettler::UNIT_TYPE);
    }

}

