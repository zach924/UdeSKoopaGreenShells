#include <sstream>
#include "UtilitySkillTree.h"

UtilitySkillTree::UtilitySkillTree() :
    Watchtower(false), ScienceUpgrade(false), BorderGrowth(false), MovementUpgrade(false), Embark(false),
    VisionUpgrade(false), MountainWalking(false), MountainConstruction(false), ArmorUpgrade(false),
    University(false), NoFogOfWar(false)
{
}

UtilitySkillTree::UtilitySkillTree(std::string value) :
    Watchtower(value.at(0) != '0'), ScienceUpgrade(value.at(1) != '0'), BorderGrowth(value.at(2) != '0'),
    MovementUpgrade(value.at(3) != '0'), Embark(value.at(4) != '0'), VisionUpgrade(value.at(5) != '0'),
    MountainWalking(value.at(6) != '0'), MountainConstruction(value.at(7) != '0'),
    ArmorUpgrade(value.at(8) != '0'), University(value.at(9) != '0'), NoFogOfWar(value.at(10) != '0')
{
}

UtilitySkillTree UtilitySkillTree::GetReadyForResearch()
{
    UtilitySkillTree canResearch{};

    canResearch.Watchtower = true;
    canResearch.ScienceUpgrade = Watchtower;
    canResearch.BorderGrowth = ScienceUpgrade;
    canResearch.MovementUpgrade = BorderGrowth;
    canResearch.Embark = BorderGrowth;
    canResearch.MountainWalking = MovementUpgrade;
    canResearch.MountainConstruction = MountainWalking;
    canResearch.VisionUpgrade = Embark || MovementUpgrade;
    canResearch.ArmorUpgrade = VisionUpgrade;
    canResearch.NoFogOfWar = ArmorUpgrade;
    canResearch.University = ArmorUpgrade;

    return canResearch;
}

std::string UtilitySkillTree::toString()
{
    std::stringstream ss;
    ss << Watchtower << ScienceUpgrade << BorderGrowth << MovementUpgrade
        << Embark << VisionUpgrade << MountainWalking << MountainConstruction
        << ArmorUpgrade << University << NoFogOfWar;
    return ss.str();
}