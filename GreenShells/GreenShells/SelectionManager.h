#pragma once
#include <vector>
class Position;
class UnitBase;
class DistrictBase;

class SelectionManager
{
	enum SelectionManagerState
	{
		m_idle,
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
public:

	static SelectionManager& GetInstance()
	{
		static SelectionManager m_instance;
		return m_instance;
	}

    UnitBase* GetSelectedUnit();
    DistrictBase* GetSelectedDistrict();
    std::vector<Position> GetOverlayTiles();

	void HandleSelection(Position pos);

	void UnitAttackPressed();
	void UnitMovePressed();

	bool IsAnUnitSelected();
	bool IsAnDistrictSelected();
	
	void UnitSell();
};

