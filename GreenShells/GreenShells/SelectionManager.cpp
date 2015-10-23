#include "SelectionManager.h"

#include <iostream>

#include "MapLocal.h"
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
	, m_actionPossibleTile()
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

void SelectionManager::HandleSelection(Position pos)
{
	//TODO taskID 8.2 Processus de selection
	Map* map = GameSession::GetInstance().GetWorldState()->GetMap();
	//Map map = GameSession::GetInstance().GetWorldState()->GetMapCopy();
	TileBase* tile = map->GetTile(pos);


	UnitBase* unit = tile->GetUnit();
	DistrictBase* district = tile->GetDistrict();

	// If the tile selected is not in our range of action possible, we remove the selected actor and do like no action was waiting
	if (m_state != m_idle && std::find(m_actionPossibleTile.begin(), m_actionPossibleTile.end(), tile->GetPosition()) == m_actionPossibleTile.end())
	{
		DeselectUnit();
		DeselectDistrict();
		m_state = m_idle;
		m_actionPossibleTile.clear();
	}

	switch (m_state)
	{
	case m_idle:
	{ // NEEDED {} because Switch Case statement doesn't like declaration in the CASE statement
		std::cout << "Selecting Unit and district at pos " << pos.Column << " " << pos.Row << std::endl;
		SelectUnit(unit);
		SelectDistrict(district);

		// Without that {} it doesnt compile....
		ButtonState btnUnitState = unit && unit->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID() ? ButtonState::Unpressed : ButtonState::Disabled;
		std::vector<Button*> unitButtons = ClickManager::GetInstance().GetUnitButtons();
		for (auto btn : unitButtons)
		{
			btn->SetButtonState(btnUnitState);
		}



		ButtonState btnDistrictState = district && district->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID() ? ButtonState::Unpressed : ButtonState::Disabled;
		std::vector<Button*> districtButtons = ClickManager::GetInstance().GetDistrictButtons();
		for (auto btn : districtButtons)
		{
			btn->SetButtonState(btnDistrictState);
		}


		break;
	}
	case m_unitMoving:
		std::cout << "Moving Unit, Deselecting District and Unit Setting to Idle" << std::endl;
		map->MoveUnit(GameSession::GetInstance().GetCurrentPlayerID(), m_selectedUnit->GetPosition(), pos);
		DeselectUnit();
		DeselectDistrict();
		m_state = m_idle;
		m_actionPossibleTile.clear();
		break;
	case m_unitAttacking:
		std::cout << "Attacking Unit, Deselecting District and Unit Setting to Idle" << std::endl;
		
		// Consider that GetArea give me only the tile attackable.
		map->Attack(GameSession::GetInstance().GetCurrentPlayerID(), m_selectedUnit->GetPosition(), pos);

		DeselectUnit();
		DeselectDistrict();
		m_state = m_idle;
		m_actionPossibleTile.clear();
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
		m_actionPossibleTile = map.GetArea(m_selectedUnit->GetPosition(), m_selectedUnit->GetAttackRange());
	}
}

void SelectionManager::UnitMovePressed()
{
	if (IsAnUnitSelected())
	{
		std::cout << "Selection Manager Move State" << std::endl;

		m_state = m_unitMoving;

		Map map = GameSession::GetInstance().GetWorldState()->GetMapCopy();
		m_actionPossibleTile = map.GetArea(m_selectedUnit->GetPosition(), m_selectedUnit->GetMoveRange());
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
