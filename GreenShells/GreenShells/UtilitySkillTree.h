#pragma once

#include <string>

class UtilitySkillTree
{
public:
    bool Watchtower : 1;
    bool ScienceUpgrade : 1;
    bool BorderGrowth : 1;
    bool MovementUpgrade : 1;
    bool Embark : 1;
    bool VisionUpgrade : 1;
    bool MountainWalking : 1;
    bool MountainConstruction : 1;
    bool ArmorUpgrade : 1;
    bool University : 1;
    bool NoFogOfWar : 1;

    UtilitySkillTree();
    UtilitySkillTree(std::string value);
    UtilitySkillTree GetReadyForResearch();
    std::string toString();
};
