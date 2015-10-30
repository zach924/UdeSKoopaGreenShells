#pragma once

#include <string>

class EmpireSkillTree
{
    bool Settler : 1;
    bool Monastery : 1;
    bool Farm : 1;
    bool Winmill : 1;
    bool Fishery : 1;
    bool Stable : 1;
    bool Cathedral : 1;
    bool Fort : 1;
    bool MilitaryTent : 1;
    bool InnAndTavern : 1;
    bool Warehouse : 1;
    bool RessourcesBonus : 1;

public:
    EmpireSkillTree();
    EmpireSkillTree(std::string value);

    EmpireSkillTree GetReadyForResearch();
    std::string toString();
};