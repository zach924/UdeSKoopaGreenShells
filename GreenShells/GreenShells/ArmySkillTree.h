#pragma once

#include <string>

class ArmySkillTree
{
public:

    bool Militia : 1;
    bool ArcherT1 : 1;
    bool ArcherT2 : 1;
    bool ArcherT3 : 1;
    bool SwordT2 : 1;
    bool SwordT3 : 1;
    bool AxeT1 : 1;
    bool AxeT2 : 1;
    bool MaceT1 : 1;
    bool MaceT2 : 1;
    bool Fortress : 1;
    bool Shield : 1;
    bool Canon : 1;

    ArmySkillTree();
    ArmySkillTree(std::string value);
    ArmySkillTree GetReadyForResearch();
    std::string toString();
};