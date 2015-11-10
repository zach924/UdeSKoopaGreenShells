#include "Unit.h"
#include "Texture.h"

#include "UnitArcher.h"
#include "UnitSwordsman.h"
#include "UnitSettler.h"
#include "UnitEmpty.h"

Texture UnitEmpty::tBase::m_Texture = {};
Texture UnitSwordsman::tBase::m_Texture = {};
Texture UnitArcher::tBase::m_Texture = {};
Texture UnitSettler::tBase::m_Texture = {};

bool UnitEmpty::tBase::m_forceLoading = false;
bool UnitSwordsman::tBase::m_forceLoading = false;
bool UnitArcher::tBase::m_forceLoading = false;
bool UnitSettler::tBase::m_forceLoading = false;