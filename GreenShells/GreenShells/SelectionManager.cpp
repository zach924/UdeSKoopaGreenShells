#include "SelectionManager.h"

#include <iostream>

#include "MapRemote.h"
#include "Position.h"
#include "ServerSession.h"
#include "Tile.h"
#include "UnitBase.h"
#include "UnitEmpty.h"
#include "DistrictBase.h"
#include "DistrictEmpty.h"
#include "GameSession.h"
#include "ClickManager.h"

SelectionManager::SelectionManager()
	:m_selectedDistrict(new DistrictEmpty(-1))
	, m_selectedUnit(new UnitEmpty(-1))
	, m_state(m_idle)
	, m_unitEmpty(new UnitEmpty(-1))
	, m_districtEmpty(new DistrictEmpty(-1))
    , m_actionPossibleTiles()
{
}

SelectionManager::~SelectionManager()
{
}

UnitBase* SelectionManager::GetSelectedUnit()
{
    return m_selectedUnit;
}

DistrictBase* SelectionManager::GetSelectedDistrict()
{
    return m_selectedDistrict;
}

std::vector<Position> SelectionManager::GetOverlayTiles()
{
    return m_actionPossibleTiles;
}

void SelectionManager::DeselectUnit(UnitBase* unit)
{
	// TODO: need to be called when Unit dies
	if (unit == m_selectedUnit || unit == nullptr)
	{
		m_selectedUnit = m_unitEmpty;
		m_state = m_idle;
	}
}

void SelectionManager::DeselectDistrict(DistrictBase* district)
{
	// TODO: need to be called when District is destroyed
	if (district == m_selectedDistrict || district == nullptr)
	{
		m_selectedDistrict = m_districtEmpty;
	}
}

void SelectionManager::SelectUnit(UnitBase * unitToSelect)
{
	m_selectedUnit = unitToSelect ? unitToSelect : m_unitEmpty;
	m_state = m_idle;
}

void SelectionManager::SelectDistrict(DistrictBase * districtToSelect)
{
	m_selectedDistrict = districtToSelect ? districtToSelect : m_districtEmpty;
}

void SelectionManager::ChangeButtonState(ButtonState unitState, ButtonState districtState)
{
	std::vector<Button*> unitButtons = ClickManager::GetInstance().GetUnitButtons();
	for (auto btn : unitButtons)
	{
		btn->SetButtonState(unitState);
	}
	
	std::vector<Button*> districtButtons = ClickManager::GetInstance().GetDistrictButtons();
	for (auto btn : districtButtons)
	{
		btn->SetButtonState(districtState);
	}
}

void SelectionManager::Idle(UnitBase* unit, DistrictBase* district)
{
	SelectUnit(unit);
	SelectDistrict(district);

	// Without that {} it doesnt compile....
	ButtonState btnUnitState;
	if (unit && unit->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID())
	{
		btnUnitState = ButtonState::Unpressed;
	}
	else
	{
		btnUnitState = ButtonState::Disabled;
	}

	ButtonState btnDistrictState;
	if (district && district->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID())
	{
		btnDistrictState = ButtonState::Unpressed;
	}
	else
	{
		btnDistrictState = ButtonState::Disabled;
	}

	ChangeButtonState(btnUnitState, btnDistrictState);
}

void SelectionManager::Attack(Map * map, Position pos)
{
	map->Attack(GameSession::GetInstance().GetCurrentPlayerID(), m_selectedUnit->GetPosition(), pos);
	DeselectUnit();
	DeselectDistrict();
	m_state = m_idle;
	m_actionPossibleTiles.clear();

	ChangeButtonState(ButtonState::Disabled, ButtonState::Disabled);
}

void SelectionManager::Move(Map * map, Position pos)
{
	map->MoveUnit(GameSession::GetInstance().GetCurrentPlayerID(), m_selectedUnit->GetPosition(), pos);
	DeselectUnit();
	DeselectDistrict();
	m_state = m_idle;
	m_actionPossibleTiles.clear();

	ChangeButtonState(ButtonState::Disabled, ButtonState::Disabled);
}

void SelectionManager::HandleSelection(Position pos)
{
	//TODO taskID 8.2 Processus de selection
	Map* map = GameSession::GetInstance().GetWorldState()->GetMap();
	TileBase* tile = map->GetTile(pos);


	UnitBase* unit = tile->GetUnit();
	DistrictBase* district = tile->GetDistrict();
    
	// If the tile selected is not in our range of action possible, we remove the selected actor and do like no action was waiting
	if (m_state != m_idle && std::find(m_actionPossibleTiles.begin(), m_actionPossibleTiles.end(), tile->GetPosition()) == m_actionPossibleTiles.end())
	{
		DeselectUnit();
		DeselectDistrict();
		m_state = m_idle;
		m_actionPossibleTiles.clear();
	}

	switch (m_state)
	{
	case m_idle:
		std::cout << "Selecting Unit and district at pos " << pos.Column << " " << pos.Row << std::endl;
		Idle(unit, district);
		break;
	case m_unitMoving:
		std::cout << "Moving Unit, Deselecting District and Unit Setting to Idle" << std::endl;
		Move(map, pos);
		break;
	case m_unitAttacking:
		std::cout << "Attacking Unit, Deselecting District and Unit Setting to Idle" << std::endl;
		Attack(map, pos);
		
		break;
	default:
		break;
	}
}

void SelectionManager::UnitAttackPressed()
{
	if (IsAnUnitSelected())
	{
		std::cout << "Selection Manager attack State" << std::endl;

		m_state = m_unitAttacking;

		Map map = GameSession::GetInstance().GetWorldState()->GetMapCopy();
		m_actionPossibleTiles = map.GetArea(m_selectedUnit->GetPosition(), m_selectedUnit->GetAttackRange());
	}
}

void SelectionManager::UnitMovePressed()
{
	if (IsAnUnitSelected())
	{
		std::cout << "Selection Manager Move State" << std::endl;

		m_state = m_unitMoving;

		Map map = GameSession::GetInstance().GetWorldState()->GetMapCopy();
		m_actionPossibleTiles = map.GetArea(m_selectedUnit->GetPosition(), m_selectedUnit->GetMoveRange());
	}
}

bool SelectionManager::IsAnUnitSelected()
{
	return dynamic_cast<UnitEmpty*>(m_selectedUnit) == nullptr;
}

bool SelectionManager::IsAnDistrictSelected()
{
	return dynamic_cast<DistrictEmpty*>(m_selectedDistrict) == nullptr;
}

void SelectionManager::UnitSell()
{
	// TODO: Sell Unit
}
