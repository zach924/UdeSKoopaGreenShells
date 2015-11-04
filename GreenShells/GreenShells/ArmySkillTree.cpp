#include <sstream>
#include "ArmySkillTree.h"

ArmySkillTree::ArmySkillTree() :
    Militia(false), RangerT1(false), RangerT2(false), RangerT3(false), SwordT2(false),
    SwordT3(false), AxeT1(false), AxeT2(false), MaceT1(false), MaceT2(false),
    Fortress(false), Shield(false), Canon(false)
{
}

ArmySkillTree::ArmySkillTree(std::string value) :
    Militia(value.at(0) != '0'), RangerT1(value.at(1) != '0'), RangerT2(value.at(2) != '0'),
    RangerT3(value.at(3) != '0'), SwordT2(value.at(4) != '0'), SwordT3(value.at(5) != '0'),
    AxeT1(value.at(6) != '0'), AxeT2(value.at(7) != '0'), MaceT1(value.at(8) != '0'),
    MaceT2(value.at(9) != '0'), Fortress(value.at(10) != '0'), Shield(value.at(11) != '0'),
    Canon(value.at(12) != '0')
{
}

ArmySkillTree ArmySkillTree::GetReadyForResearch()
{
    ArmySkillTree canResearch{};

    canResearch.RangerT1 = true;
    canResearch.Militia = RangerT1;
    canResearch.SwordT2 = Militia;
    canResearch.AxeT1 = Militia;
    canResearch.AxeT2 = AxeT1;
    canResearch.RangerT2 = AxeT1;
    canResearch.SwordT3 = SwordT2;
    canResearch.RangerT2 = SwordT2;
    canResearch.MaceT1 = RangerT2;
    canResearch.MaceT2 = MaceT1;
    canResearch.RangerT3 = MaceT1;
    canResearch.Fortress = RangerT3;
    canResearch.Shield = RangerT3;
    canResearch.Canon = Shield;
   
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