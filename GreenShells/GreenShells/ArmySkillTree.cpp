#include <sstream>
#include "ArmySkillTree.h"

ArmySkillTree::ArmySkillTree():
	Militia(false), RangerT1(false), RangerT2(false), RangerT3(false), SwordT2(false),
	SwordT3(false), AxeT1(false), AxeT2(false), MaceT1(false), MaceT2(false),
	Fortress(false), Shield(false), Canon(false)
{
}

ArmySkillTree::ArmySkillTree(std::string value):
	Militia(value.at(0) != '0'), RangerT1(value.at(1) != '0'), RangerT2(value.at(2) != '0'),
	RangerT3(value.at(3) != '0'), SwordT2(value.at(4) != '0'), SwordT3(value.at(5) != '0'),
	AxeT1(value.at(6) != '0'), AxeT2(value.at(7) != '0'), MaceT1(value.at(8) != '0'),
	MaceT2(value.at(9) != '0'),	Fortress(value.at(10) != '0'), Shield(value.at(11) != '0'),
	Canon(value.at(12) != '0')
{
}

ArmySkillTree ArmySkillTree::GetReadyForResearch()
{
	ArmySkillTree canResearch{};

	canResearch.RangerT1 = true;

	if (RangerT1)
	{
		canResearch.Militia = true;
	}

	if (Militia)
	{
		canResearch.SwordT2 = true;
		canResearch.AxeT1 = true;
	}

	if (AxeT1)
	{
		canResearch.AxeT2 = true;
		canResearch.RangerT2 = true;
	}

	if (SwordT2)
	{
		canResearch.SwordT3 = true;
		canResearch.RangerT2 = true;
	}

	if (RangerT2)
	{
		canResearch.MaceT1 = true;
	}

	if (MaceT1)
	{
		canResearch.MaceT2 = true;
		canResearch.RangerT3 = true;
	}

	if (RangerT3)
	{
		canResearch.Fortress = true;
		canResearch.Shield = true;
	}

	if (Shield)
	{
		canResearch.Canon = true;
	}

	return canResearch;
}

std::string ArmySkillTree::toString()
{
	std::stringstream ss;
	ss << Militia << RangerT1 << RangerT1 << RangerT1
		<< SwordT2 << SwordT2 << AxeT1 << AxeT1
		<< MaceT1 << MaceT1 << Fortress << Shield << Canon;
	return ss.str();
}