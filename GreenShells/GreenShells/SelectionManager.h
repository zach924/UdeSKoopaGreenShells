#pragma once
#include <vector>
#include "TileBase.h"
class Position;
class UnitBase;
class DistrictBase;
class Map;
enum ButtonState;

class SelectionManager
{
	enum SelectionManagerState
	{
		m_idle,
		m_createDistrict,
		m_unitMoving,
		m_unitAttacking
	};

    UnitBase* m_unitEmpty;
    DistrictBase* m_districtEmpty;

	SelectionManagerState m_state;

	UnitBase * m_selectedUnit;
	DistrictBase * m_selectedDistrict;
	
	SelectionManager(SelectionManager const&) = delete;
	void operator=(SelectionManager const&) = delete;
    std::vector<Position> m_actionPossibleTiles;
	SelectionManager();
	~SelectionManager();

	void DeselectUnit(UnitBase* unit = nullptr);
	void DeselectDistrict(DistrictBase* district = nullptr);

	void SelectUnit(UnitBase* unitToSelect);
	void SelectDistrict(DistrictBase* districtToSelect);

	void ChangeButtonState(ButtonState unitState, ButtonState districtState);

	void Idle(UnitBase* unit, DistrictBase* district);
	void Attack(Map* map, Position pos);
	void CreateDistrict(Map* map, Position pos);
	void Move(Map* map, Position pos);

public:

	static SelectionManager& GetInstance()
	{
		static SelectionManager m_instance;
		return m_instance;
	}

    UnitBase* GetSelectedUnit();
    DistrictBase* GetSelectedDistrict();
    std::vector<Position> GetOverlayTiles();

	void Cancel();

	void HandleSelection(Position pos);

	void CreateDistrictPressed();

	void UnitAttackPressed();
	void UnitMovePressed();

	bool IsAnUnitSelected();
	bool IsAnDistrictSelected();
	
	void UnitSell();
};

