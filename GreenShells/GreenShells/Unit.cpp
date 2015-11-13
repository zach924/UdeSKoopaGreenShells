#include "Unit.h"
#include "Texture.h"

#include "UnitSettler.h"

#include "UnitSwordsmanI.h"
#include "UnitSwordsmanII.h"
#include "UnitSwordsmanIII.h"

#include "UnitArcher.h"

#include "UnitAxeman.h"

#include "UnitMace.h"

#include "UnitCannon.h"

#include "UnitEmpty.h"


Texture UnitSettler::tBase::m_Texture = {};

Texture UnitSwordsmanI::tBase::m_Texture = {};
Texture UnitSwordsmanII::tBase::m_Texture = {};
Texture UnitSwordsmanIII::tBase::m_Texture = {};

Texture UnitArcher::tBase::m_Texture = {};

Texture UnitAxeman::tBase::m_Texture = {};

Texture UnitMace::tBase::m_Texture = {};

Texture UnitCannon::tBase::m_Texture = {};

Texture UnitEmpty::tBase::m_Texture = {};


bool UnitSettler::tBase::m_forceLoading = false;

bool UnitArcher::tBase::m_forceLoading = false;

bool UnitSwordsmanI::tBase::m_forceLoading = false;
bool UnitSwordsmanII::tBase::m_forceLoading = false;
bool UnitSwordsmanIII::tBase::m_forceLoading = false;

bool UnitAxeman::tBase::m_forceLoading = false;

bool UnitMace::tBase::m_forceLoading = false;

bool UnitCannon::tBase::m_forceLoading = false;

bool UnitEmpty::tBase::m_forceLoading = false;