#include "Unit.h"
#include "Texture.h"

#include "UnitSettler.h"
#include "UnitBuilder.h"

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


Texture UnitSettler::tBase::m_unitTexture = {};
Texture UnitSettler::tBase::m_boatTexture = {};
Texture UnitBuilder::tBase::m_unitTexture = {};
Texture UnitBuilder::tBase::m_boatTexture = {};

Texture UnitSwordsmanI::tBase::m_unitTexture = {};
Texture UnitSwordsmanI::tBase::m_boatTexture = {};
Texture UnitSwordsmanII::tBase::m_unitTexture = {};
Texture UnitSwordsmanII::tBase::m_boatTexture = {};
Texture UnitSwordsmanIII::tBase::m_unitTexture = {};
Texture UnitSwordsmanIII::tBase::m_boatTexture = {};

Texture UnitArcherI::tBase::m_unitTexture = {};
Texture UnitArcherI::tBase::m_boatTexture = {};
Texture UnitArcherII::tBase::m_unitTexture = {};
Texture UnitArcherII::tBase::m_boatTexture = {};
Texture UnitArcherIII::tBase::m_unitTexture = {};
Texture UnitArcherIII::tBase::m_boatTexture = {};

Texture UnitAxemanI::tBase::m_unitTexture = {};
Texture UnitAxemanI::tBase::m_boatTexture = {};
Texture UnitAxemanII::tBase::m_unitTexture = {};
Texture UnitAxemanII::tBase::m_boatTexture = {};

Texture UnitMaceI::tBase::m_unitTexture = {};
Texture UnitMaceI::tBase::m_boatTexture = {};
Texture UnitMaceII::tBase::m_unitTexture = {};
Texture UnitMaceII::tBase::m_boatTexture = {};

Texture UnitCannon::tBase::m_unitTexture = {};
Texture UnitCannon::tBase::m_boatTexture = {};
Texture UnitShield::tBase::m_unitTexture = {};
Texture UnitShield::tBase::m_boatTexture = {};

Texture UnitEmpty::tBase::m_unitTexture = {};
Texture UnitEmpty::tBase::m_boatTexture = {};

bool UnitSettler::tBase::m_forceLoading = false;
bool UnitBuilder::tBase::m_forceLoading = false;

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