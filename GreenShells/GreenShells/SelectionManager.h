#pragma once
class Position;
class Unit;
class District;
class SelectionManager
{
	enum SelectionManagerState
	{
		m_idle,
		m_unitMoving,
		m_unitAttacking
	};

	SelectionManagerState m_state;

	Unit * m_selectedUnit;
	District * m_selectedDistrict;

	SelectionManager(SelectionManager const&) = delete;
	void operator=(SelectionManager const&) = delete;

	SelectionManager();
	~SelectionManager();

	

	void DeselectUnit(Unit* unit = nullptr);
	void DeselectDistrict(District* district = nullptr);

	void SelectUnit(Unit* unitToSelect);
	void SelectDistrict(District* districtToSelect);
public:

	static SelectionManager& GetInstance()
	{
		static SelectionManager m_instance;
		return m_instance;
	}

	void HandleSelection(Position pos);

	void UnitAttackPressed();
	void UnitMovePressed();

	bool IsAnActorSelected();
	bool IsAnUnitSelected();
	bool IsAnDistrictSelected();
	
};

