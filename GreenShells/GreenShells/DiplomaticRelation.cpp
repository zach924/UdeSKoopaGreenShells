#include "DiplomaticRelation.h"

DiplomaticRelation::DiplomaticRelation(int propositionTurn, RelationStatus status, int mustAnswerPlayerId)
    :m_status(status)
    ,m_mustAnswerPlayerId(mustAnswerPlayerId)
    ,m_propositionTurn(propositionTurn)
{
}

DiplomaticRelation::~DiplomaticRelation()
{
}

void DiplomaticRelation::ChangeRelationStatus(RelationStatus status, int currentTurn, int mustAnswerPlayerId)
{
    m_status = status;
    m_propositionTurn = currentTurn;
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

int DiplomaticRelation::GetPropositionTurn()
{
    return m_propositionTurn;
}
