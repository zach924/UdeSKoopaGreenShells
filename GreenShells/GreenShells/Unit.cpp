#include "Unit.h"
#include "Texture.h"

#include "UnitSettler.h"

#include "UnitSwordsman.h"

#include "UnitArcher.h"

#include "UnitAxeman.h"

#include "UnitEmpty.h"

#include "UnitCannon.h"


Texture UnitSettler::tBase::m_Texture = {};

Texture UnitSwordsman::tBase::m_Texture = {};

Texture UnitArcher::tBase::m_Texture = {};

Texture UnitAxeman::tBase::m_Texture = {};

Texture UnitCannon::tBase::m_Texture = {};

Texture UnitEmpty::tBase::m_Texture = {};


bool UnitSettler::tBase::m_forceLoading = false;

bool UnitArcher::tBase::m_forceLoading = false;

bool UnitSwordsman::tBase::m_forceLoading = false;

bool UnitAxeman::tBase::m_forceLoading = false;

bool UnitCannon::tBase::m_forceLoading = false;

bool UnitEmpty::tBase::m_forceLoading = false;