#include "SelectionManager.h"

#include <iostream>

#include "Map.h"
#include "Position.h"
#include "ServerSession.h"
#include "Tile.h"
#include "UnitBase.h"
#include "UnitEmpty.h"
#include "DistrictBase.h"
#include "DistrictEmpty.h"
#include "GameSession.h"

SelectionManager::SelectionManager()
    :m_selectedDistrict(new DistrictEmpty(-1))
    , m_selectedUnit(new UnitEmpty(-1))
    , m_state(m_idle)
    , m_unitEmpty(new UnitEmpty(-1))
    , m_districtEmpty(new DistrictEmpty(-1))
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
	Map map = GameSession::GetInstance().GetWorldState()->GetMapCopy();
	TileBase* tile = map.GetTile(pos);
	
	UnitBase* unit = tile->GetUnit();
	DistrictBase* district = tile->GetDistrict();

	switch (m_state)
	{
	case m_idle:
		std::cout << "Selecting Unit and district at pos " << pos.X << " " << pos.Y << std::endl;
		SelectUnit(unit);
		SelectDistrict(district);
		break;
	case m_unitMoving:
		std::cout << "Moving Unit, Deselecting District and Unit Setting to Idle" << std::endl;
		map.MoveUnit(GameSession::GetInstance().GetCurrentPlayerID(), m_selectedUnit->GetPosition(), pos);
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

bool SelectionManager::IsAnUnitSelected()
{
	return dynamic_cast<UnitEmpty*>(m_selectedUnit) != nullptr;
}

bool SelectionManager::IsAnDistrictSelected()
{
	return dynamic_cast<DistrictEmpty*>(m_selectedDistrict) != nullptr;
}
