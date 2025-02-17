#include <sstream>
#include "EmpireSkillTree.h"

EmpireSkillTree::EmpireSkillTree() :
    Settler(false), Monastery(false), Farm(false), Windmill(false), Fishery(false),
    Stable(false), Cathedral(false), Fort(false), MilitaryTent(false), InnAndTavern(false),
    Warehouse(false), RessourcesBonus(false), School(false)
{
}

EmpireSkillTree::EmpireSkillTree(std::string value) :
    Settler(value.at(0) != '0'), Monastery(value.at(1) != '0'), Farm(value.at(2) != '0'),
    Windmill(value.at(3) != '0'), Fishery(value.at(4) != '0'), Stable(value.at(5) != '0'),
    Cathedral(value.at(6) != '0'), Fort(value.at(7) != '0'), MilitaryTent(value.at(8) != '0'),
    InnAndTavern(value.at(9) != '0'), Warehouse(value.at(10) != '0'),
    RessourcesBonus(value.at(11) != '0'), School(value.at(12) != '0')
{
}

EmpireSkillTree EmpireSkillTree::GetReadyForResearch()
{
    EmpireSkillTree canResearch{};

    canResearch.Monastery = true;
    canResearch.Settler = Monastery;
    canResearch.Farm = Settler;
    canResearch.Fishery = Settler;
    canResearch.Stable = Settler;
    canResearch.Windmill = Farm;
    canResearch.Cathedral = Stable || Fishery || Farm;
    canResearch.Fort = Stable;
    canResearch.InnAndTavern = Fort || Cathedral || Windmill;
    canResearch.MilitaryTent = Cathedral || Fort || Windmill;
    canResearch.Warehouse = InnAndTavern;
    canResearch.School = InnAndTavern;
    canResearch.RessourcesBonus = Warehouse;

    return canResearch;
}

std::string EmpireSkillTree::toString()
{
    std::stringstream ss;
    ss << Settler << Monastery << Farm << Windmill
        << Fishery << Stable << Cathedral << Fort
        << MilitaryTent << InnAndTavern << Warehouse << RessourcesBonus << School;
    return ss.str();
}