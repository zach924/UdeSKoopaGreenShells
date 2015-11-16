#include "District.h"
#include "Texture.h"

#include "DistrictCityCenter.h"
#include "DistrictFarm.h"
#include "DistrictEmpty.h"

Texture DistrictCityCenter::tBase::m_Texture = {};
Texture DistrictFarm::tBase::m_Texture = {};
Texture DistrictEmpty::tBase::m_Texture = {};

bool DistrictCityCenter::tBase::m_forceLoading = false;
bool DistrictFarm::tBase::m_forceLoading = false;
bool DistrictEmpty::tBase::m_forceLoading = false;
