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
#include "DistrictFarm.h"

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
        UnitBase* unitSelected = map->GetTile(m_selectedPosition)->GetUnit();

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
        DistrictBase* selecteDistrict = map->GetTile(m_selectedPosition)->GetDistrict();

        return selecteDistrict ? selecteDistrict->Clone() : m_districtEmpty;
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
                && selectedUnit->GetHealth() < 100) // TODO : get max health for unit
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
                && selectedDistrict->GetHealth() < 200) // TODO : GetMaxHeatlh
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
            if (selectedDistrict->GetTypeAsInt() == DistrictCityCenter::DISTRICT_TYPE
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
            if (selectedDistrict->GetTypeAsInt() == DistrictCityCenter::DISTRICT_TYPE
                && selectedDistrict->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID())
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
            if (GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID())->IsPlayerReadyForNextTurn())
            {
                btn->SetButtonState(ButtonState::Disabled);
            }
            else
            {
                btn->SetButtonState(ButtonState::Unpressed);
            }
        }
        else
        {
            assert(false && "You must implement this for your button!");
        }
    }

    if (selectedDistrict->GetTypeAsInt() != DistrictEmpty::DISTRICT_TYPE)
    {
        delete selectedDistrict;
    }
    if (selectedUnit->GetTypeAsInt() != UnitEmpty::UNIT_TYPE)
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
    GameSession::GetInstance().GetWorldState()->Attack(GameSession::GetInstance().GetCurrentPlayerID(), m_selectedPosition, pos);
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
    GameSession::GetInstance().GetWorldState()->MoveUnit(GameSession::GetInstance().GetCurrentPlayerID(), m_selectedPosition, pos);
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
    //TODO taskID 8.2 Processus de selection
    Map* map = GameSession::GetInstance().GetWorldState()->GetMap();
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

void SelectionManager::CreateDistrictPressed(int districtType)
{
    if (IsADistrictSelected())
    {
        std::cout << "Selection Manager create district State" << std::endl;

        m_state = m_createDistrict;
        m_districtTypeToConstruct = districtType;

        unique_ptr<Map> map{ GameSession::GetInstance().GetWorldState()->GetMapCopy() };
        std::vector<Position> allPositionNear = map->GetArea(m_selectedPosition, 3 /* TODO : Validate where the constant will be (MaxBorderRange) */, NO_FILTER);

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

        // TODO : Change for open the window and then create the unit
    }
}

void SelectionManager::UnitAttackPressed()
{
    if (IsAnUnitSelected())
    {
        std::cout << "Selection Manager attack State" << std::endl;

        m_state = m_unitAttacking;

        unique_ptr<Map> map{ GameSession::GetInstance().GetWorldState()->GetMapCopy() };

        std::vector<Position> allPositionNear = map->GetArea(m_selectedPosition, GetSelectedUnit()->GetAttackRange(), NO_FILTER);
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
    if (IsAnUnitSelected())
    {
        std::cout << "Selection Manager Move State" << std::endl;

        m_state = m_unitMoving;

        unique_ptr<Map> map{ GameSession::GetInstance().GetWorldState()->GetMapCopy() };
        Position unitPosition = m_selectedPosition;
        Player* player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
        std::vector<Position> allPositionNear = map->GetArea(unitPosition, GetSelectedUnit()->GetMoveRange(), player->GetMoveRestriction());
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

bool SelectionManager::IsAnUnitSelected()
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