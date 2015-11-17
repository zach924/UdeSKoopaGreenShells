#include "Unit.h"
#include "Texture.h"

#include "UnitSettler.h"

#include "UnitSwordsmanI.h"
#include "UnitSwordsmanII.h"
#include "UnitSwordsmanIII.h"

#include "UnitArcherI.h"
#include "UnitArcherII.h"
#include "UnitArcherIII.h"

#include "UnitAxemanI.h"
#include "UnitAxemanII.h"

#include "UnitMaceI.h"
#include "UnitMaceII.h"

#include "UnitCannon.h"
#include "UnitShield.h"

#include "UnitEmpty.h"


Texture UnitSettler::tBase::m_Texture = {};

Texture UnitSwordsmanI::tBase::m_Texture = {};
Texture UnitSwordsmanII::tBase::m_Texture = {};
Texture UnitSwordsmanIII::tBase::m_Texture = {};

Texture UnitArcherI::tBase::m_Texture = {};
Texture UnitArcherII::tBase::m_Texture = {};
Texture UnitArcherIII::tBase::m_Texture = {};

Texture UnitAxemanI::tBase::m_Texture = {};
Texture UnitAxemanII::tBase::m_Texture = {};

Texture UnitMaceI::tBase::m_Texture = {};
Texture UnitMaceII::tBase::m_Texture = {};

Texture UnitCannon::tBase::m_Texture = {};
Texture UnitShield::tBase::m_Texture = {};

Texture UnitEmpty::tBase::m_Texture = {};


bool UnitSettler::tBase::m_forceLoading = false;

bool UnitArcherI::tBase::m_forceLoading = false;
bool UnitArcherII::tBase::m_forceLoading = false;
bool UnitArcherIII::tBase::m_forceLoading = false;

bool UnitSwordsmanI::tBase::m_forceLoading = false;
bool UnitSwordsmanII::tBase::m_forceLoading = false;
bool UnitSwordsmanIII::tBase::m_forceLoading = false;

bool UnitAxemanI::tBase::m_forceLoading = false;
bool UnitAxemanII::tBase::m_forceLoading = false;

bool UnitMaceI::tBase::m_forceLoading = false;
bool UnitMaceII::tBase::m_forceLoading = false;

bool UnitCannon::tBase::m_forceLoading = false;
bool UnitShield::tBase::m_forceLoading = false;

bool UnitEmpty::tBase::m_forceLoading = false;