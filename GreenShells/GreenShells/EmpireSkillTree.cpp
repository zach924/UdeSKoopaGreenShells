#include <sstream>
#include "EmpireSkillTree.h"

EmpireSkillTree::EmpireSkillTree() :
    Settler(false), Monastery(false), Farm(false), Winmill(false), Fishery(false),
    Stable(false), Cathedral(false), Fort(false), MilitaryTent(false), InnAndTavern(false),
    Warehouse(false), RessourcesBonus(false)
{
}

EmpireSkillTree::EmpireSkillTree(std::string value) :
    Settler(value.at(0) != '0'), Monastery(value.at(1) != '0'), Farm(value.at(2) != '0'),
    Winmill(value.at(3) != '0'), Fishery(value.at(4) != '0'), Stable(value.at(5) != '0'),
    Cathedral(value.at(6) != '0'), Fort(value.at(7) != '0'), MilitaryTent(value.at(8) != '0'),
    InnAndTavern(value.at(9) != '0'), Warehouse(value.at(10) != '0'),
    RessourcesBonus(value.at(11) != '0')
{
}

EmpireSkillTree EmpireSkillTree::GetReadyForResearch()
{
    EmpireSkillTree canResearch{};

    canResearch.Settler = true;

    if (Settler)
    {
        canResearch.Monastery = true;
    }

    if (Monastery)
    {
        canResearch.Farm = true;
        canResearch.Fishery = true;
        canResearch.Stable = true;
    }

    if (Farm)
    {
        canResearch.Cathedral = true;
        canResearch.Winmill = true;
    }

    if (Fishery)
    {
        canResearch.Cathedral = true;
    }

    if (Stable)
    {
        canResearch.Cathedral = true;
        canResearch.Fort = true;
    }

    if (Cathedral)
    {
        canResearch.MilitaryTent = true;
        canResearch.InnAndTavern = true;
    }

    if (Winmill)
    {
        canResearch.InnAndTavern = true;
        canResearch.MilitaryTent = true;
    }

    if (Fort)
    {
        canResearch.MilitaryTent = true;
        canResearch.InnAndTavern = true;
    }

    if (InnAndTavern)
    {
        canResearch.Warehouse = true;
    }

    if (Warehouse)
    {
        canResearch.RessourcesBonus = true;
    }

    return canResearch;
}

std::string EmpireSkillTree::toString()
{
    std::stringstream ss;
    ss << Settler << Monastery << Farm << Winmill
        << Fishery << Stable << Cathedral << Fort
        << MilitaryTent << InnAndTavern << Warehouse << RessourcesBonus;
    return ss.str();
}