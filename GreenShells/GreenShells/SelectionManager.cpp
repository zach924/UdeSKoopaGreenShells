#include "SelectionManager.h"

#include <iostream>

#include "Map.h"
#include "Position.h"
#include "ServerSession.h"
#include "Tile.h"
#include "Unit.h"
#include "District.h"
#include "GameSession.h"


SelectionManager::SelectionManager()
	:m_selectedDistrict(nullptr),
	m_selectedUnit(nullptr),
	m_state(m_idle)
{
}


SelectionManager::~SelectionManager()
{
}

void SelectionManager::DeselectUnit(Unit* unit)
{
	// TODO: need to be called when Unit dies
	if (unit == m_selectedUnit || unit == nullptr)
	{
		m_selectedUnit = nullptr;
		m_state = m_idle;
	}
}
void SelectionManager::DeselectDistrict(District* district)
{
	// TODO: need to be called when District is destroyed
	if (district == m_selectedDistrict || district == nullptr)
	{
		m_selectedDistrict = nullptr;
	}
}

void SelectionManager::SelectUnit(Unit * unitToSelect)
{
	m_selectedUnit = unitToSelect;
	m_state = m_idle;
}

void SelectionManager::SelectDistrict(District * districtToSelect)
{
	m_selectedDistrict = districtToSelect;
}

void SelectionManager::HandleSelection(Position pos)
{
	//TODO taskID 8.2 Processus de selection
	TileBase* tile = ServerSession::GetInstance().m_worldState.GetMap()->GetTile(pos);
	Map* map = ServerSession::GetInstance().m_worldState.GetMap();


	//TODO when replication is available, use gamesession
	//Map* map = GameSession::GetInstance().GetWorldState()->GetMap();

	Unit* unit = tile->GetUnit();
	District* district = tile->GetDistrict();

	switch (m_state)
	{
	case m_idle:
		std::cout << "Selecting Unit and district at pos " << pos.X << " " << pos.Y << std::endl;
		SelectUnit(unit);
		SelectDistrict(district);
		break;
	case m_unitMoving:
		std::cout << "Moving Unit, Deselecting District and Unit Setting to Idle" << std::endl;
		map->MoveUnit(GameSession::GetInstance().GetCurrentPlayerID(), m_selectedUnit->GetPosition(), pos);
		DeselectUnit();
		DeselectDistrict();
		m_state = m_idle;
		break;
	case m_unitAttacking:
		std::cout << "Attacking Unit, Deselecting District and Unit Setting to Idle" << std::endl;
		// TODO: attack
		DeselectUnit();
		DeselectDistrict();
		m_state = m_idle;
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
	}
}

void SelectionManager::UnitMovePressed()
{
	if (IsAnUnitSelected())
	{
		std::cout << "Selection Manager Move State" << std::endl;

		m_state = m_unitMoving;
	}
}

bool SelectionManager::IsAnActorSelected()
{
	return IsAnDistrictSelected() || IsAnActorSelected();
}

bool SelectionManager::IsAnUnitSelected()
{
	return m_selectedUnit != nullptr;
}

bool SelectionManager::IsAnDistrictSelected()
{
	return m_selectedDistrict != nullptr;
}
