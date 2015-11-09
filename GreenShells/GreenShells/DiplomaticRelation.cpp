#include "DiplomaticRelation.h"

DiplomaticRelation::DiplomaticRelation(RelationStatus status, int mustAnswerPlayerId)
    :m_status(status)
    ,m_mustAnswerPlayerId(mustAnswerPlayerId)
{
}

DiplomaticRelation::~DiplomaticRelation()
{
}

void DiplomaticRelation::ChangeRelationStatus(RelationStatus status, int mustAnswerPlayerId)
{
    m_status = status;
    m_mustAnswerPlayerId = mustAnswerPlayerId;
}

int DiplomaticRelation::GetMustAnswerPlayerId()
{
    return m_mustAnswerPlayerId;
}

RelationStatus DiplomaticRelation::GetRelationStatus()
{
    return m_status;
}
